#ifndef TPOHB_MAPFILEPARSER_H
#define TPOHB_MAPFILEPARSER_H

#include "EntityManager.h"
#include "Map.h"
#include "MapParserState.h"
#include "Result.h"

class MapFileParser {

  private:
    MapParserState currentState;
    Map map;
    std::map<int, EntityManager::Type> types;
    std::map<Vec, MapSection>::iterator currentSection = map.sections.end();
    GameState gameState;
    int width, height;

    static std::pair<Result, Vec> readSetCommand(const std::string &line);

    static std::tuple<Result, Vec, Vec, int>
    readMonsterAddCommand(const std::string &line);

  public:
    MapFileParser(int width, int height);

    Result parseNextLine(const std::string &line);

    Map getMap();

    Result areAllValuesSet() const;

    GameState getState();
};

#endif // TPOHB_MAPFILEPARSER_H
