#ifndef TPOHB_SCREEN_H
#define TPOHB_SCREEN_H

#include "Dialog.h"
#include <SDL_events.h>
#include <memory>
#include <string>
#include <vector>

/**
 * Screen is a base class for any screen of the game
 * It consumes events, handles navigation, showing of a dialog...
 */
class Screen {
  public:
    /**
     * If user requested the application quite
     */
    bool m_ApplicationQuitRequested = false;

    Screen(int screenWidth, int screenHeight);

    virtual ~Screen();

    /**
     * The main loop of the screen. Consumes events, renders the screen and the
     * dialog.
     */
    void onLoop();

    /**
     * Called when the screen should render itself
     */
    virtual void onRender() = 0;

    /**
     * Receive an event from SDL. SDL_Quit events are not sent, they are
     * consumed by onLoop already.
     * @param event an event from SDL
     */
    virtual void onEvent(SDL_Event event) = 0;

    /**
     * The screen can navigate to a different screen if this functions returns
     * it. Nothing happens if the return value is nullptr. When navigating, the
     * new screen is added to the front backstack.
     * @return the screen to be navigated to, nullptr for no navigation
     */
    std::unique_ptr<Screen> getNavigationDestination();

    /**
     * The screen can request itself to be popped from the backstack.
     * This causes the application to navigate back to the previous screen.
     * If no screen was set, the application terminates.
     * @return whether this screen should be popped
     */
    virtual bool shouldPopSelf();

    /**
     * The screen can request the navigation backstack to be cleared.
     * If no navigation destination is set, this will cause the application to
     * terminate.
     * @return if the backstack should be cleared
     */
    virtual bool shouldClearBackStack();

    /**
     * Called when the backstack resumes to the screen
     */
    virtual void onResume();

  protected:
    std::unique_ptr<Screen> m_NavigationDestination = nullptr;
    int m_ScreenWidth, m_ScreenHeight;
    std::unique_ptr<Dialog> m_Dialog = nullptr;

    /**
     * Show a dialog on top of the screen
     * @param dialog a dialog to be shown
     */
    void showDialog(std::unique_ptr<Dialog> dialog);
};

#endif // TPOHB_SCREEN_H
