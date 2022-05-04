#include "Stats.h"
#include "../resources/strings/Paths.h"

Stats::Stats(int maxHealth) : Entity(Texture(Paths::Bitmaps::stats)) {
    this->maxHealth = maxHealth;
    hearth = std::make_unique<Hearth>();
}

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
