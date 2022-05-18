#include "MapFileParser.h"
#include "../entity/Monster.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>

MapFileParser::MapFileParser(int width, int height)
    : m_BlocksWidth(width), m_BlocksHeight(height) {
    m_Map = std::make_shared<Map>();
}

Result MapFileParser::parseNextLine(const std::string &line) {

    if (line.empty() || line[0] == ';')
        return Result::success();

    std::istringstream lineStream(line);

    MapParserState possibleNewState = MapParserState::fromString(line);
    if (possibleNewState != MapParserState::value_type::invalid) {
        if (m_CurrentState == MapParserState::value_type::none) {
            m_CurrentState.set(possibleNewState);
            return Result::success();
        } else {
            return Result::error("Unexpected state change");
        }
    } else if (m_CurrentState == MapParserState::value_type::none) {
        return Result::error("Unexpected token");
    }

    // Line begins with END
    if (line.rfind("END", 0) == 0) {
        std::istringstream tmpStream(line);
        std::string end, what, current = m_CurrentState.toString();
        tmpStream >> end >> what;
        if (what == current) {
            if (m_CurrentState == MapParserState::value_type::section) {
                m_CurrentState.set(MapParserState::value_type::sections);
            } else {
                m_CurrentState.reset();
            }
            return Result::success();
        } else {
            return Result::error("Was in " + current + " but tried to end " +
                                 what);
        }
    }

    if (m_CurrentState == MapParserState::value_type::player) {
        auto result = readSetCommand(line);
        if (result.first.m_isError)
            return result.first;

        if (m_CurrentSectionIt == m_Map->m_Sections.end()) {
            return Result::error(
                "No default map section has been specified yet!");
        }

        if (m_CurrentSectionIt->second.isEdge(result.second)) {
            std::stringstream str;
            str << "Position out of bounds: " << result.second;
            return Result::error(str.str());
        }

        m_GameState.m_PlayerPosition = result.second;
    } else if (m_CurrentState == MapParserState::value_type::default_section) {

        auto result = readSetCommand(line);
        if (result.first.m_isError)
            return result.first;

        m_Map->m_CurrentSectionIt = m_Map->m_Sections.find(result.second);

        if (m_Map->m_CurrentSectionIt == m_Map->m_Sections.end()) {
            std::stringstream str;
            str << "Cannot find section with position " << result.second;
            return Result::error(str.str());
        }

    } else if (m_CurrentState == MapParserState::value_type::sections) {

        std::string command;
        int x, y, background = -1;
        lineStream >> command >> x >> y >> background;
        if (command != "SECTION" || !lineStream) {
            return Result::error("Invalid syntax");
        }

        m_CurrentState.set(MapParserState::value_type::section);

        auto backgroundType = m_Types.find(background);

        if (backgroundType == m_Types.end()) {
            return Result::error("Unknown entity type");
        }

        auto backgroundEntity =
            EntityManager::getEntity(backgroundType->second);

        if (backgroundEntity == nullptr) {
            return Result::error("Invalid background entity");
        }

        auto insert = m_Map->m_Sections.emplace(
            Vec(x, y), MapSection(m_BlocksWidth, m_BlocksHeight,
                                  std::move(backgroundEntity)));

        if (!insert.second) {
            return Result::error("Could not create a section");
        }

        m_CurrentSectionIt = insert.first;
    } else if (m_CurrentState == MapParserState::value_type::section) {

        if (m_CurrentSectionIt->second.m_Entities.size() ==
            (size_t)m_CurrentSectionIt->second.m_BlocksHeight) {
            return Result::error("Unexpected line, height exceeded");
        }

        std::vector<std::unique_ptr<Entity>> row;
        row.reserve(m_CurrentSectionIt->second.m_BlocksWidth);

        std::string entityString;

        int entityRowCount = 0;

        // For every space separated string
        while (std::getline(lineStream, entityString, ' ')) {

            if (entityRowCount == m_CurrentSectionIt->second.m_BlocksWidth) {
                return Result::error("Unexpected entity, width exceeded: " +
                                     entityString);
            }

            int entityIdentifier = -1;
            std::istringstream tmpStream(entityString);
            tmpStream >> entityIdentifier;

            if (!tmpStream) {
                return Result::error("Invalid entity type: " + entityString);
            }

            auto it = m_Types.find(entityIdentifier);
            if (it == m_Types.end()) {
                return Result::error("Could not find a valid entity type: " +
                                     entityString);
            } else {
                row.emplace_back(
                    std::move(EntityManager::getEntity(it->second)));
            }

            entityRowCount++;
        }

        if (entityRowCount < m_BlocksWidth) {
            return Result::error("Missing entities for a complete row!");
        }

        m_CurrentSectionIt->second.m_Entities.emplace_back(std::move(row));

    } else if (m_CurrentState == MapParserState::value_type::define) {

        int number = -1;
        std::string entityName;

        lineStream >> number >> entityName;
        EntityType type = EntityManager::getType(entityName);

        if (type != EntityType::INVALID && number >= 0 && lineStream) {
            m_Types[number] = type;
        } else {
            return Result::error("Invalid definition");
        }
    } else if (m_CurrentState == MapParserState::value_type::monsters) {
        Result result = Result::error();
        Vec position;
        Vec section;
        int entityIdentifier;

        std::tie(result, position, section, entityIdentifier) =
            readMonsterAddCommand(line);

        if (result.m_isError)
            return result;

        auto thisSection = m_Map->m_Sections.find(section);

        if (thisSection == m_Map->m_Sections.end()) {
            std::stringstream str;
            str << "Cannot find section with position " << section;
            return Result::error(str.str());
        }

        if (thisSection->second.isEdge(position)) {
            std::stringstream str;
            str << "Position out of bounds: " << position;
            return Result::error(str.str());
        }

        auto it = m_Types.find(entityIdentifier);
        if (it == m_Types.end())
            return Result::error("Could not find a valid entity type: " +
                                 std::to_string(entityIdentifier));

        auto monster = EntityManager::getMonster(it->second);

        if (monster == nullptr) {
            return Result::error("Entity is not a monster");
        }

        monster->m_Position = position;
        thisSection->second.m_MovingEntities.emplace_back(std::move(monster));
    }
    return Result::success();
}

