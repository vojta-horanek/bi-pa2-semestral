#ifndef TPOHB_MENUITEM_H
#define TPOHB_MENUITEM_H

#include "Text.h"
#include "Vec.h"
#include <string>

class MenuItem {
  private:
    Text m_Text;
    const int m_TextPadding = 16;
    Vec getTotalSize() const;

  protected:
    MenuItem(const std::string &text);

  public:
    virtual ~MenuItem();

    enum class Item { NEW, LOAD, QUIT, RESUME, MAIN_MENU, SAVE, HELP };

    virtual Item getType() = 0;

    void render(Vec position);

    void renderActive(Vec position);

    Vec getDestinationPosition(int position, int itemCount, int screenWidth,
                               int screenHeight) const;
};

#endif // TPOHB_MENUITEM_H
