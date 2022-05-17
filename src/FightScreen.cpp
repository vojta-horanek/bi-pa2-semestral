#include "FightScreen.h"

#include <utility>

#include "Game.h"
#include "Renderer.h"
#include "ResumeMenu.h"
#include "entity/Weapon.h"
#include "resources/strings/L10n.h"
#include "resources/strings/Paths.h"

FightScreen::FightScreen(std::shared_ptr<Player> player,
                         std::shared_ptr<GameState> gameState, int width,
                         int height)
    : Screen(width, height), player(std::move(player)),
      gameState(std::move(gameState)) {

    background = Texture(Paths::Bitmaps::fighting_background);
    stats = std::make_unique<Stats>(3);

    m_PlayerHealthText.setFontSize(60);
    m_PlayerHealthText.setText(
        L10n::yourHealth +
        std::to_string(this->gameState->playerCurrentHealth));

    m_MonsterHealthText.setFontSize(60);
    m_MonsterHealthText.setText(
        L10n::monsterHealth +
        std::to_string(this->gameState->fight->currentHealth));

    this->gameState->fight->onFightBegin();
    this->player->onFightBegin();
}

void FightScreen::onRender() {
    background.renderFullscreen();

    int monsterXPos = 1;
    if (!playerTurn && !justShown)
        monsterXPos--;

    int playerXPos = 3;
    if (playerTurn && !justShown)
        playerXPos++;

    player->render(*gameState, Vec(playerXPos, 4));
    gameState->fight->render(*gameState,
                             Vec(width / 2 / BLOCK_PIXELS + monsterXPos, 4));

    if (!fighting && (player->isFadeOut() || gameState->fight->isFadeOut())) {
        fadeFinished = true;
    }

    Renderer::getInstance().selectDrawColor(0, 0, 0, 0xaa);
    Renderer::getInstance().drawRectangle(
        {Vec(0, height - height / 5), Vec(width, height / 5)}, true);

    if (gameState->playerCurrentHealth > 0) {
        stats->render(*gameState, Vec(0, height / BLOCK_PIXELS - 1), false);
    }

    m_PlayerHealthText.render(
        Vec(width - m_PlayerHealthText.getBoxSize().x - 15,
            height - m_PlayerHealthText.getBoxSize().y - 15));

    m_MonsterHealthText.render(
        Vec(width - m_MonsterHealthText.getBoxSize().x - 15,
            height - m_MonsterHealthText.getBoxSize().y - 15 -
                m_PlayerHealthText.getBoxSize().y));
}

void FightScreen::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                navigationDestination =
                    std::make_unique<ResumeMenu>(width, height);
                break;
            case SDLK_RETURN:
            case SDLK_SPACE:
                if (!justShown && fighting) {
                    attack();
                } else if (justShown) {
                    justShown = false;
                    playerTurn = rand() % 2;
                }
                break;
        }
    }
}

bool FightScreen::popSelf() { return fadeFinished; }

FightScreen::~FightScreen() {
    player->onFightEnd();
    if (gameState->weapon != nullptr) {
        gameState->weapon->onFightEnd();
    }
    gameState->fight->onFightEnd();
    gameState->fight = nullptr;
}

void FightScreen::attack() {
    playerTurn = !playerTurn;

    if (playerTurn) {
        if (gameState->weapon != nullptr) {
            gameState->fight->currentHealth -=
                gameState->weapon->getDamage() + gameState->playerDefaultDamage;
        } else {
            gameState->fight->currentHealth -= gameState->playerDefaultDamage;
        }
    } else {
        gameState->playerCurrentHealth -= gameState->fight->getDamage();
    }
    if (gameState->playerCurrentHealth <= 0) {
        gameState->playerCurrentHealth = 0;
        player->fadeOut();
        if (gameState->weapon != nullptr) {
            gameState->weapon->fadeOut();
        }
        fighting = false;
    } else if (gameState->fight->currentHealth <= 0) {
        gameState->fight->currentHealth = 0;
        gameState->fight->fadeOut();
        fighting = false;
    }

    m_PlayerHealthText.setText(L10n::yourHealth +
                               std::to_string(gameState->playerCurrentHealth));

    m_MonsterHealthText.setText(
        L10n::monsterHealth + std::to_string(gameState->fight->currentHealth));
}
