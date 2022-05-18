#include "SaveManager.h"

#include <fstream>

const std::string SaveManager::s_CommonSavePaths[] = {
        "examples/save_manual", "../examples/save_manual"};

const std::string SaveManager::s_NewGamePaths[] = {
        "assets/new_games/new_game_save", "new_games/new_game_save"};

bool SaveManager::fileExists(const std::string &path) {
    std::ifstream file(path);
    return file.good();
}

std::string SaveManager::getSaveFilePath(bool mustExist) {
    for (const auto &s_CommonSavePath: s_CommonSavePaths) {
        if (!mustExist || fileExists(s_CommonSavePath))
            return s_CommonSavePath;
    }

    return "";
}

std::string SaveManager::getNewGameFilePath() {
    for (const auto &s_NewGamePath: s_NewGamePaths) {
        if (fileExists(s_NewGamePath))
            return s_NewGamePath;
    }

    return "";
}

Result SaveManager::saveGame(const std::string &saveFilePath,
                             const std::string &mapFilePath,
                             const GameState &gameState) {

    std::ofstream saveFile(saveFilePath);

    if (!saveFile.good())
        return Result::error("Cannot create save file: " + saveFilePath);

    std::map<EntityType, int> types = EntityManager::createDefinitions();

    // Write definitions
    writeSection(SaveParserState(SaveParserState::value_type::define), saveFile,
                 [&types](std::ostream &ostream) {
                     EntityManager::printDefinitions(types, ostream);
                 });

    // Write map file
    writeSection(SaveParserState(SaveParserState::value_type::mapfile),
                 saveFile, [&mapFilePath](std::ostream &ostream) {
                ostream << mapFilePath << std::endl;
            });

    // Write m_Inventory
    if (!gameState.m_Inventory.empty()) {
        writeSection(SaveParserState(SaveParserState::value_type::inventory),
                     saveFile, [&gameState, &types](std::ostream &ostream) {
                    for (const auto &item: gameState.m_Inventory) {
                        ostream << "ADD " << types[item->getType()]
                                << std::endl;
                    }
                });
    }

    // Write weapon
    if (gameState.m_Weapon != nullptr) {
        writeSection(SaveParserState(SaveParserState::value_type::weapon),
                     saveFile, [&gameState, &types](std::ostream &ostream) {
                    ostream << "SET "
                            << types[gameState.m_Weapon->getType()]
                            << std::endl;
                });
    }

    // Write player health
    writeSection(SaveParserState(SaveParserState::value_type::health), saveFile,
                 [&gameState](std::ostream &ostream) {
                     ostream << "SET " << gameState.m_PlayerMaxHealth
                             << std::endl;
                 });

    // Write current player health
    writeSection(SaveParserState(SaveParserState::value_type::current_health),
                 saveFile, [&gameState](std::ostream &ostream) {
                ostream << "SET " << gameState.m_PlayerCurrentHealth
                        << std::endl;
            });

    // Write default damage
    writeSection(SaveParserState(SaveParserState::value_type::default_damage),
                 saveFile, [&gameState](std::ostream &ostream) {
                ostream << "SET " << gameState.m_PlayerDefaultDamage
                        << std::endl;
            });

    if (!saveFile.good())
        return Result::error("Failed writing to save file: " + saveFilePath);

    return Result::success();
}

void SaveManager::writeSection(
        const SaveParserState &section, std::ostream &output,
        const std::function<void(std::ostream &ostream)> &writeFun) {
    const std::string &sectionName = section.toString();
    output << sectionName << std::endl;
    writeFun(output);
    output << "END " << sectionName << std::endl;
}