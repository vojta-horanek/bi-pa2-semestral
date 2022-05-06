#ifndef TPOHB_APPLICATION_H
#define TPOHB_APPLICATION_H

#include "Window.h"
#include "Screen.h"

#include <vector>
#include <string>
#include <memory>
#include <stack>

class Application {
private:
    Window window;
    std::stack<std::unique_ptr<Screen>> backstack;
public:

    Application();

    int run(const std::vector<std::string> &args);

    void popBackStack();
    void navigateTo(std::unique_ptr<Screen> destination);
    void clearBackStack();

};


#endif //TPOHB_APPLICATION_H
