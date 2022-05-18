#ifndef TPOHB_MENU_H
#define TPOHB_MENU_H

#include "../Screen.h"
#include "MenuItem.h"

#include "../Dialog.h"
#include "../render/Texture.h"
#include <memory>
#include <vector>

class Menu : public Screen {
  public:
    void onEvent(SDL_Event event) override;

    void onRender() override;

    bool shouldPopSelf() override;

  protected:
    Menu(int screenWidth, int screenHeight);

    bool m_IsUserInMenu = true;

    std::vector<std::unique_ptr<MenuItem>> m_MenuItems;

    virtual void onItemSelected(int activeIndex) = 0;

    virtual void onEscapePressed() = 0;

    virtual int getItemsTopPadding() const;

  private:
    int m_ActiveItemIndex = 0;
    Texture m_BackdropTexture;
};

#endif // TPOHB_MENU_H
