#ifndef TPOHB_MAPSECTION_H
#define TPOHB_MAPSECTION_H

#include "Vec.h"
#include "entity/Apple.h"
#include "entity/Axe.h"
#include "entity/Bricks.h"
#include "entity/Entity.h"
#include "entity/Grass.h"
#include "entity/MovingEntity.h"
#include "entity/Sword.h"
#include "entity/Tree.h"
#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <vector>

class MapSection {
  private:
    std::unique_ptr<Entity> backgroundEntity = nullptr;

  public:
    int width;
    int height;
    std::vector<std::vector<std::unique_ptr<Entity>>> entities;
    std::vector<std::unique_ptr<MovingEntity>> movingEntities;

    explicit MapSection(int width, int height,
                        std::unique_ptr<Entity> background);

    Entity *get(Vec at) const;

    void set(Vec at, std::unique_ptr<Entity> entity);

    void render(GameState &state);

    void onTurn(GameState &state);

    bool isEdge(Vec position) const;

    bool collideWith(Vec position, GameState &gameState,
                     bool isPlayer = true) const;

    bool isMovingEntity(Vec position) const;
};

#endif // TPOHB_MAPSECTION_H
