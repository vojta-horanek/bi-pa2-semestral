#ifndef TPOHB_MAPFILEPARSER_H
#define TPOHB_MAPFILEPARSER_H

#include "EntityManager.h"
#include "Map.h"
#include "Result.h"

class MapParserState {
  public:
    enum class Value {
        player,
        default_section,
        section,
        sections,
        define,
        none,
        invalid,
        monsters
    };

  private:
    Value value = Value::none;

  public:
    MapParserState();

    explicit MapParserState(Value value);

    std::string toString() const;

    void reset();

    void set(Value val);

    void set(const MapParserState &state);

    Value get() const;

    static MapParserState fromString(const std::string &str);

    bool operator==(const MapParserState &rhs) const;

    bool operator!=(const MapParserState &rhs) const;

    bool operator==(Value rhs) const;

    bool operator!=(Value rhs) const;
};

class MapFileParser {

  private:
    MapParserState currentState;
    Map map;
    std::map<int, EntityManger::Type> types;
    std::map<Vec, MapSection>::iterator currentSection = map.sections.end();
    GameState gameState;
    int width, height;

    static std::pair<Result, Vec> readSetCommand(const std::string &line);

    static std::tuple<Result, Vec, Vec, int> readMonsterAddCommand(const std::string &line);

  public:
    MapFileParser(int width, int height);

    Result parseNextLine(const std::string &line);

    Map getMap();

    Result areAllValuesSet() const;

    GameState getState();
};

#endif // TPOHB_MAPFILEPARSER_H
