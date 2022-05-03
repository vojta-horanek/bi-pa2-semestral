#ifndef TPOHB_ENTITYTYPE_H
#define TPOHB_ENTITYTYPE_H

#include <string>
#include <memory>
#include <stdexcept>
#include "Entity.h"

enum EntityType {
    VOID,
    TREE,
    APPLE,
    SWORD,
    AXE,
    BRICK,
    GRASS,
    INVALID
};

EntityType fromStr(const std::string & name) {
    if (name == "VOID") return VOID;
    if (name == "TREE") return TREE;
    if (name == "APPLE") return APPLE;
    if (name == "SWORD") return SWORD;
    if (name == "AXE") return AXE;
    if (name == "BRICK") return BRICK;
    if (name == "GRASS") return GRASS;
    else return INVALID;
}

std::unique_ptr<Entity> toNewEntity(EntityType type) {
    switch (type) {
        case VOID:
            return std::move(std::make_unique<Entity>(nullptr));
        case TREE:
            return std::move(std::make_unique<Tree>());
        case APPLE:
            return std::move(std::make_unique<Apple>());
        case SWORD:
            return std::move(std::make_unique<Sword>());
        case AXE:
            return std::move(std::make_unique<Axe>());
        case BRICK:
            return std::move(std::make_unique<Bricks>());
        case GRASS:
            return std::move(std::make_unique<Grass>());
        case INVALID:
        default:
            throw std::invalid_argument("An invalid entity type does not have an entity!");
    }
}

#endif //TPOHB_ENTITYTYPE_H
