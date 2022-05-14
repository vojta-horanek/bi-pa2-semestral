#include "MapSection.h"

#include "entity/MovingEntity.h"
#include <algorithm>

MapSection::MapSection(int width, int height,
                       std::unique_ptr<Entity> background) {
    this->width = width;
    this->height = height;
    backgroundEntity = std::move(background);
    this->entities.reserve(height);
}

void MapSection::render(GameState &state) {

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (backgroundEntity != nullptr) {
                backgroundEntity->render(state, Vec(x, y));
            }
            if (entities[y][x] != nullptr) {
                entities[y][x]->render(state, Vec(x, y));
            }
        }
    }

    for (const auto &entity : movingEntities) {
        entity->render(state, entity->position);
    }
}

void MapSection::onTurn(GameState &state) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (entities[y][x] != nullptr && entities[y][x]->removeOnNextTurn) {
                entities[y][x] = nullptr;
            }
        }
    }

    for (const auto &entity : movingEntities) {
        entity->onTurn(state, *this);
    }

    movingEntities.erase(std::remove_if(movingEntities.begin(),
                                        movingEntities.end(),
                                        [](const auto &entity) {
                                            return entity->removeOnNextTurn;
                                        }),
                         movingEntities.end());
}

bool MapSection::isEdge(Vec position) const {
    return position.x < 0 || position.x >= width || position.y >= height ||
           position.y < 0;
}

bool MapSection::collideWith(Vec position, GameState &gameState,
                             bool isPlayer) const {
    Entity *atPosition = get(position);
    if (atPosition == nullptr)
        return false;
    if (isPlayer && atPosition->collisionType != Entity::Collision::NONE)
        atPosition->onCollision(gameState);
    return atPosition->collisionType == Entity::Collision::HARD;
}

void MapSection::set(Vec at, std::unique_ptr<Entity> entity) {
    entities[at.y][at.x] = std::move(entity);
}

Entity *MapSection::get(Vec at) const { return entities[at.y][at.x].get(); }

bool MapSection::isMovingEntity(Vec position) const {
    for (const auto &item : movingEntities) {
        if (item->position == position)
            return true;
    }
    return false;
}
