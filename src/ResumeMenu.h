#ifndef TPOHB_RESUMEMENU_H
#define TPOHB_RESUMEMENU_H

#include "Menu.h"

class ResumeMenu : public Menu {
private:
    bool goToMainMenu = false;
    void onItemSelected(size_t activeIndex) override;
    void onEscapePressed() override;
public:
    ResumeMenu(int width, int height, bool saveEnabled = true);
    bool clearBackStack() override;

};

#endif //TPOHB_RESUMEMENU_H
