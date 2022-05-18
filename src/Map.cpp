#include "Map.h"
#include "entity/Monster.h"
#include "parser/MapFileParser.h"
#include "render/Vec.h"
#include "utils/StringUtils.h"
#include <fstream>
#include <iostream>
#include <string>

bool Map::tryNavigateToSection(Vec playerDirection) {
    // If player is going up/down its direction is negative/positive. Multiply
    // by -1 to convert to map coordinates
    playerDirection.y *= -1;
    Vec newSection = m_CurrentSectionIt->first + playerDirection;
    auto it = m_Sections.find(newSection);
    if (it != m_Sections.end()) {
        m_CurrentSectionIt = it;
        return true;
    } else {
        return false;
    }
}

MapSection &Map::getCurrentSection() {
    assert(m_CurrentSectionIt != m_Sections.end());
    return m_CurrentSectionIt->second;
}

Result Map::saveToFile(const std::string &path, const GameState &gameState) {
    std::ofstream saveFile(path);

    if (!saveFile.good())
        return Result::error("Cannot create map file: " + path);

    std::map<EntityType, int> types = EntityManager::createDefinitions();

    // Write definitions
    writeFileSection(MapParserState(MapParserState::value_type::define), saveFile,
                     [&types](std::ostream &ostream) {
                         EntityManager::printDefinitions(types, ostream);
                     });

    // Write sections
    writeFileSection(MapParserState(MapParserState::value_type::sections), saveFile,
                     [&](std::ostream &ostream) {
                         for (const auto &[position, section]: m_Sections) {
                             section.writeToStream(ostream, types, position);
                         }
                     });

    // Write default section
    writeFileSection(MapParserState(MapParserState::value_type::default_section),
                     saveFile, [&](std::ostream &ostream) {
                ostream << "SET " << m_CurrentSectionIt->first << std::endl;
            });

    // Write player postion
    writeFileSection(MapParserState(MapParserState::value_type::player), saveFile,
                     [&gameState](std::ostream &ostream) {
                         ostream << "SET " << gameState.m_PlayerPosition
                                 << std::endl;
                     });

    // Write monsters
    writeFileSection(MapParserState(MapParserState::value_type::monsters), saveFile,
                     [&](std::ostream &ostream) {
                         for (const auto &[position, section]: m_Sections) {
                             section.writeMovingEntities(ostream, types, position);
                         }
                     });

    if (!saveFile.good())
        return Result::error("Failed writing to map file: " + path);

    return Result::success();
}

std::shared_ptr<Map> Map::loadFromFile(const std::string &fileName,
                                       GameState &gameState, int blocksWidth,
                                       int blocksHeight) {

    std::ifstream mapFile(fileName);
    if (!mapFile)
        throw std::invalid_argument("Could not open file " + fileName);

    int lineNum = 0;

    MapFileParser parser(blocksWidth, blocksHeight);

    std::string line;

    while (std::getline(mapFile, line)) {
        lineNum++;
        StringUtils::trim(line);

        auto result = parser.parseNextLine(line);

        if (result.m_isError) {
            std::cerr << "Error while parsing " << fileName << ". " << std::endl
                      << "Occurred on line " << lineNum
                      << " with error:" << std::endl
                      << "\t" << result.m_ErrorText << std::endl
                      << "The invalid line:" << std::endl
                      << "\t" << line << std::endl;
            throw std::invalid_argument("Error while loading map: " +
                                        result.m_ErrorText);
        }
    }

    auto parsingResult = parser.areAllValuesSet();

    if (parsingResult.m_isError) {
        throw std::invalid_argument(
            "Some values were not set in the map file: " +
            parsingResult.m_ErrorText);
    }

    GameState newGameState = parser.getState();

    // Update game state values
    gameState.m_PlayerPosition = newGameState.m_PlayerPosition;

    return parser.m_Map;
}

void Map::writeFileSection(
    const MapParserState &section, std::ostream &output,
    const std::function<void(std::ostream &ostream)> &writeFun) {
    const std::string &sectionName = section.toString();
    output << sectionName << std::endl;
    writeFun(output);
    output << "END " << sectionName << std::endl;
}