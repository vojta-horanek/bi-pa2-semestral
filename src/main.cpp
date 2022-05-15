#include "resources/strings/L10n.h"

#include "Application.h"
#include <string>
#include <vector>

int main(int argc, char **argv) {
    std::vector<std::string> args;

    for (int arg = 1; arg < argc; arg++) {
        args.emplace_back(argv[arg]);
    }

    Application app;
    return app.run(args);
}
