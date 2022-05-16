#include "MessageDialog.h"
#include <iostream>
#include "resources/strings/L10n.h"

MessageDialog::MessageDialog(int screenWidth, int screenHeight,
                             const std::string &text)
    : Dialog(screenWidth, screenHeight),
      m_Text(text + "\n\n" + L10n::pressKeyToHide) {

    m_Text.setWrapWidth(m_Width - m_TextPadding);

    // Change text size to wrap around dialog max size, limit the font size to 10pt at least
    while (m_Text.getBoxSize().y > (m_Height - 2 * m_TextPadding) &&
           m_Text.getFontSize() >= 10) {
        m_Text.setFontSize(m_Text.getFontSize() - 1);
    }

    if (m_Text.getBoxSize().y > (m_Height - 2 * m_TextPadding)) {
        std::cerr << "Could not wrap text to dialog, overflowing" << std::endl;
    }

    // Set wrap dialog size to text if text is smaller than dialog
    m_Height = m_Text.getBoxSize().y + m_TextPadding * 2;
    m_Width = m_Text.getBoxSize().x + m_TextPadding * 2;
}

void MessageDialog::onRender() {
    Dialog::onRender();
    m_Text.render(getDialogPosition() + m_TextPadding);
}

void MessageDialog::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYUP) {
        m_isVisible = false;
    }
}