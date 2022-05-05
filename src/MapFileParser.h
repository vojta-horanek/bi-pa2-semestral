#ifndef TPOHB_MAPFILEPARSER_H
#define TPOHB_MAPFILEPARSER_H


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <memory>
#include <tuple>
#include <utility>
#include "Map.h"
#include "Result.h"
#include "entity/Entity.h"
#include "entity/Tree.h"
#include "entity/Apple.h"
#include "entity/Sword.h"
#include "entity/Axe.h"
#include "entity/Bricks.h"
#include "entity/Grass.h"
#include "entity/Monster.h"

class MapParserState {
public:
    enum class Value {
        player, default_section, section, sections, define, none, invalid, monsters
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

class EntityManger {
public:
    enum class Type {
        VOID, TREE, APPLE, SWORD, AXE, BRICK, GRASS, MONSTER, INVALID
    };

    static Type getType(const std::string &name);

    static std::unique_ptr<Entity> getEntity(Type type);

    static std::unique_ptr<Monster> getMonster(Type type);
};

class MapFileParser {

private:
    MapParserState currentState;
    Map map;
    std::map<int, EntityManger::Type> types;
    std::map<Vec, MapSection>::iterator currentSection;
    GameState gameState;
    int width, height;

    static std::pair<Result, Vec> readSetCommand(const std::string &line);

    static std::tuple<Result, Vec, Vec, int> readMonsterAddCommand(const std::string &line);

public:
    MapFileParser(int width, int height);

    Result parseNextLine(const std::string &line);

    Map getMap();

    GameState getState();
};


#endif //TPOHB_MAPFILEPARSER_H
