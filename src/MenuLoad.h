#ifndef TPOHB_MENULOAD_H
#define TPOHB_MENULOAD_H

#include "MenuItem.h"

class MenuLoad : public MenuItem {
  public:
    MenuLoad();
    Item getType() override;
};

#endif // TPOHB_MENULOAD_H
