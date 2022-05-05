#ifndef TPOHB_APPLICATION_H
#define TPOHB_APPLICATION_H

#include "Window.h"
#include "Screen.h"

#include <vector>
#include <string>
#include <memory>

class Application {
private:
    Window window;
    std::unique_ptr<Screen> currentScreen;
public:

    Application();

    int run(const std::vector<std::string> &args);

};


#endif //TPOHB_APPLICATION_H
