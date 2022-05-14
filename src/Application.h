#ifndef TPOHB_APPLICATION_H
#define TPOHB_APPLICATION_H

#include "Screen.h"
#include "Window.h"

#include <memory>
#include <stack>
#include <string>
#include <vector>

class Application {
  private:
    Window window;
    std::stack<std::unique_ptr<Screen>> backstack;

  public:
    Application();

    int run(const std::vector<std::string> &args);

    void popBackStack();

    void navigateTo(std::unique_ptr<Screen> destination,
                    const std::vector<std::string> &args);

    void clearBackStack();
};

#endif // TPOHB_APPLICATION_H
