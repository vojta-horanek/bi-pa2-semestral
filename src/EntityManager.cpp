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

const std::pair<EntityType, const std::string> EntityManager::typeTable[] = {
    {EntityType::VOID, "VOID"},    {EntityType::TREE, "TREE"},
    {EntityType::APPLE, "APPLE"},  {EntityType::SWORD, "SWORD"},
    {EntityType::AXE, "AXE"},      {EntityType::BRICK, "BRICK"},
    {EntityType::GRASS, "GRASS"},  {EntityType::ZOMBIE, "ZOMBIE"},
    {EntityType::HEARTH, "HEARTH"}};

const size_t EntityManager::typeTableSize =
    sizeof(typeTable) / sizeof(typeTable[0]);

std::pair<EntityType, const std::string>
EntityManager::findType(const std::string &name) {
    for (size_t i = 0; i < typeTableSize; i++) {
        if (typeTable[i].second == name)
            return typeTable[i];
    }

    return {EntityType::INVALID, "INVALID"};
}

std::pair<EntityType, const std::string>
EntityManager::findType(EntityType type) {
    for (size_t i = 0; i < typeTableSize; i++) {
        if (typeTable[i].first == type)
            return typeTable[i];
    }

    return {EntityType::INVALID, "INVALID"};
}

EntityType EntityManager::getType(const std::string &name) {
    return findType(name).first;
}

std::string EntityManager::getString(const EntityType &type) {
    return findType(type).second;
}

std::unique_ptr<Entity> EntityManager::getEntity(EntityType type) {
    switch (type) {
        case EntityType::VOID:
            return std::move(std::make_unique<Entity>());
        case EntityType::TREE:
            return std::move(std::make_unique<Tree>());
        case EntityType::APPLE:
            return std::move(std::make_unique<Apple>());
        case EntityType::SWORD:
            return std::move(std::make_unique<Sword>());
        case EntityType::AXE:
            return std::move(std::make_unique<Axe>());
        case EntityType::BRICK:
            return std::move(std::make_unique<Bricks>());
        case EntityType::GRASS:
            return std::move(std::make_unique<Grass>());
        case EntityType::ZOMBIE:
            return std::move(std::make_unique<Zombie>());
        default:
            return nullptr;
    }
}

std::unique_ptr<Monster> EntityManager::getMonster(EntityType type) {
    switch (type) {
        case EntityType::ZOMBIE:
            return std::move(std::make_unique<Zombie>());
        default:
            return nullptr;
    }
}

std::unique_ptr<PickupEntity> EntityManager::getPickupEntity(EntityType type) {
    switch (type) {
        case EntityType::APPLE:
            return std::move(std::make_unique<Apple>());
        default:
            return nullptr;
    }
}

std::unique_ptr<Weapon> EntityManager::getWeapon(EntityType type) {
    switch (type) {
        case EntityType::SWORD:
            return std::move(std::make_unique<Sword>());
        case EntityType::AXE:
            return std::move(std::make_unique<Axe>());
        default:
            return nullptr;
    }
}

std::map<EntityType, int> EntityManager::createDefinitions() {
    std::map<EntityType, int> typeMap;

    for (size_t i = 0; i < typeTableSize; i++) {
        typeMap[typeTable[i].first] = i;
    }

    return typeMap;
}

void EntityManager::printDefinitions(const std::map<EntityType, int> &types,
                                     std::ostream &outStream) {

    for (const auto &item : types) {
        outStream << item.second << " " << getString(item.first) << std::endl;
    }
}