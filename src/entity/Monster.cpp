#include "Monster.h"
#include "../MapSection.h"
#include "../resources/strings/Paths.h"

Monster::Monster() : MovingEntity(Texture(Paths::Bitmaps::monster)) {}

void Monster::onTurn(GameState &state, MapSection &section) {
    position = state.playerPosition.withX(-1);
    if (section.isEdge(position) || section.wouldCollide(position)) {
        position = state.playerPosition.withX(1);
    }
}
