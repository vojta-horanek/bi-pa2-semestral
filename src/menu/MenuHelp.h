#ifndef TPOHB_MENUHELP_H
#define TPOHB_MENUHELP_H

#include "MenuItem.h"

class MenuHelp : public MenuItem {
  public:
    MenuHelp();

    Item getType() override;
};

#endif // TPOHB_MENULOAD_H
