#ifndef TPOHB_MAPSECTION_H
#define TPOHB_MAPSECTION_H

#include "entity/Apple.h"
#include "entity/Axe.h"
#include "entity/Bricks.h"
#include "entity/Entity.h"
#include "entity/Grass.h"
#include "entity/MovingEntity.h"
#include "entity/Monster.h"
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
    /**
     * A 2D vector holding all the non movable entities to be rendered and interacted with.
     */
    std::vector<std::vector<std::unique_ptr<Entity>>> m_Entities;

    /**
     * A vector holding all the moving entities.
     * Moving entities have their position saved as a member value.
     */
    std::vector<std::unique_ptr<MovingEntity>> m_MovingEntities;

    explicit MapSection(int blocksWidth, int blocksHeight,
                        std::unique_ptr<Entity> background);

    /**
     *
     * @param at position of the entity
     * @return the pointer to the entity at that position.
     * The pointer returned must not be kept for any longer that necessary,
     * since it might get invalidated
     */
    Entity *get(Vec at) const;

    /**
     * Set's an entity to the position erasing the previous one
     * @param at the position
     * @param entity the entity to be placed at the position
     */
    void set(Vec at, std::unique_ptr<Entity> entity);

    /**
     * Renders this game section
     * @param state current state of the game
     */
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
    /**
     * A background entity is an entity that is implicitly drawn under any other entity.
     * It cannot be interacted with (e.g. no collision, pickup etc...)
     */
    std::unique_ptr<Entity> m_BackgroundEntity = nullptr;
};

#endif // TPOHB_MAPSECTION_H
