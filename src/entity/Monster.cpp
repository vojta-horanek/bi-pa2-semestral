#include "Monster.h"

Monster::Monster() : MovingEntity(Texture("resources/bitmaps/invalid.bm")) {}

void Monster::onTurn(GameState &state) {
    this->position = state.playerPosition.withX(-1);
}
