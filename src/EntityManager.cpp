#include "EntityManager.h"

#include "entity/Entity.h"
#include "entity/Tree.h"
#include "entity/Apple.h"
#include "entity/Sword.h"
#include "entity/Axe.h"
#include "entity/Bricks.h"
#include "entity/Grass.h"
#include "entity/Monster.h"
#include "entity/Zombie.h"

EntityManger::Type EntityManger::getType(const std::string &name) {
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

std::unique_ptr<Entity> EntityManger::getEntity(EntityManger::Type type) {
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

std::unique_ptr<Monster> EntityManger::getMonster(EntityManger::Type type) {
    switch (type) {
        case Type::ZOMBIE:
            return std::move(std::make_unique<Zombie>());
        default:
            return nullptr;
    }
}

std::unique_ptr<PickupEntity> EntityManger::getPickupEntity(Type type) {
    switch (type) {
        case Type::APPLE:
            return std::move(std::make_unique<Apple>());
        default:
            return nullptr;
    }
}

std::unique_ptr<Weapon> EntityManger::getWeapon(Type type) {
    switch (type) {
        case Type::SWORD:
            return std::move(std::make_unique<Sword>());
        case Type::AXE:
            return std::move(std::make_unique<Axe>());
        default:
            return nullptr;
    }
}
