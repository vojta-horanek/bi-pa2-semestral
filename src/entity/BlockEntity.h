#ifndef TPOHB_BLOCKENTITY_H
#define TPOHB_BLOCKENTITY_H

#include "Entity.h"

/**
 * A block entity is an entity that the player cannot move onto, e.g. it stops
 * their movement
 */
class BlockEntity : public Entity {
  protected:
    explicit BlockEntity(Texture texture);
};

#endif // TPOHB_BLOCKENTITY_H
