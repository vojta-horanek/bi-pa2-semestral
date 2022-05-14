#include "MapFileParser.h"
#include "entity/Monster.h"

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

Result MapFileParser::parseNextLine(const std::string &line) {

    if (line.empty() || line[0] == ';')
        return Result::success();

    std::istringstream lineStream(line);

    MapParserState possibleNewState = MapParserState::fromString(line);
    if (possibleNewState != MapParserState::Value::invalid) {
        if (currentState == MapParserState::Value::none) {
            currentState.set(possibleNewState);
            return Result::success();
        } else {
            return Result::error("Unexpected state change");
        }
    } else if (currentState == MapParserState::Value::none) {
        return Result::error("Unexpected token");
    }

    // Line begins with END
    if (line.rfind("END", 0) == 0) {
        std::istringstream tmpStream(line);
        std::string end, what, current = currentState.toString();
        tmpStream >> end >> what;
        if (what == current) {
            if (currentState == MapParserState::Value::section) {
                currentState.set(MapParserState::Value::sections);
            } else {
                currentState.reset();
            }
            return Result::success();
        } else {
            return Result::error("Was in " + current + " but tried to end " + what);
        }
    }

    if (currentState == MapParserState::Value::player) {
        auto result = readSetCommand(line);
        if (result.first.isError)
            return result.first;

        if (currentSection == map.sections.end()) {
            return Result::error("No default map section has been specified yet!");
        }

        if (currentSection->second.isEdge(result.second)) {
            std::stringstream str;
            str << "Position out of bounds: " << result.second;
            return Result::error(str.str());
        }

        gameState.playerPosition = result.second;
    } else if (currentState == MapParserState::Value::default_section) {

        auto result = readSetCommand(line);
        if (result.first.isError)
            return result.first;

        map.currentSection = map.sections.find(result.second);

        if (map.currentSection == map.sections.end()) {
            std::stringstream str;
            str << "Cannot find section with position " << result.second;
            return Result::error(str.str());
        }

    } else if (currentState == MapParserState::Value::sections) {

        std::string command;
        int x, y, background = -1;
        lineStream >> command >> x >> y >> background;
        if (command != "SECTION" || !lineStream) {
            return Result::error("Invalid syntax");
        }

        currentState.set(MapParserState::Value::section);

        auto backgroundType = types.find(background);

        if (backgroundType == types.end()) {
            return Result::error("Unknown entity type");
        }

        auto backgroundEntity = EntityManager::getEntity(backgroundType->second);

        if (backgroundEntity == nullptr) {
            return Result::error("Invalid background entity");
        }

        auto insert =
            map.sections.emplace(Vec(x, y), MapSection(width, height, std::move(backgroundEntity)));

        if (!insert.second) {
            return Result::error("Could not create a section");
        }

        currentSection = insert.first;
    } else if (currentState == MapParserState::Value::section) {

        if (currentSection->second.entities.size() == (size_t)currentSection->second.height) {
            return Result::error("Unexpected line, height exceeded");
        }

        std::vector<std::unique_ptr<Entity>> row;
        row.reserve(currentSection->second.width);

        std::string entityString;

        int entityRowCount = 0;

        // For every space separated string
        while (std::getline(lineStream, entityString, ' ')) {

            if (entityRowCount == currentSection->second.width) {
                return Result::error("Unexpected entity, width exceeded: " + entityString);
            }

            int entityIdentifier = -1;
            std::istringstream tmpStream(entityString);
            tmpStream >> entityIdentifier;

            if (!tmpStream) {
                return Result::error("Invalid entity type: " + entityString);
            }

            auto it = types.find(entityIdentifier);
            if (it == types.end()) {
                return Result::error("Could not find a valid entity type: " + entityString);
            } else {
                row.emplace_back(std::move(EntityManager::getEntity(it->second)));
            }

            entityRowCount++;
        }

        currentSection->second.entities.emplace_back(std::move(row));

    } else if (currentState == MapParserState::Value::define) {

        int number = -1;
        std::string entityName;

        lineStream >> number >> entityName;
        EntityManager::Type type = EntityManager::getType(entityName);

        if (type != EntityManager::Type::INVALID && number >= 0 && lineStream) {
            types[number] = type;
        } else {
            return Result::error("Invalid definition");
        }
    } else if (currentState == MapParserState::Value::monsters) {
        Result result = Result::error();
        Vec position;
        Vec section;
        int entityIdentifier;

        std::tie(result, position, section, entityIdentifier) = readMonsterAddCommand(line);

        if (result.isError)
            return result;

        auto thisSection = map.sections.find(section);

        if (thisSection == map.sections.end()) {
            std::stringstream str;
            str << "Cannot find section with position " << section;
            return Result::error(str.str());
        }

        if (thisSection->second.isEdge(position)) {
            std::stringstream str;
            str << "Position out of bounds: " << position;
            return Result::error(str.str());
        }

        auto it = types.find(entityIdentifier);
        if (it == types.end())
            return Result::error("Could not find a valid entity type: " +
                                 std::to_string(entityIdentifier));

        auto monster = EntityManager::getMonster(it->second);

        if (monster == nullptr) {
            return Result::error("Entity is not a monster");
        }

        monster->position = position;
        thisSection->second.movingEntities.emplace_back(std::move(monster));
    }
    return Result::success();
}

