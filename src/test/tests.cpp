#include <cassert>
#include <iostream>

#include "../Application.h"
#include "../Map.h"
#include "../Window.h"
#include "../parser/SaveFileParser.h"
#include "../utils/Constants.h"

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

bool saveTest(const std::string &path) {
    SaveFileParser saveFileParser;

    Result saveFileResult = saveFileParser.loadSaveFromFile(path);
    if (saveFileResult.m_isError)
        return false;

    return mapTest(saveFileParser.getMapFilePath());
}

void testMaps() {
    assert(!mapTest(""));
    assert(!mapTest("i don't exist"));
    assert(mapTest("examples/map"));

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

void testSaves() {

    assert(!saveTest(""));
    assert(!saveTest("i don't exist"));
    assert(saveTest("examples/save"));
    assert(!saveTest("src/test/saves/bad_save"));
    assert(!saveTest("src/test/saves/bad_save2"));
    assert(!saveTest("src/test/saves/bad_save3"));
    assert(!saveTest("src/test/saves/bad_save4"));
    assert(!saveTest("src/test/saves/bad_save5"));
}

#ifdef TEST

int main(int argc, char **argv) {
    std::cout << "Running tests." << std::endl;

    Application app;
    Window w("Tests");

    std::cout << "Testing maps." << std::endl;
    testMaps();
    std::cout << "OK" << std::endl;

    std::cout << "Testing saves." << std::endl;
    testSaves();
    std::cout << "OK" << std::endl;

    std::cout << "All test succeeded." << std::endl;
}

#endif