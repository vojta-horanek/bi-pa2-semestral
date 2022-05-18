#ifndef TPOHB_MAINMENU_H
#define TPOHB_MAINMENU_H

#include "../render/Text.h"
#include "Menu.h"

class MainMenu : public Menu {
public:
    MainMenu(int width, int height);

    void onRender() override;

protected:
    int getItemsTopPadding() const override;

private:
    Text m_TitleText;

    void onItemSelected(int activeIndex) override;

    void onEscapePressed() override;


};

#endif // TPOHB_MAINMENU_H
