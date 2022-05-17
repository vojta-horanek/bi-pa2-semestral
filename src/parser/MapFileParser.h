#ifndef TPOHB_MAPFILEPARSER_H
#define TPOHB_MAPFILEPARSER_H

#include "../EntityManager.h"
#include "../EntityType.h"
#include "../Map.h"
#include "../utils/Result.h"
#include "MapParserState.h"
#include <memory>

class MapFileParser {

  private:
    MapParserState currentState;
    std::map<int, EntityType> types;
    std::map<Vec, MapSection>::iterator currentSection = map->m_Sections.end();
    GameState gameState;
    int width, height;

    static std::pair<Result, Vec> readSetCommand(const std::string &line);

    static std::tuple<Result, Vec, Vec, int>
    readMonsterAddCommand(const std::string &line);

  public:
    MapFileParser(int width, int height);

    std::shared_ptr<Map> map;

    Result parseNextLine(const std::string &line);

    Result areAllValuesSet() const;

    GameState getState();
};

#endif // TPOHB_MAPFILEPARSER_H
