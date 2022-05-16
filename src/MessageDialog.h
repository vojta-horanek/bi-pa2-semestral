#ifndef TPOHB_MESSAGEDIALOG_H
#define TPOHB_MESSAGEDIALOG_H

#include "Dialog.h"
#include "Text.h"
#include <SDL2/SDL_events.h>

class MessageDialog : public Dialog {
  public:
    MessageDialog(int screenWidth, int screenHeight, const std::string &text);
    void onRender() override;
    void onEvent(SDL_Event event) override;

  private:
    Text m_Text;
    const int m_TextPadding = 25;
};

#endif // TPOHB_MESSAGEDIALOG_H