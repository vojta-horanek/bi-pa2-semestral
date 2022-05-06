#ifndef TPOHB_MENUITEM_H
#define TPOHB_MENUITEM_H

#include "Vec.h"
#include "Texture.h"

class MenuItem {
private:
    Texture inactive;
    Texture active;

    const int renderScale = 3;
    const int height = 24;
    const int width = 80;
protected:
    MenuItem(Texture inactive, Texture active);

public:

    virtual ~MenuItem();

    enum class Item {
        NEW, LOAD, QUIT, RESUME, MAIN_MENU
    };

    virtual Item getType() = 0;

    void render(Vec position);

    void renderActive(Vec position);

    Vec getDestinationPosition(int position, int itemCount, int screenWidth, int screenHeight) const;
};


#endif //TPOHB_MENUITEM_H
