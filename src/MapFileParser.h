#ifndef TPOHB_MAPFILEPARSER_H
#define TPOHB_MAPFILEPARSER_H


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <locale>
#include <memory>
#include <utility>
#include <stdexcept>
#include "entity/Entity.h"
#include "entity/Tree.h"
#include "entity/Apple.h"
#include "entity/Sword.h"
#include "entity/Axe.h"
#include "entity/Bricks.h"
#include "entity/Grass.h"
#include "Map.h"
#include "Result.h"

class MapFileParser {

private:

    enum EntityType {
        VOID,
        TREE,
        APPLE,
        SWORD,
        AXE,
        BRICK,
        GRASS,
        INVALID
    };

    static EntityType typeFromString(const std::string &name) {
        if (name == "VOID") return VOID;
        if (name == "TREE") return TREE;
        if (name == "APPLE") return APPLE;
        if (name == "SWORD") return SWORD;
        if (name == "AXE") return AXE;
        if (name == "BRICK") return BRICK;
        if (name == "GRASS") return GRASS;
        else return INVALID;
    }

    static std::unique_ptr<Entity> typeToNewEntity(EntityType type) {
        switch (type) {
            case VOID:
                return std::move(std::make_unique<Entity>());
            case TREE:
                return std::move(std::make_unique<Tree>());
            case APPLE:
                return std::move(std::make_unique<Apple>());
            case SWORD:
                return std::move(std::make_unique<Sword>());
            case AXE:
                return std::move(std::make_unique<Axe>());
            case BRICK:
                return std::move(std::make_unique<Bricks>());
            case GRASS:
                return std::move(std::make_unique<Grass>());
            case INVALID:
            default:
                throw std::invalid_argument("An invalid entity type does not have an entity!");
        }
    }

    class State {
    private:
        int value = none;
    public:
        static const int player = 0;
        static const int default_section = 1;
        static const int section = 2;
        static const int sections = 3;
        static const int define = 4;
        static const int none = 5;
        static const int invalid = 6;

        State() = default;

        explicit State(int value) : value(value) {}

        std::string toString() const {
            switch (value) {
                case player:
                    return "PLAYER";
                case default_section:
                    return "DEFAULT_SECTION";
                case sections:
                    return "SECTIONS";
                case section:
                    return "SECTION";
                case define:
                    return "DEFINE";
                case none:
                    return "NONE";
                default:
                    throw std::invalid_argument("Unknown state!");
            }
        }

        void reset() {
            value = none;
        }

        void set(int _value) {
            value = _value;
        }

        void set(const State & state) {
            value = state.value;
        }

        int get() const {
            return value;
        }

        static State fromString(const std::string &str) {
            if (str == "PLAYER") return State(player);
            if (str == "DEFAULT_SECTION") return State(default_section);
            if (str == "SECTIONS") return State(sections);
            if (str == "SECTION") return State(section);
            if (str == "DEFINE") return State(define);
            else return State(invalid);
        }

        bool operator==(const State &rhs) const {
            return value == rhs.value;
        }

        bool operator!=(const State &rhs) const {
            return !(rhs == *this);
        }

        bool operator==(int rhs) const {
            return value == rhs;
        }

        bool operator!=(int rhs) const {
            return !(*this == rhs);
        }
    };

    State currentState;
    Map map;
    std::map<int, EntityType> types;
    std::map<Vec, MapSection>::iterator currentSection;
    GameState gameState;

    static std::pair<Result, Vec> readSetCommand(const std::string &line);

public:
    Result parseNextLine(const std::string & line);
    Map getMap();
    GameState getState();

};


#endif //TPOHB_MAPFILEPARSER_H
