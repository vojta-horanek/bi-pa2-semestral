#ifndef TPOHB_MAPFILEPARSER_H
#define TPOHB_MAPFILEPARSER_H

#include "../EntityManager.h"
#include "../EntityType.h"
#include "../Map.h"
#include "../utils/Result.h"
#include "MapParserState.h"
#include <memory>

class MapFileParser {

public:
    MapFileParser(int width, int height);

    std::shared_ptr<Map> m_Map;

    Result parseNextLine(const std::string &line);

    Result areAllValuesSet() const;

    GameState getState();

private:
    MapParserState m_CurrentState;
    std::map<int, EntityType> m_Types;
    std::map<Vec, MapSection>::iterator m_CurrentSectionIt = m_Map->m_Sections.end();
    GameState m_GameState;
    int m_BlocksWidth, m_BlocksHeight;

    static std::pair<Result, Vec> readSetCommand(const std::string &line);

    static std::tuple<Result, Vec, Vec, int>
    readMonsterAddCommand(const std::string &line);

};

#endif // TPOHB_MAPFILEPARSER_H
