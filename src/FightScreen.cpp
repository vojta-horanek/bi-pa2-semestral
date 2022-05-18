#include "FightScreen.h"

#include <utility>

#include "Game.h"
#include "menu/ResumeMenu.h"
#include "render/Renderer.h"
#include "resources/strings/L10n.h"
#include "resources/strings/Paths.h"

FightScreen::FightScreen(std::shared_ptr<Player> player,
                         std::shared_ptr<GameState> gameState, int screenWidth,
                         int screenHeight)
    : Screen(screenWidth, screenHeight), m_Player(std::move(player)),
      m_GameState(std::move(gameState)) {

    m_BackgroundTexture = Texture(Paths::Bitmaps::fighting_background);
    m_Stats = std::make_unique<Stats>(3);

    m_PlayerHealthText.setFontSize(60);
    m_PlayerHealthText.setText(
        L10n::yourHealth +
        std::to_string(m_GameState->m_PlayerCurrentHealth));

    m_MonsterHealthText.setFontSize(60);
    m_MonsterHealthText.setText(
        L10n::monsterHealth +
        std::to_string(m_GameState->m_Monster->m_CurrentHealth));

    m_GameState->m_Monster->onFightBegin();
    m_Player->onFightBegin();
}

void FightScreen::onRender() {
    m_BackgroundTexture.renderFullscreen();

    int monsterXPos = 1;
    if (!m_IsPlayerTurn && !m_IsJustShown)
        monsterXPos--;

    int playerXPos = 3;
    if (m_IsPlayerTurn && !m_IsJustShown)
        playerXPos++;

    m_Player->render(*m_GameState, Vec(playerXPos, 4));
    m_GameState->m_Monster->render(
        *m_GameState, Vec(m_ScreenWidth / 2 / BLOCK_PIXELS + monsterXPos, 4));

    if (!m_IsFighting &&
        (m_Player->isFadeOut() || m_GameState->m_Monster->isFadeOut())) {
        m_IsFadeFinished = true;
    }

    Renderer::getInstance().selectDrawColor(0, 0, 0, 0xaa);
    Renderer::getInstance().drawRectangle(
        {Vec(0, m_ScreenHeight - m_ScreenHeight / 5),
         Vec(m_ScreenWidth, m_ScreenHeight / 5)},
        true);

    if (m_GameState->m_PlayerCurrentHealth > 0) {
        m_Stats->render(*m_GameState, Vec(0, m_ScreenHeight / BLOCK_PIXELS - 1),
                        false);
    }

    m_PlayerHealthText.render(
        Vec(m_ScreenWidth - m_PlayerHealthText.getBoxSize().x - 15,
            m_ScreenHeight - m_PlayerHealthText.getBoxSize().y - 15));

    m_MonsterHealthText.render(
        Vec(m_ScreenWidth - m_MonsterHealthText.getBoxSize().x - 15,
            m_ScreenHeight - m_MonsterHealthText.getBoxSize().y - 15 -
                m_PlayerHealthText.getBoxSize().y));
}

void FightScreen::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                m_NavigationDestination =
                    std::make_unique<ResumeMenu>(m_ScreenWidth, m_ScreenHeight);
                break;
            case SDLK_RETURN:
            case SDLK_SPACE:
                if (!m_IsJustShown && m_IsFighting) {
                    attack();
                } else if (m_IsJustShown) {
                    m_IsJustShown = false;
                    m_IsPlayerTurn = rand() % 2;
                }
                break;
        }
    }
}

bool FightScreen::shouldPopSelf() { return m_IsFadeFinished; }

FightScreen::~FightScreen() {
    m_Player->onFightEnd();
    if (m_GameState->m_Weapon != nullptr) {
        m_GameState->m_Weapon->onFightEnd();
    }
    m_GameState->m_Monster->onFightEnd();
    m_GameState->m_Monster = nullptr;
}

void FightScreen::attack() {
    m_IsPlayerTurn = !m_IsPlayerTurn;

    if (m_IsPlayerTurn) {
        if (m_GameState->m_Weapon != nullptr) {
            // Player has weapon
            m_GameState->m_Monster->m_CurrentHealth -=
                m_GameState->m_Weapon->getDamage() +
                m_GameState->m_PlayerDefaultDamage;
        } else {
            m_GameState->m_Monster->m_CurrentHealth -=
                m_GameState->m_PlayerDefaultDamage;
        }
    } else {
        m_GameState->m_PlayerCurrentHealth -=
            m_GameState->m_Monster->getDamage();
    }

    if (m_GameState->m_PlayerCurrentHealth <= 0) {
        m_GameState->m_PlayerCurrentHealth = 0;
        m_Player->fadeOut();
        if (m_GameState->m_Weapon != nullptr) {
            m_GameState->m_Weapon->fadeOut();
        }
        m_IsFighting = false;
    } else if (m_GameState->m_Monster->m_CurrentHealth <= 0) {
        m_GameState->m_Monster->m_CurrentHealth = 0;
        m_GameState->m_Monster->fadeOut();
        m_IsFighting = false;
    }

    m_PlayerHealthText.setText(
        L10n::yourHealth + std::to_string(m_GameState->m_PlayerCurrentHealth));

    m_MonsterHealthText.setText(
        L10n::monsterHealth +
        std::to_string(m_GameState->m_Monster->m_CurrentHealth));
}
