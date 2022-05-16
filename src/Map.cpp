#include "Map.h"
#include "MapFileParser.h"
#include "StringUtils.h"
#include "Vec.h"
#include "entity/Monster.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

bool Map::tryNavigateToSection(Vec inPlayerDirection) {
    // If player is going up/down its direction is negative/positive. Multiply
    // by -1 to convert to map coordinates
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

Result Map::saveToFile(const std::string &path, const GameState &gameState) {
    std::ofstream saveFile(path);

    if (!saveFile.good())
        return Result::error("Cannot create map file: " + path);

    std::map<EntityType, int> types = EntityManager::createDefinitions();

    // Write definitions
    writeSection(MapParserState(MapParserState::value_type::define), saveFile,
                 [&types](std::ostream &ostream) {
                     EntityManager::printDefinitions(types, ostream);
                 });

    // Write sections
    writeSection(MapParserState(MapParserState::value_type::sections), saveFile,
                 [&](std::ostream &ostream) {
                     for (const auto &[position, section] : sections) {
                         section.writeToStream(ostream, types, position);
                     }
                 });

    // Write default section
    writeSection(MapParserState(MapParserState::value_type::default_section),
                 saveFile, [&](std::ostream &ostream) {
                     ostream << "SET " << currentSection->first << std::endl;
                 });

    // Write player postion
    writeSection(MapParserState(MapParserState::value_type::player), saveFile,
                 [&gameState](std::ostream &ostream) {
                     ostream << "SET " << gameState.playerPosition << std::endl;
                 });

    // Write monsters
    writeSection(MapParserState(MapParserState::value_type::monsters), saveFile,
                 [&](std::ostream &ostream) {
                     for (const auto &[position, section] : sections) {
                         section.writeMovingEntities(ostream, types, position);
                     }
                 });

    if (!saveFile.good())
        return Result::error("Failed writing to map file: " + path);

    return Result::success();
}

std::shared_ptr<Map> Map::loadFromFile(const std::string &fileName,
                                       GameState &gameState, int width,
                                       int height) {

    std::ifstream mapFile(fileName);
    if (!mapFile)
        throw std::invalid_argument("Could not open file " + fileName);

    int lineNum = 0;

    MapFileParser parser(width, height);

    std::string line;

    while (std::getline(mapFile, line)) {
        lineNum++;
        StringUtils::trim(line);

        auto result = parser.parseNextLine(line);

        if (result.isError) {
            std::cerr << "Error while parsing " << fileName << ". " << std::endl
                      << "Occurred on line " << lineNum
                      << " with error:" << std::endl
                      << "\t" << result.errorText << std::endl
                      << "The invalid line:" << std::endl
                      << "\t" << line << std::endl;
            throw std::invalid_argument("Error while loading map: " +
                                        result.errorText);
        }
    }

    auto parsingResult = parser.areAllValuesSet();

    if (parsingResult.isError) {
        throw std::invalid_argument(
            "Some values were not set in the map file: " +
            parsingResult.errorText);
    }

    GameState newGameState = parser.getState();

    // Update game state values
    gameState.playerPosition = newGameState.playerPosition;

    return parser.map;
}

void Map::writeSection(MapParserState section, std::ostream &output,
                       std::function<void(std::ostream &ostream)> writeFun) {
    const std::string &sectionName = section.toString();
    output << sectionName << std::endl;
    writeFun(output);
    output << "END " << sectionName << std::endl;
}