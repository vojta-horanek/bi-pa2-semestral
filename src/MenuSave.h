#ifndef TPOHB_MENUSAVE_H
#define TPOHB_MENUSAVE_H

#include "MenuItem.h"

class MenuSave : public MenuItem {
  public:
    MenuSave();
    Item getType() override;
};

#endif // TPOHB_MENUSAVE_H
