#include <iostream>
#include <cassert>

#include "../Map.h"
#include "../utils/Constants.h"
#include "../Window.h"
#include "../Application.h"

bool mapTest(const std::string &path) {
    GameState gs;
    try {
        if (Map::loadFromFile(path, gs, WINDOW_WIDTH, WINDOW_HEIGHT - 1)) {
            return true;
        }
        return false;
    } catch (...) {
        return false;
    }
}

void testMaps() {
    assert(!mapTest(""));
    assert(!mapTest("i don't exist"));
    assert(mapTest("examples/map"));
    assert(mapTest("examples/save_manual_map"));

    assert(!mapTest("src/test/maps/bad_map"));
    assert(!mapTest("src/test/maps/bad_map2"));
    assert(!mapTest("src/test/maps/bad_map3"));
    assert(!mapTest("src/test/maps/bad_map4"));
    assert(!mapTest("src/test/maps/bad_map5"));
    assert(!mapTest("src/test/maps/bad_map6"));
    assert(!mapTest("src/test/maps/bad_map7"));
    assert(!mapTest("src/test/maps/bad_map8"));
    assert(!mapTest("src/test/maps/bad_map9"));
}

#ifdef TEST

int main(int argc, char **argv) {
    std::cout << "Running tests." << std::endl;

    Application app;
    Window w("Tests");

    std::cout << "Testing maps." << std::endl;
    testMaps();


    std::cout << "All test succeeded." << std::endl;

}

#endif