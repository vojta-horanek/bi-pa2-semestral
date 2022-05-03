#include "Map.h"
#include "StringUtils.h"
#include "MapFileParser.h"
#include <iostream>
#include <string>
#include <algorithm>

bool Map::tryNavigateToSection(Vec inPlayerDirection) {
    // If player is going up/down its direction is negative/positive. Multiply by -1 to convert to map coordinates
    inPlayerDirection.y *= -1;
    Vec newSection = currentSection->first + inPlayerDirection;
    auto it = sections.find(newSection);
    if (it != sections.end()) {
        currentSection = it;
        return true;
    } else {
        return false;
    }
}

MapSection &Map::getCurrentSection() {
    assert(currentSection != sections.end());
    return currentSection->second;
}

Map Map::loadFromFile(const std::string &fileName, GameState &gameState) {

    std::ifstream mapFile(fileName);
    if (!mapFile) throw std::invalid_argument("Could not open file " + fileName);

    int lineNum = 0;

    MapFileParser parser;

    std::string line;

    bool isError = false;

    while (std::getline(mapFile, line)) {
        lineNum++;
        StringUtils::trim(line);

        auto result = parser.parseNextLine(line);

        if (result.isError) {
            std::cerr << "Error while parsing " << fileName << ". " << std::endl <<
                      "Occurred on line " << lineNum << " with error:" << std::endl <<
                      "\t" << result.errorText << std::endl <<
                      "The invalid line:" << std::endl <<
                      "\t" << line << std::endl;
            isError = true;
            break;
        }

    }

    mapFile.close();

    if (isError) throw std::invalid_argument("Map could not be loaded from file");

    GameState newGameState = parser.getState();

    // Update game state values
    gameState.playerPosition = newGameState.playerPosition;

    return std::move(parser.getMap());
}
