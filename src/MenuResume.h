#ifndef TPOHB_MENURESUME_H
#define TPOHB_MENURESUME_H

#include "MenuItem.h"

class MenuResume : public MenuItem {
  public:
    MenuResume();

    Item getType() override;
};

#endif // TPOHB_MENURESUME_H
