#ifndef TPOHB_MAINMENU_H
#define TPOHB_MAINMENU_H

#include "../render/Text.h"
#include "Menu.h"

class MainMenu : public Menu {
  private:
    Text m_Title;

    void onItemSelected(size_t activeIndex) override;

    void onEscapePressed() override;

  protected:
    int getItemsTopPadding() const override;

  public:
    MainMenu(int width, int height);

    void onRender() override;
};

#endif // TPOHB_MAINMENU_H
