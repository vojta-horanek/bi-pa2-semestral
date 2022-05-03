#include "MapFileParser.h"

Result MapFileParser::parseNextLine(const std::string &line) {

    std::istringstream lineStream(line);

    if (line.empty() || line[0] == ';') return Result::success();

    State possibleNewState = State::fromString(line);
    if (possibleNewState != State::invalid) {
        if (currentState == State::none) {
            currentState.set(possibleNewState);
            return Result::success();
        } else {
            return Result::error("Unexpected state change");
        }
    } else if (currentState == State::none) {
        return Result::error("Unexpected token");
    }

    // Line begins with END
    if (line.rfind("END", 0) == 0) {
        std::istringstream tmpStream(line);
        std::string end, what, current = currentState.toString();
        tmpStream >> end >> what;
        if (what == current) {
            if (currentState == State::section) {
                currentState.set(State::sections);
            } else {
                currentState.reset();
            }
            return Result::success();
        } else {
            return Result::error("Was in " + current + " but tried to end " + what);
        }
    }

    if (currentState == State::player) {
        auto result = readSetCommand(line);
        if (result.first.isError) return result.first;
        gameState.playerPosition = result.second;
    } else if (currentState == State::default_section) {

        auto result = readSetCommand(line);
        if (result.first.isError) return result.first;

        map.currentSection = map.sections.find(result.second);

        if (map.currentSection == map.sections.end()) {
            std::stringstream str;
            str << "Cannot find section with position " << result.second;
            return Result::error(str.str());
        }

    } else if (currentState == State::sections) {

        std::string command;
        int x, y, background = -1;
        lineStream >> command >> x >> y >> background;
        if (command != "SECTION" || !lineStream) {
            return Result::error("Invalid syntax");
        }

        currentState.set(State::section);

        auto backgroundType = types.find(background);

        if (backgroundType == types.end()) {
            return Result::error("Unknown entity type");
        }

        auto back = typeToNewEntity(backgroundType->second);
        auto insert = map.sections.emplace(
                Vec(x, y),
                MapSection(GAME_WIDTH, GAME_HEIGHT, std::move(back)) // TODO...
        );
        if (!insert.second) {
            return Result::error("Could not create a section");
        }

        currentSection = insert.first;
    } else if (currentState == State::section) {

        std::vector<std::unique_ptr<Entity>> row;
        row.reserve(currentSection->second.width);

        std::string entityString;
        // For every space separated string
        while (std::getline(lineStream, entityString, ' ')) {

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
                row.emplace_back(std::move(typeToNewEntity(it->second)));
            }
        }

        currentSection->second.entities.emplace_back(std::move(row));

    } else if (currentState == State::define) {

        int number = -1;
        std::string entityName;

        lineStream >> number >> entityName;
        EntityType type = typeFromString(entityName);

        if (type != INVALID && number >= 0 && lineStream) {
            types[number] = type;
        } else {
            return Result::error("Invalid definition");
        }
    }
    return Result::success();
}

Map MapFileParser::getMap() {
    return std::move(map);
}

GameState MapFileParser::getState() {
    return std::move(gameState);
}

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

