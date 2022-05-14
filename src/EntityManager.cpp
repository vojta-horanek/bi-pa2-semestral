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

EntityManager::Type EntityManager::getType(const std::string &name) {
    if (name == "VOID")
        return Type::VOID;
    if (name == "TREE")
        return Type::TREE;
    if (name == "APPLE")
        return Type::APPLE;
    if (name == "SWORD")
        return Type::SWORD;
    if (name == "AXE")
        return Type::AXE;
    if (name == "BRICK")
        return Type::BRICK;
    if (name == "GRASS")
        return Type::GRASS;
    if (name == "ZOMBIE")
        return Type::ZOMBIE;
    else
        return Type::INVALID;
}

std::string EntityManager::getString(const Type &type) {
    switch (type) {
        case Type::VOID:
            return "VOID";
        case Type::TREE:
            return "TREE";
        case Type::APPLE:
            return "APPLE";
        case Type::SWORD:
            return "SWORD";
        case Type::AXE:
            return "AXE";
        case Type::BRICK:
            return "BRICK";
        case Type::GRASS:
            return "GRASS";
        case Type::ZOMBIE:
            return "ZOMBIE";
        default:
            return "";
    }
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

void EntityManager::printDefinitions(const std::map<EntityManager::Type, int> &types,
                                     std::ostream &outStream) {

    for (const auto &item : types) {
        outStream << item.second << " " << getString(item.first) << std::endl;
    }
}