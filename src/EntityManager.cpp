#include "EntityManager.h"

#include "entity/Apple.h"
#include "entity/Axe.h"
#include "entity/Bricks.h"
#include "entity/Entity.h"
#include "entity/Grass.h"
#include "entity/Monster.h"
#include "entity/Sword.h"
#include "entity/Tree.h"
#include "entity/Zombie.h"
#include <initializer_list>
#include <map>

const std::pair<EntityManager::Type, const std::string>
    EntityManager::typeTable[] = {
        {Type::VOID, "VOID"},   {Type::TREE, "TREE"},    {Type::APPLE, "APPLE"},
        {Type::SWORD, "SWORD"}, {Type::AXE, "AXE"},      {Type::BRICK, "BRICK"},
        {Type::GRASS, "GRASS"}, {Type::ZOMBIE, "ZOMBIE"}};

const size_t EntityManager::typeTableSize =
    sizeof(typeTable) / sizeof(typeTable[0]);

std::pair<EntityManager::Type, const std::string>
EntityManager::findType(const std::string &name) {
    for (size_t i = 0; i < typeTableSize; i++) {
        if (typeTable[i].second == name)
            return typeTable[i];
    }

    return {Type::INVALID, "INVALID"};
}

std::pair<EntityManager::Type, const std::string>
EntityManager::findType(Type type) {
    for (size_t i = 0; i < typeTableSize; i++) {
        if (typeTable[i].first == type)
            return typeTable[i];
    }

    return {Type::INVALID, "INVALID"};
}

EntityManager::Type EntityManager::getType(const std::string &name) {
    return findType(name).first;
}

std::string EntityManager::getString(const Type &type) {
    return findType(type).second;
}

std::unique_ptr<Entity> EntityManager::getEntity(EntityManager::Type type) {
    switch (type) {
        case Type::VOID:
            return std::move(std::make_unique<Entity>());
        case Type::TREE:
            return std::move(std::make_unique<Tree>());
        case Type::APPLE:
            return std::move(std::make_unique<Apple>());
        case Type::SWORD:
            return std::move(std::make_unique<Sword>());
        case Type::AXE:
            return std::move(std::make_unique<Axe>());
        case Type::BRICK:
            return std::move(std::make_unique<Bricks>());
        case Type::GRASS:
            return std::move(std::make_unique<Grass>());
        case Type::ZOMBIE:
            return std::move(std::make_unique<Zombie>());
        default:
            return nullptr;
    }
}

std::unique_ptr<Monster> EntityManager::getMonster(EntityManager::Type type) {
    switch (type) {
        case Type::ZOMBIE:
            return std::move(std::make_unique<Zombie>());
        default:
            return nullptr;
    }
}

std::unique_ptr<PickupEntity> EntityManager::getPickupEntity(Type type) {
    switch (type) {
        case Type::APPLE:
            return std::move(std::make_unique<Apple>());
        default:
            return nullptr;
    }
}

std::unique_ptr<Weapon> EntityManager::getWeapon(Type type) {
    switch (type) {
        case Type::SWORD:
            return std::move(std::make_unique<Sword>());
        case Type::AXE:
            return std::move(std::make_unique<Axe>());
        default:
            return nullptr;
    }
}

std::map<EntityManager::Type, int> EntityManager::createDefinitions() {
    const Type types[] = {Type::VOID, Type::TREE,  Type::APPLE, Type::SWORD,
                          Type::AXE,  Type::BRICK, Type::GRASS, Type::ZOMBIE};

    std::map<Type, int> typeMap;

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        typeMap[types[i]] = i;
    }

    return typeMap;
}

void EntityManager::printDefinitions(
    const std::map<EntityManager::Type, int> &types, std::ostream &outStream) {

    for (const auto &item : types) {
        outStream << item.second << " " << getString(item.first) << std::endl;
    }
}