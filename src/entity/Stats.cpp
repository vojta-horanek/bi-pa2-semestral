#include "Stats.h"
#include "../resources/strings/Paths.h"

Stats::Stats(int maxHealth) : Entity(Texture(Paths::Bitmaps::stats)) {
    this->maxHealth = maxHealth;
    hearth = std::make_unique<Hearth>();
}

void Stats::render(GameState &state, int playerHealth, int playerCurrentHealth, Vec position, bool withBackground) {
    int mappedHealth = map(playerCurrentHealth, 0, playerHealth, 1, maxHealth);
    int i;
    for (i = 0; i < mappedHealth && i < maxHealth; i++) {
        Vec pos = position.withX(i);

        if (withBackground) {
            Entity::render(state, pos);
        }

        hearth->render(state, pos);
    }

    if (withBackground) {
        for (int j = i; j < maxHealth; j++) {
            Entity::render(state, position.withX(j));
        }
    }
}

int Stats::map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
