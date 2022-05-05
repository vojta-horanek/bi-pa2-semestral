#include "Monster.h"
#include "../MapSection.h"
#include "../resources/strings/Paths.h"

Monster::Monster() : MovingEntity(Texture(Paths::Bitmaps::monster)) {}

// The dumbest AI
void Monster::onTurn(GameState &state, MapSection &section) {
    Vec oldPos = position;

    if (position.withX(1).distanceTo(state.playerPosition) >
    position.withX(-1).distanceTo(state.playerPosition) ) {
        position.x--;
    } else if (position.withX(1).distanceTo(state.playerPosition) <
    position.withX(-1).distanceTo(state.playerPosition) ) {
        position.x++;
    } else
    if (position.withY(1).distanceTo(state.playerPosition) >
    position.withY(-1).distanceTo(state.playerPosition) ) {
        position.y--;
    } else if (position.withY(1).distanceTo(state.playerPosition) <
    position.withY(-1).distanceTo(state.playerPosition) ) {
        position.y++;
    }

    if (section.isEdge(position) || section.wouldCollide(position)) position = oldPos;
}
