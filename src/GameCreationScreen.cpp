#include "GameCreationScreen.h"
#include "Game.h"
#include "MessageDialog.h"
#include "render/Renderer.h"
#include "resources/strings/L10n.h"
#include "resources/strings/Paths.h"

GameCreationScreen::GameCreationScreen(int width, int height)
    : Screen(width, height), m_HelpText(L10n::createCharacter),
      m_TitleText(L10n::createNewGame),
      m_ContinueText(L10n::toContinuePressEnter),
      m_BackgroundTexture(Paths::Bitmaps::menu_backdrop) {

    m_TitleText.setColor(0, 0, 0);
    m_TitleText.setFontSize(34);
    m_HelpText.setFontSize(26);
    m_HelpText.setWrapWidth(width - m_Padding * 3);
    m_AvailablePointsText.setWrapWidth(width - m_Padding * 3);
    m_AvailablePointsText.setFontSize(26);
    m_ContinueText.setFontSize(30);
    m_ContinueText.setWrapWidth(width - m_Padding * 3);

    m_Attributes.push_back(
        Attribute{Text(), L10n::health, 0, AttributeType::HEALTH});

    m_Attributes.push_back(
        Attribute{Text(), L10n::damage, 0, AttributeType::DAMAGE});

    for (auto &attribute : m_Attributes) {
        attribute.m_Text.setWrapWidth(width - m_Padding * 3);
        attribute.m_Text.setFontSize(40);
    }

    updateTexts();
}

void GameCreationScreen::onRender() {

    m_BackgroundTexture.renderFullscreen();

    m_TitleText.render(
        Vec(m_ScreenWidth / 2 - m_TitleText.getBoxSize().x / 2, m_Padding / 2));

    Renderer::getInstance().selectDrawColor(0x0a, 0x0a, 0x0a, 0x77);
    Renderer::getInstance().drawRectangle(
        {Vec(m_Padding, m_Padding + m_TitleText.getBoxSize().y),
         Vec(m_ScreenWidth - m_Padding * 2,
             m_ScreenHeight - m_Padding * 2 - m_TitleText.getBoxSize().y)},
        true);

    Vec position = Vec(m_Padding * 2, m_Padding * 3);
    m_HelpText.render(position);
    position.y += m_Padding + m_HelpText.getBoxSize().y;
    m_AvailablePointsText.render(position);
    position.y += m_Padding + m_AvailablePointsText.getBoxSize().y;

    for (size_t i = 0; i < m_Attributes.size(); i++) {
        position.x =
            m_ScreenWidth / 2 - m_Attributes[i].m_Text.getBoxSize().x / 2;
        if (m_SelectedAttributeIndex == i) {
            Renderer::getInstance().selectDrawColor(0x00, 0x00, 0x00, 0xaa);
            Renderer::getInstance().drawRectangle(
                {position - 5, m_Attributes[i].m_Text.getBoxSize() + 10}, true);
        }
        m_Attributes[i].m_Text.render(position);
        position.y += m_Padding + m_Attributes[i].m_Text.getBoxSize().y;
    }

    m_ContinueText.render(
        Vec(m_ScreenWidth - m_Padding * 2 - m_ContinueText.getBoxSize().x,
            m_ScreenHeight - m_Padding * 3));
}

void GameCreationScreen::updateTexts() {
    m_AvailablePointsText.setText(L10n::pointsAvailable +
                                  std::to_string(m_AvailablePoints));

    for (auto &attribute : m_Attributes) {
        attribute.m_Text.setText(attribute.m_Description +
                                 std::to_string(attribute.m_Value));
    }
}

void GameCreationScreen::onEvent(SDL_Event event) {

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                if (m_SelectedAttributeIndex == 0)
                    m_SelectedAttributeIndex = m_Attributes.size() - 1;
                else
                    m_SelectedAttributeIndex--;
                break;
            case SDLK_DOWN:
                if (m_SelectedAttributeIndex == m_Attributes.size() - 1)
                    m_SelectedAttributeIndex = 0;
                else
                    m_SelectedAttributeIndex++;
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_RIGHT:
                onAttributeIncrease();
                break;
            case SDLK_LEFT:
                onAttributeDecrease();
                break;
            case SDLK_ESCAPE:
                m_Exit = true;
                break;
            case SDLK_RETURN:
                openGame();
                break;
        }
    }
}

void GameCreationScreen::onAttributeIncrease() {

    if (m_AvailablePoints > 0) {
        m_Attributes[m_SelectedAttributeIndex].m_Value++;
        m_AvailablePoints--;
        updateTexts();
    } else {
        showDialog(std::make_unique<MessageDialog>(
            m_ScreenWidth, m_ScreenHeight, L10n::noPointsAvailable));
    }
}

void GameCreationScreen::onAttributeDecrease() {
    if (m_Attributes[m_SelectedAttributeIndex].m_Value > 0) {
        m_Attributes[m_SelectedAttributeIndex].m_Value--;
        m_AvailablePoints++;
        updateTexts();
    } else {
        showDialog(std::make_unique<MessageDialog>(
            m_ScreenWidth, m_ScreenHeight, L10n::cannotBeLessThanZero));
    }
}

void GameCreationScreen::openGame() {

    if (m_AvailablePoints > 0) {
        showDialog(std::make_unique<MessageDialog>(
            m_ScreenWidth, m_ScreenHeight, L10n::useAllPoints));
        return;
    }

    int health = -1, damage = -1;
    for (const auto &attribute : m_Attributes) {
        switch (attribute.m_Type) {
            case AttributeType::DAMAGE:
                damage = attribute.m_Value;
                break;
            case AttributeType::HEALTH:
                health = attribute.m_Value;
                break;
        }
    }

    if (health == -1 || damage == -1) {
        showDialog(std::make_unique<MessageDialog>(
            m_ScreenWidth, m_ScreenHeight, L10n::unknownError));
        return;
    }

    m_NavigationDestination =
        std::make_unique<Game>(m_ScreenWidth, m_ScreenHeight, damage, health);
    m_Exit = true;
}

bool GameCreationScreen::shouldPopSelf() { return m_Exit; }