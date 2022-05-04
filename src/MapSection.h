#ifndef TPOHB_MAPSECTION_H
#define TPOHB_MAPSECTION_H

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
#include "entity/MovingEntity.h"

class MapSection {
private:
    std::unique_ptr<Entity> backgroundEntity = nullptr;
public:
    size_t width;
    size_t height;
    std::vector<std::vector<std::unique_ptr<Entity>>> entities;
    std::vector<std::unique_ptr<MovingEntity>> movingEntities;

    explicit MapSection(size_t width, size_t height, std::unique_ptr<Entity> background) {
        this->width = width;
        this->height = height;
        backgroundEntity = std::move(background);
        this->entities.reserve(height);
    }

    Entity *get(Vec at) const;

    void set(Vec at, std::unique_ptr<Entity> entity);

    void render(GameState &state);

    void onTurn(GameState & state);

    bool isEdge(Vec position) const;

    bool wouldCollide(Vec player) const;
};


#endif //TPOHB_MAPSECTION_H
