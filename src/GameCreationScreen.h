#ifndef TPOHB_GAMECREATIONSCREEN_H
#define TPOHB_GAMECREATIONSCREEN_H

#include "Screen.h"
#include "Text.h"
#include "Texture.h"
#include "entity/Player.h"
#include <SDL2/SDL_events.h>
#include <memory>
#include <vector>

class GameCreationScreen : public Screen {
  public:
    GameCreationScreen(int width, int height);

    void onRender() override;

    void onEvent(SDL_Event event) override;

    bool popSelf() override;

    enum class AttributeType { DAMAGE, HEALTH };

    struct Attribute {
        Text m_Text;
        const std::string m_Description;
        int m_Value = 0;
        AttributeType m_Type;
    };

  private:
    Text m_AvailablePointsText;
    Text m_HelpText;
    Text m_TitleText;
    Text m_ContinueText;
    Texture m_BackgroundTexture;
    int m_AvailablePoints = 10;
    size_t m_SelectedAttributeIndex = 0;
    std::vector<Attribute> m_Attributes;
    const int m_Padding = 25;
    bool m_Exit = false;

    void updateTexts();
    void onAttributeIncrease();
    void onAttributeDecrease();
    void openGame();
};

#endif // TPOHB_GAMECREATIONSCREEN_H