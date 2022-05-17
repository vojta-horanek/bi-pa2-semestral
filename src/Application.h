#ifndef TPOHB_APPLICATION_H
#define TPOHB_APPLICATION_H

#include "Screen.h"
#include "Window.h"

#include <memory>
#include <stack>
#include <string>
#include <vector>

class Application {
  public:
    Application();

    ~Application();

    int run();

    void popBackStack();

    void navigateTo(std::unique_ptr<Screen> destination);

    void clearBackStack();

  private:
    Window m_Window;
    std::stack<std::unique_ptr<Screen>> m_Backstack;
};

#endif // TPOHB_APPLICATION_H
