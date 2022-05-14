#ifndef TPOHB_MAINMENU_H
#define TPOHB_MAINMENU_H

#include "Menu.h"

class MainMenu : public Menu {
  private:
    Texture title;
    void onItemSelected(size_t activeIndex) override;
    void onEscapePressed() override;

  public:
    MainMenu(int width, int height);
    void onRender() override;
};

#endif // TPOHB_MAINMENU_H
