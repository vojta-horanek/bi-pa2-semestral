#ifndef TPOHB_MAPSECTION_H
#define TPOHB_MAPSECTION_H

#include "entity/Apple.h"
#include "entity/Axe.h"
#include "entity/Bricks.h"
#include "entity/Entity.h"
#include "entity/Grass.h"
#include "entity/MovingEntity.h"
#include "entity/Sword.h"
#include "entity/Tree.h"
#include "render/Vec.h"
#include <cassert>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

class MapSection {
  public:
    int m_BlocksWidth;
    int m_BlocksHeight;
    std::vector<std::vector<std::unique_ptr<Entity>>> m_Entities;
    std::vector<std::unique_ptr<MovingEntity>> m_MovingEntities;

    explicit MapSection(int blocksWidth, int blocksHeight,
                        std::unique_ptr<Entity> background);

    Entity *get(Vec at) const;

    void set(Vec at, std::unique_ptr<Entity> entity);

    void render(GameState &state);

    void onTurn(GameState &state);

    bool isEdge(Vec position) const;

    bool collideWith(Vec position, GameState &gameState,
                     bool isPlayer = true) const;

    bool isMovingEntity(Vec position) const;

    void writeToStream(std::ostream &stream,
                       const std::map<EntityType, int> &types,
                       Vec sectionPosition) const;

    void writeMovingEntities(std::ostream &stream,
                             const std::map<EntityType, int> &types,
                             Vec sectionPosition) const;

  private:
    std::unique_ptr<Entity> backgroundEntity = nullptr;
};

#endif // TPOHB_MAPSECTION_H
