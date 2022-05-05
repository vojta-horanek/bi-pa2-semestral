#ifndef TPOHB_MENU_H
#define TPOHB_MENU_H

#include "Screen.h"
#include "MenuItem.h"

#include <memory>
#include <vector>

class Menu : public Screen {
private:
    bool userInMenu = true;
    size_t activeItem = 0;
    std::unique_ptr<Screen> nextScreen = nullptr;
    std::vector<std::unique_ptr<MenuItem>> items;

    void onItemSelected();

protected:
    bool shouldContinue() override;

public:
    Menu(int width, int height);

    std::unique_ptr<Screen> getNextScreen() override;

    void onEvent(SDL_Event event) override;

    void onRender() override;
};


#endif //TPOHB_MENU_H
