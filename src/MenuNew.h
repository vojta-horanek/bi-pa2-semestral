#ifndef TPOHB_MENUNEW_H
#define TPOHB_MENUNEW_H

#include "MenuItem.h"

class MenuNew : public MenuItem {
  public:
    MenuNew();
    Item getType() override;
};

#endif // TPOHB_MENUNEW_H
