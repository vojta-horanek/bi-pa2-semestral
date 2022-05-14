#include "SaveManager.h"

#include <fstream>

const std::string SaveManager::commonSavePaths[] = {"examples/save_manual",
                                                    "../examples/save_manual"};

bool SaveManager::fileExists(const std::string &path) {
    std::ifstream file(path);
    return file.good();
}

std::string SaveManager::getSaveFilePath() {
    for (size_t i = 0; i < sizeof(commonSavePaths) / sizeof(commonSavePaths[0]);
         i++) {
        if (fileExists(commonSavePaths[i]))
            return commonSavePaths[i];
    }

    return "";
}

Result SaveManager::saveGame(const std::string &saveFilePath,
                             const std::string &mapFilePath,
                             std::shared_ptr<GameState> gameState) {

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

    // Write inventory
    if (!gameState->inventory.empty()) {
        writeSection(SaveParserState(SaveParserState::value_type::inventory),
                     saveFile, [&gameState, &types](std::ostream &ostream) {
                         for (const auto &item : gameState->inventory) {
                             ostream << "ADD " << types[item->getType()]
                                     << std::endl;
                         }
                     });
    }

    // Write weapon
    if (gameState->weapon != nullptr) {
        writeSection(SaveParserState(SaveParserState::value_type::weapon),
                     saveFile, [&gameState, &types](std::ostream &ostream) {
                         ostream << "SET "
                                 << types[gameState->weapon->getType()]
                                 << std::endl;
                     });
    }

    // Write player health
    writeSection(SaveParserState(SaveParserState::value_type::health), saveFile,
                 [&gameState](std::ostream &ostream) {
                     ostream << "SET " << gameState->playerHealth << std::endl;
                 });

    // Write current player health
    writeSection(SaveParserState(SaveParserState::value_type::current_health),
                 saveFile, [&gameState](std::ostream &ostream) {
                     ostream << "SET " << gameState->playerCurrentHealth
                             << std::endl;
                 });

    // Write default damage
    writeSection(SaveParserState(SaveParserState::value_type::default_damage),
                 saveFile, [&gameState](std::ostream &ostream) {
                     ostream << "SET " << gameState->playerDefaultDamage
                             << std::endl;
                 });

    if (!saveFile.good())
        return Result::error("Failed writing to save file: " + saveFilePath);

    return Result::success();
}

void SaveManager::writeSection(
    SaveParserState section, std::ostream &output,
    std::function<void(std::ostream &ostream)> writeFun) {
    const std::string &sectionName = section.toString();
    output << sectionName << std::endl;
    writeFun(output);
    output << "END " << sectionName << std::endl;
}