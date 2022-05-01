#include "Stats.h"

void Stats::render(GameState &state, Vec position) {
    int i;
    for (i = 0; i < state.health && i < maxHealth; i++) {
        Vec pos = position.withX(i);

        Entity::render(state, pos);

        hearth->render(state, pos);
    }

    for (int j = i; j < maxHealth; j++) {
        Entity::render(state, position.withX(j));
    }
}
