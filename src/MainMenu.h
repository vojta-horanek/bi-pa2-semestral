#ifndef TPOHB_MAINMENU_H
#define TPOHB_MAINMENU_H


#include "Menu.h"

class MainMenu : public Menu {

private:
    void onItemSelected(size_t activeIndex) override;
    void onEscapePressed() override;
public:
    MainMenu(int width, int height);

};


#endif //TPOHB_MAINMENU_H
