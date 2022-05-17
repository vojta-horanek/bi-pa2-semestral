#include "SaveFileParser.h"
#include "../EntityManager.h"
#include "../utils/StringUtils.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

SaveFileParser::SaveFileParser() {}

Result SaveFileParser::parseNextLine(const std::string &line) {

    if (line.empty() || line[0] == ';')
        return Result::success();

    std::istringstream lineStream(line);

    SaveParserState possibleNewState = SaveParserState::fromString(line);
    if (possibleNewState != SaveParserState::value_type::invalid) {
        if (currentState == SaveParserState::value_type::none) {
            currentState.set(possibleNewState);
            return Result::success();
        } else {
            return Result::error("Unexpected state change");
        }
    } else if (currentState == SaveParserState::value_type::none) {
        return Result::error("Unexpected token");
    }

    // Line begins with END
    if (line.rfind("END", 0) == 0) {
        std::istringstream tmpStream(line);
        std::string end, what, current = currentState.toString();
        tmpStream >> end >> what;
        if (what == current) {
            currentState.reset();
            return Result::success();
        } else {
            return Result::error("Was in " + current + " but tried to end " +
                                 what);
        }
    }

    if (currentState == SaveParserState::value_type::define) {
        int number = -1;
        std::string entityName;

        lineStream >> number >> entityName;
        EntityType type = EntityManager::getType(entityName);

        if (type != EntityType::INVALID && number >= 0 && lineStream) {
            types[number] = type;
        } else {
            return Result::error("Invalid definition");
        }
    } else if (currentState == SaveParserState::value_type::health) {
        auto setHealth = readIntCommand(line, "SET");
        if (setHealth.first.isError || setHealth.second < 0)
            return setHealth.first;
        playerHealth = setHealth.second;
    } else if (currentState == SaveParserState::value_type::current_health) {
        auto setHealth = readIntCommand(line, "SET");
        if (setHealth.first.isError || setHealth.second < 0)
            return setHealth.first;
        playerCurrentHealth = setHealth.second;
    } else if (currentState == SaveParserState::value_type::default_damage) {
        auto defaultDamage = readIntCommand(line, "SET");
        if (defaultDamage.first.isError || defaultDamage.second < 0)
            return defaultDamage.first;
        playerDefaultDamage = defaultDamage.second;
    } else if (currentState == SaveParserState::value_type::weapon) {
        auto weaponSet = readIntCommand(line, "SET");
        if (weaponSet.first.isError)
            return weaponSet.first;

        auto it = types.find(weaponSet.second);

        if (it == types.end())
            return Result::error("Invalid entity type: " +
                                 std::to_string(weaponSet.second));

        auto weaponEntity = EntityManager::getWeapon(it->second);

        if (weaponEntity == nullptr)
            return Result::error("Entity is not a weapon: " +
                                 std::to_string(weaponSet.second));

        weapon = std::move(weaponEntity);
    } else if (currentState == SaveParserState::value_type::mapfile) {
        if (!mapFilePath.empty())
            return Result::success();

        std::ifstream mapFile(line);
        if (!mapFile.good()) {
            std::cout << "INFO: map file `" << line
                      << "` does not exist. Trying next one." << std::endl;
            return Result::success();
        }
        mapFilePath = line;
    } else if (currentState == SaveParserState::value_type::inventory) {
        auto inventoryAdd = readIntCommand(line, "ADD");
        if (inventoryAdd.first.isError)
            return inventoryAdd.first;

        auto it = types.find(inventoryAdd.second);

        if (it == types.end())
            return Result::error("Invalid entity type: " +
                                 std::to_string(inventoryAdd.second));

        auto pickupEntity = EntityManager::getPickupEntity(it->second);

        if (pickupEntity == nullptr)
            return Result::error("Entity is not a pickup entity: " +
                                 std::to_string(inventoryAdd.second));

        inventory.emplace_back(std::move(pickupEntity));
    }

    return Result::success();
}

std::pair<Result, int>
SaveFileParser::readIntCommand(const std::string &line,
                               const std::string &expectedCommnad) {
    std::istringstream lineStream(line);
    std::string command;
    int number;
    lineStream >> command >> number;
    if (!lineStream) {
        return {Result::error("Cannot parse command `" + line + '`'), -1};
    }
    if (command != expectedCommnad) {
        return {Result::error("Command not supported `" + command +
                              "`, expected `" + expectedCommnad + '`'),
                -1};
    }

    return {Result::success(), number};
}

Result SaveFileParser::areAllValuesSet() const {

    if (mapFilePath.empty())
        return Result::error("No valid map file path set");

    if (playerHealth == -1)
        return Result::error("Player health not set");

    if (playerCurrentHealth == -1)
        return Result::error("Current player health not set");

    if (playerDefaultDamage == -1)
        return Result::error("Player default damage not set");

    if (playerCurrentHealth > playerHealth)
        return Result::error(
            "Players current health cannot be higher than their maxium health");

    return Result::success();
}

Result SaveFileParser::loadSaveFromFile(const std::string &fileName) {
    std::ifstream saveFile(fileName);
    if (!saveFile)
        throw std::invalid_argument("Could not open file " + fileName);

    int lineNum = 0;

    std::string line;

    bool isError = false;

    while (std::getline(saveFile, line)) {
        lineNum++;
        StringUtils::trim(line);

        auto result = parseNextLine(line);

        if (result.isError) {
            std::cerr << "Error while parsing " << fileName << ". " << std::endl
                      << "Occurred on line " << lineNum
                      << " with error:" << std::endl
                      << "\t" << result.errorText << std::endl
                      << "The invalid line:" << std::endl
                      << "\t" << line << std::endl;
            isError = true;
            break;
        }
    }

    if (isError)
        return Result::error("Save could not be loaded from file");

    Result parsingResult = areAllValuesSet();

    if (parsingResult.isError)
        return Result::error(
            "Some required values were not set in the save file: " +
            parsingResult.errorText);

    return Result::success();
}

std::string SaveFileParser::getMapFilePath() const {
    assert(!mapFilePath.empty());
    return mapFilePath;
}

int SaveFileParser::getPlayerHealth() const { return playerHealth; }

int SaveFileParser::getPlayerCurrentHealth() const {
    return playerCurrentHealth;
}

int SaveFileParser::getPlayerDefaultDamage() const {
    return playerDefaultDamage;
}

std::vector<std::unique_ptr<PickupEntity>> SaveFileParser::getInventory() {
    return std::move(inventory);
}

std::unique_ptr<Weapon> SaveFileParser::getWeapon() {
    return std::move(weapon);
}