#ifndef TPOHB_ENTITYMANAGER_H
#define TPOHB_ENTITYMANAGER_H

#include "entity/Entity.fwd.h"
#include "entity/Monster.fwd.h"
#include "entity/PickupEntity.fwd.h"
#include "entity/Weapon.fwd.h"
#include <map>
#include <memory>
#include <ostream>
#include <string>

class EntityManager {
  public:
    enum class Type { VOID, TREE, APPLE, SWORD, AXE, BRICK, GRASS, ZOMBIE, INVALID };

  private:
    const static std::pair<Type, const std::string> typeTable[];
    const static size_t typeTableSize;

    static std::pair<Type, const std::string> findType(const std::string &name);
    static std::pair<Type, const std::string> findType(Type type);

  public:
    static Type getType(const std::string &name);

    static std::string getString(const Type &type);

    static std::unique_ptr<Entity> getEntity(Type type);

    static std::unique_ptr<Monster> getMonster(Type type);

    static std::unique_ptr<PickupEntity> getPickupEntity(Type type);

    static std::unique_ptr<Weapon> getWeapon(Type type);

    static std::map<Type, int> createDefinitions();

    static void printDefinitions(const std::map<EntityManager::Type, int> &types,
                                 std::ostream &outStream);
};

#endif // TPOHB_ENTITYMANAGER_H