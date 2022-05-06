#include "Monster.h"
#include "../MapSection.h"
#include <ctime>
#include <cstdlib>

Monster::Monster(Texture texture) : MovingEntity(texture) {
    srand(time(nullptr));
}

void Monster::onTurn(GameState &state, MapSection &section) {

    // The dumbest "AI" in any game...
    // It's pretty cool tho

    Vec newPosition = position;

    if (rand() % 2) {
        // Align X newPosition
        int distanceRight = newPosition.withX(1).xDistance(state.playerPosition);
        int distanceLeft = newPosition.withX(-1).xDistance(state.playerPosition);
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

    if (!section.isEdge(newPosition) &&
        !section.collideWith(newPosition, state, false) &&
        !section.isMovingEntity(newPosition) &&
        newPosition != state.playerPosition) {
        position = newPosition;
    }
}
