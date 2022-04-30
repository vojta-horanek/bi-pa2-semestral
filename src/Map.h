#ifndef TPOHB_MAP_H
#define TPOHB_MAP_H

#include <map>
#include <vector>
#include <cassert>
#include <memory>
#include "Vec.h"
#include "entity/Entity.h"
#include "entity/Grass.h"
#include "entity/Tree.h"
#include "entity/Bricks.h"
#include "entity/Apple.h"
#include "entity/Sword.h"

class Map {
private:
    class MapSection {
    private:
        std::vector<std::vector<std::unique_ptr<Entity>>> entities;
        std::unique_ptr<Entity> backgroundEntity;
        size_t width;
        size_t height;
    public:

        explicit MapSection(size_t width, size_t height) {
            this->width = width;
            this->height = height;
            entities.reserve(width);
            for (int i = 0; i < width; i++) {
                std::vector<std::unique_ptr<Entity>> row;
                row.reserve(height);
                for (int j = 0; j < height; j++) {
                    row.emplace_back(nullptr);
                }
                entities.emplace_back(std::move(row));
            }
            backgroundEntity = std::make_unique<Grass>();
        }

        Entity *get(Vec at) const {
            return entities[at.x][at.y].get();
        }

        void set(Vec at, std::unique_ptr<Entity> entity) {
            entities[at.x][at.y] = std::move(entity);
        }

        void render(GameState &state) {
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    if (backgroundEntity != nullptr) {
                        backgroundEntity->render(state, Vec(i, j));
                    }
                    if (entities[i][j] != nullptr) {
                        entities[i][j]->render(state, Vec(i, j));
                        if (entities[i][j]->removeOnNextRender) {
                            entities[i][j] = nullptr;
                        }
                    }

                }
            }
        }

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
    MapSection &getCurrentSection() {
        assert(currentSection != sections.end());
        return currentSection->second;
    }

    void navigateToSection(Vec inDirection) {
        Vec newSection = currentSection->first + inDirection;
        currentSection = sections.find(newSection);
        assert(currentSection != sections.end());
    }

    void test() {
        sections.emplace(Vec(0, 0), MapSection(SCREEN_WIDTH, SCREEN_HEIGHT));
        currentSection = sections.find(Vec(0, 0));

        std::unique_ptr<Entity> tree(new Tree());
        currentSection->second.set(Vec(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), std::move(tree));

        currentSection->second.set(Vec(2, 4), std::make_unique<Apple>());
        currentSection->second.set(Vec(4, 2), std::make_unique<Apple>());
        currentSection->second.set(Vec(5, 2), std::make_unique<Sword>());

        for (int i = 0; i < SCREEN_WIDTH / 2; i++) {
            std::unique_ptr<Entity> brick(new Bricks());
            currentSection->second.set(Vec(i, 5), std::move(brick));
        }

        for (int i = SCREEN_WIDTH / 2 + 1; i < SCREEN_WIDTH; i++) {
            std::unique_ptr<Entity> brick(new Bricks());
            currentSection->second.set(Vec(i, 5), std::move(brick));
        }

    }
};


#endif //TPOHB_MAP_H
