#ifndef TPOHB_MENUMAINMENU_H
#define TPOHB_MENUMAINMENU_H


#include "MenuItem.h"

class MenuMainMenu : public MenuItem {
public:
    MenuMainMenu();
    Item getType() override;
};

#endif //TPOHB_MENUMAINMENU_H
