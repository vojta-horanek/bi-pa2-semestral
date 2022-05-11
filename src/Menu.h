#ifndef TPOHB_MENU_H
#define TPOHB_MENU_H

#include "Screen.h"
#include "MenuItem.h"

#include <memory>
#include <vector>

class Menu : public Screen {
private:
    size_t activeItem = 0;
    Texture backdrop;

protected:
    bool userInMenu = true;

    std::vector<std::unique_ptr<MenuItem>> items;

    virtual void onItemSelected(size_t activeIndex) = 0;

    virtual void onEscapePressed() = 0;

    Menu(int width, int height);

public:

    void onEvent(SDL_Event event) override;

    void onRender() override;

    bool popSelf() override;

};


#endif //TPOHB_MENU_H
