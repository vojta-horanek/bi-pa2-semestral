#ifndef TPOHB_SAVEMANAGER_H
#define TPOHB_SAVEMANAGER_H

#include "GameState.h"
#include "Result.h"
#include "SaveFileParser.h"
#include <functional>
#include <memory>
#include <ostream>

class SaveManager {
  private:
    constexpr static const char *commonSavePaths[] = {"examples/save", "../examples/save"};
    static bool fileExists(const std::string &path);
    void writeSection(SaveParserState section, std::ostream &output,
                      std::function<void(std::ostream &ostream)> writeFun);

  public:
    static std::string getSaveFilePath();
    Result saveGame(const std::string &saveFilePath, const std::string &mapFilePath,
                    std::shared_ptr<GameState> gameState);
};

#endif // TPOHB_SAVEMANAGER_H