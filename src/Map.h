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
#include "entity/Axe.h"

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

     bool tryNavigateToSection(Vec inDirection);

    void test() {
        sections.emplace(Vec(0, 0), MapSection(SCREEN_WIDTH, SCREEN_HEIGHT));
        currentSection = sections.find(Vec(0, 0));

        for (int i = 0; i < SCREEN_WIDTH; i++) {
            std::unique_ptr<Entity> tree(new Tree());
            std::unique_ptr<Entity> tree2(new Tree());
            currentSection->second.set(Vec(i, 0), std::move(tree));
            currentSection->second.set(Vec(i, SCREEN_HEIGHT - 1), std::move(tree2));
        }

        for (int i = 1; i < SCREEN_HEIGHT - 1; i++) {
            std::unique_ptr<Entity> tree(new Tree());
            std::unique_ptr<Entity> tree2(new Tree());
            currentSection->second.set(Vec(0, i), std::move(tree));
            currentSection->second.set(Vec(SCREEN_WIDTH - 1, i), std::move(tree2));
        }

        currentSection->second.set(Vec(SCREEN_WIDTH - 1, SCREEN_HEIGHT / 2), nullptr);

        currentSection->second.set(Vec(2, 4), std::make_unique<Apple>());
        currentSection->second.set(Vec(4, 2), std::make_unique<Apple>());
        currentSection->second.set(Vec(5, 2), std::make_unique<Sword>());

        addSection2();
    }

    void addSection2() {
        auto ins = sections.emplace(Vec(1, 0), MapSection(SCREEN_WIDTH, SCREEN_HEIGHT));

        if (!ins.second) return;

        for (int i = 0; i < SCREEN_WIDTH; i++) {
            std::unique_ptr<Entity> tree(new Tree());
            std::unique_ptr<Entity> tree2(new Tree());
            ins.first->second.set(Vec(i, 0), std::move(tree));
            ins.first->second.set(Vec(i, SCREEN_HEIGHT - 1), std::move(tree2));
        }

        for (int i = 1; i < SCREEN_HEIGHT - 1; i++) {
            std::unique_ptr<Entity> tree(new Tree());
            std::unique_ptr<Entity> tree2(new Tree());
            ins.first->second.set(Vec(0, i), std::move(tree));
            ins.first->second.set(Vec(SCREEN_WIDTH - 1, i), std::move(tree2));
        }

        ins.first->second.set(Vec(0, SCREEN_HEIGHT / 2), nullptr);

        std::unique_ptr<Entity> tree(new Tree());
        ins.first->second.set(Vec(1, 6), std::move(tree));

        ins.first->second.set(Vec(2, 4), std::make_unique<Apple>());
        ins.first->second.set(Vec(4, 2), std::make_unique<Apple>());
        ins.first->second.set(Vec(6, 2), std::make_unique<Axe>());

    }
};


#endif //TPOHB_MAP_H
