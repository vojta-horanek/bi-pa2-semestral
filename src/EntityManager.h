#ifndef TPOHB_ENTITYMANAGER_H
#define TPOHB_ENTITYMANAGER_H

#include "EntityType.h"
#include "entity/Entity.fwd.h"
#include "entity/Monster.fwd.h"
#include "entity/PickupEntity.fwd.h"
#include "entity/Weapon.fwd.h"
#include <map>
#include <memory>
#include <ostream>
#include <string>

class EntityManager {
  private:
    const static std::pair<EntityType, const std::string> s_TypeTable[];
    const static size_t s_TypeTableSize;

    static std::pair<EntityType, const std::string>
    findType(const std::string &name);

    static std::pair<EntityType, const std::string> findType(EntityType type);

  public:
    static EntityType getType(const std::string &name);

    static std::string getString(const EntityType &type);

    static std::unique_ptr<Entity> getEntity(EntityType type);

    static std::unique_ptr<Monster> getMonster(EntityType type);

    static std::unique_ptr<PickupEntity> getPickupEntity(EntityType type);

    static std::unique_ptr<Weapon> getWeapon(EntityType type);

    static std::map<EntityType, int> createDefinitions();

    static void printDefinitions(const std::map<EntityType, int> &types,
                                 std::ostream &outStream);
};

#endif // TPOHB_ENTITYMANAGER_H