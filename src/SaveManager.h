#ifndef TPOHB_SAVEMANAGER_H
#define TPOHB_SAVEMANAGER_H

#include "GameState.h"
#include "parser/SaveFileParser.h"
#include "utils/Result.h"
#include <functional>
#include <memory>
#include <ostream>

class SaveManager {
  public:
    static std::string getSaveFilePath();

    static std::string getNewGameFilePath();

    Result saveGame(const std::string &saveFilePath,
                    const std::string &mapFilePath, const GameState &gameState);

  private:
    static const std::string s_CommonSavePaths[];
    static const std::string s_NewGamePaths[];

    static bool fileExists(const std::string &path);

    void writeSection(SaveParserState section, std::ostream &output,
                      std::function<void(std::ostream &ostream)> writeFun);
};

#endif // TPOHB_SAVEMANAGER_H