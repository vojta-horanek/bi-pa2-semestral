#include "SaveFileParser.h"
#include "../utils/StringUtils.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

SaveFileParser::SaveFileParser() = default;

Result SaveFileParser::parseNextLine(const std::string &line) {

    if (line.empty() || line[0] == ';')
        return Result::success();

    std::istringstream lineStream(line);

    SaveParserState possibleNewState = SaveParserState::fromString(line);
    if (possibleNewState != SaveParserState::value_type::invalid) {
        if (m_CurrentState == SaveParserState::value_type::none) {
            m_CurrentState.set(possibleNewState);
            return Result::success();
        } else {
            return Result::error("Unexpected state change");
        }
    } else if (m_CurrentState == SaveParserState::value_type::none) {
        return Result::error("Unexpected token");
    }

    // Line begins with END
    if (line.rfind("END", 0) == 0) {
        std::istringstream tmpStream(line);
        std::string end, what, current = m_CurrentState.toString();
        tmpStream >> end >> what;
        if (what == current) {
            m_CurrentState.reset();
            return Result::success();
        } else {
            return Result::error("Was in " + current + " but tried to end " +
                                 what);
        }
    }

    if (m_CurrentState == SaveParserState::value_type::define) {
        int number = -1;
        std::string entityName;

        lineStream >> number >> entityName;
        EntityType type = EntityManager::getType(entityName);

        if (type != EntityType::INVALID && number >= 0 && lineStream) {
            m_Types[number] = type;
        } else {
            return Result::error("Invalid definition");
        }
    } else if (m_CurrentState == SaveParserState::value_type::health) {
        auto setHealth = readIntCommand(line, "SET");
        if (setHealth.first.m_isError || setHealth.second < 0)
            return setHealth.first;
        m_PlayerMaxHealth = setHealth.second;
    } else if (m_CurrentState == SaveParserState::value_type::current_health) {
        auto setHealth = readIntCommand(line, "SET");
        if (setHealth.first.m_isError || setHealth.second < 0)
            return setHealth.first;
        m_PlayerCurrentHealth = setHealth.second;
    } else if (m_CurrentState == SaveParserState::value_type::default_damage) {
        auto defaultDamage = readIntCommand(line, "SET");
        if (defaultDamage.first.m_isError || defaultDamage.second < 0)
            return defaultDamage.first;
        m_PlayerDefaultDamage = defaultDamage.second;
    } else if (m_CurrentState == SaveParserState::value_type::weapon) {
        auto weaponSet = readIntCommand(line, "SET");
        if (weaponSet.first.m_isError)
            return weaponSet.first;

        auto it = m_Types.find(weaponSet.second);

        if (it == m_Types.end())
            return Result::error("Invalid entity type: " +
                                 std::to_string(weaponSet.second));

        auto weaponEntity = EntityManager::getWeapon(it->second);

        if (weaponEntity == nullptr)
            return Result::error("Entity is not a weapon: " +
                                 std::to_string(weaponSet.second));

        m_Weapon = std::move(weaponEntity);
    } else if (m_CurrentState == SaveParserState::value_type::mapfile) {
        if (!m_MapFilePath.empty())
            return Result::success();

        std::ifstream mapFile(line);
        if (!mapFile.good()) {
            std::cout << "INFO: map file `" << line
                      << "` does not exist. Trying next one." << std::endl;
            return Result::success();
        }
        m_MapFilePath = line;
    } else if (m_CurrentState == SaveParserState::value_type::inventory) {
        auto inventoryAdd = readIntCommand(line, "ADD");
        if (inventoryAdd.first.m_isError)
            return inventoryAdd.first;

        auto it = m_Types.find(inventoryAdd.second);

        if (it == m_Types.end())
            return Result::error("Invalid entity type: " +
                                 std::to_string(inventoryAdd.second));

        auto pickupEntity = EntityManager::getPickupEntity(it->second);

        if (pickupEntity == nullptr)
            return Result::error("Entity is not a pickup entity: " +
                                 std::to_string(inventoryAdd.second));

        m_Inventory.emplace_back(std::move(pickupEntity));
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

    if (m_MapFilePath.empty())
        return Result::error("No valid map file path set");

    if (m_PlayerMaxHealth == -1)
        return Result::error("Player health not set");

    if (m_PlayerCurrentHealth == -1)
        return Result::error("Current player health not set");

    if (m_PlayerDefaultDamage == -1)
        return Result::error("Player default damage not set");

    if (m_PlayerCurrentHealth > m_PlayerMaxHealth)
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

        if (result.m_isError) {
            std::cerr << "Error while parsing " << fileName << ". " << std::endl
                      << "Occurred on line " << lineNum
                      << " with error:" << std::endl
                      << "\t" << result.m_ErrorText << std::endl
                      << "The invalid line:" << std::endl
                      << "\t" << line << std::endl;
            isError = true;
            break;
        }
    }

    if (isError)
        return Result::error("Save could not be loaded from file");

    Result parsingResult = areAllValuesSet();

    if (parsingResult.m_isError)
        return Result::error(
            "Some required values were not set in the save file: " +
            parsingResult.m_ErrorText);

    return Result::success();
}

std::string SaveFileParser::getMapFilePath() const {
    assert(!m_MapFilePath.empty());
    return m_MapFilePath;
}

int SaveFileParser::getPlayerHealth() const { return m_PlayerMaxHealth; }

int SaveFileParser::getPlayerCurrentHealth() const {
    return m_PlayerCurrentHealth;
}

int SaveFileParser::getPlayerDefaultDamage() const {
    return m_PlayerDefaultDamage;
}

std::vector<std::unique_ptr<PickupEntity>> SaveFileParser::getInventory() {
    return std::move(m_Inventory);
}

std::unique_ptr<Weapon> SaveFileParser::getWeapon() {
    return std::move(m_Weapon);
}