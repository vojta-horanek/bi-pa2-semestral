#ifndef TPOHB_MAP_H
#define TPOHB_MAP_H

#include <map>
#include <vector>
#include <cassert>
#include <string>
#include <memory>
#include "Vec.h"
#include "entity/Entity.h"
#include "entity/Grass.h"
#include "entity/Tree.h"
#include "entity/Bricks.h"
#include "entity/Apple.h"
#include "entity/Sword.h"
#include "entity/Axe.h"

class Map {
private:
    class MapSection {
    private:
        std::unique_ptr<Entity> backgroundEntity = nullptr;
        size_t width;
        size_t height;
    public:
        std::vector<std::vector<std::unique_ptr<Entity>>> entities;

        explicit MapSection(size_t width, size_t height, std::unique_ptr<Entity> background) {
            this->width = width;
            this->height = height;
            backgroundEntity = std::move(background);
        }

        Entity *get(Vec at) const {
            return entities[at.y][at.x].get();
        }

        void set(Vec at, std::unique_ptr<Entity> entity) {
            entities[at.y][at.x] = std::move(entity);
        }

        void render(GameState &state);

        bool isEdge(Vec position) const {
            return position.x < 0 ||
                   position.x >= width ||
                   position.y >= height ||
                   position.y < 0;
        }

        bool wouldCollide(Vec player) const {
            return get(player) != nullptr && get(player)->hasCollision;
        }
    };

    std::map<Vec, MapSection> sections;
    std::map<Vec, MapSection>::iterator currentSection = sections.end();
public:
    MapSection &getCurrentSection();

     bool tryNavigateToSection(Vec inPlayerDirection);

     static Map loadFromFile(const std::string & fileName, GameState & gameState);
};


#endif //TPOHB_MAP_H
