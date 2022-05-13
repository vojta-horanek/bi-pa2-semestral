#ifndef TPOHB_ENTITYMANAGER_H
#define TPOHB_ENTITYMANAGER_H

#include "entity/Entity.fwd.h"
#include "entity/Monster.fwd.h"
#include "entity/PickupEntity.fwd.h"
#include "entity/Weapon.fwd.h"
#include <memory>
#include <string>

class EntityManger {
  public:
    enum class Type { VOID, TREE, APPLE, SWORD, AXE, BRICK, GRASS, ZOMBIE, INVALID };

    static Type getType(const std::string &name);

    static std::unique_ptr<Entity> getEntity(Type type);

    static std::unique_ptr<Monster> getMonster(Type type);

    static std::unique_ptr<PickupEntity> getPickupEntity(Type type);

    static std::unique_ptr<Weapon> getWeapon(Type type);
};

#endif // TPOHB_ENTITYMANAGER_H