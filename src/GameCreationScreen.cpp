#include "GameCreationScreen.h"
#include "Renderer.h"
#include "resources/strings/L10n.h"

GameCreationScreen::GameCreationScreen(int width, int height)
    : Screen(width, height), m_HelpText(L10n::createCharacter) {
    updateTexts();
    m_HelpText.setWrapWidth(width - m_Padding);
}

void GameCreationScreen::onRender() {
    Renderer::getInstance().selectDrawColor(0x8e, 0xa3, 0x48, 0xff);
    m_HelpText.render(Vec(m_Padding, m_Padding));

    // TODO
}

void GameCreationScreen::updateTexts() {
    m_AvailablePointsText.setText(
        "You have " + std::to_string(m_AvailablePoints) + " points available.");
}

void GameCreationScreen::onEvent(SDL_Event event) {}