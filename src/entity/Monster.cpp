#include "Monster.h"
#include "../EntityManager.h"
#include "../MapSection.h"
#include <cstdlib>
#include <ctime>

Monster::Monster(Texture texture) : Monster(texture, 1, true, 0) {}

Monster::Monster(Texture texture, int animationFrameCount,
                 bool animationSynchronized, int animationSpeed)
    : MovingEntity(texture, animationFrameCount, animationSynchronized,
                   animationSpeed) {
    srand(time(nullptr));
}

void Monster::onTurn(GameState &state, MapSection &section) {

    // The dumbest "AI" in any game...
    // It's pretty cool tho

    Vec newPosition = m_Position;

    if (rand() % 2) {
        // Align X newPosition
        int distanceRight =
            newPosition.withX(1).xDistance(state.m_PlayerPosition);
        int distanceLeft =
            newPosition.withX(-1).xDistance(state.m_PlayerPosition);
        if (distanceRight > distanceLeft) {
            newPosition.x--;
        } else if (distanceRight < distanceLeft) {
            newPosition.x++;
        }
    } else {
        // Align Y newPosition
        int distanceUp =
            newPosition.withY(-1).yDistance(state.m_PlayerPosition);
        int distanceDown =
            newPosition.withY(1).yDistance(state.m_PlayerPosition);
        if (distanceDown > distanceUp) {
            newPosition.y--;
        } else if (distanceDown < distanceUp) {
            newPosition.y++;
        }
    }

    if (newPosition == state.m_PlayerPosition) {
        m_RemoveOnNextTurn = onStartFight(state);
    } else if (!section.isEdge(newPosition) &&
               !section.collideWith(newPosition, state, false) &&
               !section.isMovingEntity(newPosition)) {
        m_Position = newPosition;
    }
}

void Monster::onFightBegin() { m_TextureScale = 2; }

void Monster::onFightEnd() {
    m_TextureScale = 1;
    resetAlpha();
}

bool Monster::onStartFight(GameState &state) {
    if (state.m_Monster != nullptr)
        return false;

    state.m_Monster = EntityManager::getMonster(getType());
    return true;
}