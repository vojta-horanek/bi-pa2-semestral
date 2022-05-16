#ifndef TPOHB_GAMECREATIONSCREEN_H
#define TPOHB_GAMECREATIONSCREEN_H

#include "Screen.h"
#include "Text.h"
#include "entity/Player.h"
#include <SDL2/SDL_events.h>
#include <memory>

class GameCreationScreen : public Screen {
  public:
    GameCreationScreen(int width, int height);

    void onRender() override;

    void onEvent(SDL_Event event) override;

  private:
    Text m_AvailablePointsText;
    Text m_HealthText;
    Text m_DamageText;
    Text m_HelpText;
    int m_Health, m_Damage;
    int m_AvailablePoints = 10;
    const int m_Padding = 25;

    void updateTexts();
};

#endif // TPOHB_GAMECREATIONSCREEN_H