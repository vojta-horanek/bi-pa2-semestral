#include "MapSection.h"

#include "entity/MovingEntity.h"
#include <algorithm>

MapSection::MapSection(int blocksWidth, int blocksHeight,
                       std::unique_ptr<Entity> background) {
    m_BlocksWidth = blocksWidth;
    m_BlocksHeight = blocksHeight;
    m_BackgroundEntity = std::move(background);
    m_Entities.reserve(blocksHeight);
}

void MapSection::render(GameState &state) {

    for (int x = 0; x < m_BlocksWidth; x++) {
        for (int y = 0; y < m_BlocksHeight; y++) {
            if (m_BackgroundEntity != nullptr) {
                m_BackgroundEntity->render(state, Vec(x, y));
            }
            if (m_Entities[y][x] != nullptr) {
                m_Entities[y][x]->render(state, Vec(x, y));
            }
        }
    }

    for (const auto &entity : m_MovingEntities) {
        entity->render(state, entity->m_Position);
    }
}

void MapSection::onTurn(GameState &state) {
    for (int x = 0; x < m_BlocksWidth; x++) {
        for (int y = 0; y < m_BlocksHeight; y++) {
            if (m_Entities[y][x] != nullptr &&
                m_Entities[y][x]->m_RemoveOnNextTurn) {
                m_Entities[y][x] = nullptr;
            }
        }
    }

    for (const auto &entity : m_MovingEntities) {
        entity->onTurn(state, *this);
    }

    m_MovingEntities.erase(std::remove_if(m_MovingEntities.begin(),
                                          m_MovingEntities.end(),
                                          [](const auto &entity) {
                                              return entity->m_RemoveOnNextTurn;
                                          }),
                           m_MovingEntities.end());
}

bool MapSection::isEdge(Vec position) const {
    return position.x < 0 || position.x >= m_BlocksWidth ||
           position.y >= m_BlocksHeight || position.y < 0;
}

bool MapSection::collideWith(Vec position, GameState &gameState,
                             bool isPlayer) const {
    Entity *atPosition = get(position);
    if (atPosition == nullptr)
        return false;
    if (isPlayer && atPosition->m_CollisionType != Entity::Collision::NONE)
        atPosition->onCollision(gameState);
    return atPosition->m_CollisionType == Entity::Collision::HARD;
}

void MapSection::set(Vec at, std::unique_ptr<Entity> entity) {
    m_Entities[at.y][at.x] = std::move(entity);
}

Entity *MapSection::get(Vec at) const { return m_Entities[at.y][at.x].get(); }

bool MapSection::isMovingEntity(Vec position) const {
    for (const auto &item : m_MovingEntities) {
        if (item->m_Position == position)
            return true;
    }
    return false;
}

void MapSection::writeToStream(std::ostream &stream,
                               const std::map<EntityType, int> &types,
                               Vec sectionPosition) const {
    stream << "SECTION " << sectionPosition << " "
           << types.find(m_BackgroundEntity->getType())->second << std::endl;

    for (const auto &row : m_Entities) {
        for (const auto &entity : row) {
            if (entity == nullptr) {
                stream << types.find(EntityType::VOID)->second << " ";
            } else {
                stream << types.find(entity->getType())->second << " ";
            }
        }
        stream << std::endl;
    }

    stream << "END SECTION" << std::endl;
}

void MapSection::writeMovingEntities(std::ostream &stream,
                                     const std::map<EntityType, int> &types,
                                     Vec sectionPosition) const {
    for (const auto &entity : m_MovingEntities) {
        stream << "ADD " << entity->m_Position << " " << sectionPosition << " "
               << types.find(entity->getType())->second << std::endl;
    }
}
