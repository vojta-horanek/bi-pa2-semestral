#ifndef TPOHB_APPLICATION_H
#define TPOHB_APPLICATION_H

#include "Window.h"

#include <vector>
#include <string>

class Application {
private:
    Window window;
public:

    Application();
    int run(const std::vector<std::string> & args);

};


#endif //TPOHB_APPLICATION_H
