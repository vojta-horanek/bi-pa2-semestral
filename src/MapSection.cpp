#include "MapSection.h"

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

    for (const auto &entity: movingEntities) {
        entity->render(state, entity->position);
    }

}

void MapSection::onTurn(GameState &state) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (entities[y][x] != nullptr
                && entities[y][x]->removeOnNextTurn) {
                entities[y][x] = nullptr;
            }
        }
    }

    for (const auto &entity: movingEntities) {
        entity->onTurn(state);
    }
}

bool MapSection::isEdge(Vec position) const {
    return position.x < 0 ||
           position.x >= width ||
           position.y >= height ||
           position.y < 0;
}

bool MapSection::wouldCollide(Vec player) const {
    return get(player) != nullptr && get(player)->hasCollision;
}

void MapSection::set(Vec at, std::unique_ptr<Entity> entity) {
    entities[at.y][at.x] = std::move(entity);
}

Entity *MapSection::get(Vec at) const {
    return entities[at.y][at.x].get();
}
