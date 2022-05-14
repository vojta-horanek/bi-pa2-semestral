#include "Monster.h"
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

    Vec newPosition = position;

    if (rand() % 2) {
        // Align X newPosition
        int distanceRight =
            newPosition.withX(1).xDistance(state.playerPosition);
        int distanceLeft =
            newPosition.withX(-1).xDistance(state.playerPosition);
        if (distanceRight > distanceLeft) {
            newPosition.x--;
        } else if (distanceRight < distanceLeft) {
            newPosition.x++;
        }
    } else {
        // Align Y newPosition
        int distanceUp = newPosition.withY(-1).yDistance(state.playerPosition);
        int distanceDown = newPosition.withY(1).yDistance(state.playerPosition);
        if (distanceDown > distanceUp) {
            newPosition.y--;
        } else if (distanceDown < distanceUp) {
            newPosition.y++;
        }
    }

    if (newPosition == state.playerPosition) {
        removeOnNextTurn = true;
        onFight(state);
    } else if (!section.isEdge(newPosition) &&
               !section.collideWith(newPosition, state, false) &&
               !section.isMovingEntity(newPosition)) {
        position = newPosition;
    }
}

void Monster::onFightBegin() { scale = 2; }

void Monster::onFightEnd() {
    scale = 1;
    resetAlpha();
}