GameState MapFileParser::getState() { return std::move(m_GameState); }

std::pair<Result, Vec> MapFileParser::readSetCommand(const std::string &line) {
    std::istringstream lineStream(line);
    std::string command;
    int x, y;
    lineStream >> command >> x >> y;
    if (!lineStream) {
        return {Result::error("Cannot parse command `" + line + '`'), Vec()};
    }
    if (command != "SET") {
        return {Result::error("Command not supported `" + command + '`'),
                Vec()};
    }

    return {Result::success(), Vec(x, y)};
}

std::tuple<Result, Vec, Vec, int>
MapFileParser::readMonsterAddCommand(const std::string &line) {
    std::istringstream lineStream(line);
    std::string command;
    int x, y, sectionX, sectionY, type;
    lineStream >> command >> x >> y >> sectionX >> sectionY >> type;
    if (!lineStream) {
        return {Result::error("Cannot parse command `" + line + '`'), Vec(),
                Vec(), type};
    }
    if (command != "ADD") {
        return {Result::error("Command not supported `" + command + '`'), Vec(),
                Vec(), type};
    }

    return {Result::success(), Vec(x, y), Vec(sectionX, sectionY), type};
}

Result MapFileParser::areAllValuesSet() const {
    if (m_Map->m_Sections.empty()) {
        return Result::error("No map sections defined");
    }

    if (m_Map->m_CurrentSectionIt == m_Map->m_Sections.end()) {
        return Result::error("A default section has not been set");
    }

    if (m_GameState.m_PlayerPosition == Vec::max()) {
        return Result::error("Player position has not been set");
    }

    return Result::success();
}