Map MapFileParser::getMap() { return std::move(map); }

GameState MapFileParser::getState() { return std::move(gameState); }

std::pair<Result, Vec> MapFileParser::readSetCommand(const std::string &line) {
    std::istringstream lineStream(line);
    std::string command;
    int x, y;
    lineStream >> command >> x >> y;
    if (!lineStream) {
        return {Result::error("Cannot parse command `" + line + '`'), Vec()};
    }
    if (command != "SET") {
        return {Result::error("Command not supported `" + command + '`'), Vec()};
    }

    return {Result::success(), Vec(x, y)};
}

std::tuple<Result, Vec, Vec, int> MapFileParser::readMonsterAddCommand(const std::string &line) {
    std::istringstream lineStream(line);
    std::string command;
    int x, y, sectionX, sectionY, type;
    lineStream >> command >> x >> y >> sectionX >> sectionY >> type;
    if (!lineStream) {
        return {Result::error("Cannot parse command `" + line + '`'), Vec(), Vec(), type};
    }
    if (command != "ADD") {
        return {Result::error("Command not supported `" + command + '`'), Vec(), Vec(), type};
    }

    return {Result::success(), Vec(x, y), Vec(sectionX, sectionY), type};
}

MapFileParser::MapFileParser(int width, int height) : width(width), height(height) {}

Result MapFileParser::areAllValuesSet() const {
    if (map.sections.empty()) {
        return Result::error("No map sections defined");
    }

    if (map.currentSection == map.sections.end()) {
        return Result::error("A default section has not been set");
    }

    if (gameState.playerPosition == Vec::max()) {
        return Result::error("Player position has not been set");
    }

    return Result::success();
}

std::string MapParserState::toString() const {
    switch (value) {
        case Value::player:
            return "PLAYER";
        case Value::default_section:
            return "DEFAULT_SECTION";
        case Value::sections:
            return "SECTIONS";
        case Value::section:
            return "SECTION";
        case Value::define:
            return "DEFINE";
        case Value::none:
            return "NONE";
        case Value::monsters:
            return "MONSTERS";
        default:
            throw std::invalid_argument("Unknown state!");
    }
}

void MapParserState::reset() { value = Value::none; }

void MapParserState::set(MapParserState::Value val) { value = val; }

void MapParserState::set(const MapParserState &state) { value = state.value; }

MapParserState::Value MapParserState::get() const { return value; }

MapParserState MapParserState::fromString(const std::string &str) {
    if (str == "PLAYER")
        return MapParserState(Value::player);
    if (str == "DEFAULT_SECTION")
        return MapParserState(Value::default_section);
    if (str == "SECTIONS")
        return MapParserState(Value::sections);
    if (str == "SECTION")
        return MapParserState(Value::section);
    if (str == "DEFINE")
        return MapParserState(Value::define);
    if (str == "MONSTERS")
        return MapParserState(Value::monsters);
    else
        return MapParserState(Value::invalid);
}

bool MapParserState::operator==(const MapParserState &rhs) const { return value == rhs.value; }

bool MapParserState::operator!=(const MapParserState &rhs) const { return !(rhs == *this); }

bool MapParserState::operator==(MapParserState::Value rhs) const { return value == rhs; }

bool MapParserState::operator!=(MapParserState::Value rhs) const { return !(*this == rhs); }

MapParserState::MapParserState(MapParserState::Value value) : value(value) {}

MapParserState::MapParserState() = default;