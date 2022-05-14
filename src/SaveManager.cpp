#include "SaveManager.h"

#include <fstream>

bool SaveManager::fileExists(const std::string &path) {
    std::ifstream file(path);
    return file.good();
}

std::string SaveManager::getSaveFilePath() {
    for (size_t i = 0; i < sizeof(commonSavePaths) / sizeof(commonSavePaths[0]); i++) {
        if (fileExists(commonSavePaths[i]))
            return commonSavePaths[i];
    }

    return "";
}

Result SaveManager::saveGame(const std::string &saveFilePath, const std::string &mapFilePath,
                             std::shared_ptr<GameState> gameState) {

    std::ofstream saveFile(saveFilePath);

    if (!saveFile.good())
        return Result::error("Cannot create save file: " + saveFilePath);

    std::map<EntityManager::Type, int> types = EntityManager::createDefinitions();

    // Write definitions
    writeSection(
        SaveParserState(SaveParserState::Value::define), saveFile,
        [&types](std::ostream &ostream) { EntityManager::printDefinitions(types, ostream); });

    // Write map file
    writeSection(SaveParserState(SaveParserState::Value::mapfile), saveFile,
                 [&mapFilePath](std::ostream &ostream) { ostream << mapFilePath << std::endl; });

    // Write inventory TODO
    if (!gameState->inventory.empty()) {
        writeSection(
            SaveParserState(SaveParserState::Value::inventory), saveFile,
            [&mapFilePath](std::ostream &ostream) { ostream << mapFilePath << std::endl; });
    }

    // Write weapon TODO
    if (gameState->weapon != nullptr) {
        writeSection(
            SaveParserState(SaveParserState::Value::weapon), saveFile,
            [&mapFilePath](std::ostream &ostream) { ostream << mapFilePath << std::endl; });
    }

    // Write player health
    writeSection(SaveParserState(SaveParserState::Value::health), saveFile,
                 [&gameState](std::ostream &ostream) {
                     ostream << "SET " << gameState->playerHealth << std::endl;
                 });

    // Write current player health
    writeSection(SaveParserState(SaveParserState::Value::current_health), saveFile,
                 [&gameState](std::ostream &ostream) {
                     ostream << "SET " << gameState->playerCurrentHealth << std::endl;
                 });

    // Write default damage
    writeSection(SaveParserState(SaveParserState::Value::default_damage), saveFile,
                 [&gameState](std::ostream &ostream) {
                     ostream << "SET " << gameState->playerDefaultDamage << std::endl;
                 });

    if (!saveFile.good())
        return Result::error("Failed writing to save file: " + saveFilePath);

    return Result::success();
}

void SaveManager::writeSection(SaveParserState section, std::ostream &output,
                               std::function<void(std::ostream &ostream)> writeFun) {
    const std::string &sectionName = section.toString();
    output << sectionName << std::endl;
    writeFun(output);
    output << "END " << sectionName << std::endl;
}