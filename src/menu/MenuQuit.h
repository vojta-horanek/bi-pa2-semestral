#ifndef TPOHB_MENUQUIT_H
#define TPOHB_MENUQUIT_H

#include "MenuItem.h"

class MenuQuit : public MenuItem {
  public:
    MenuQuit();

    Item getType() override;
};

#endif // TPOHB_MENUQUIT_H
