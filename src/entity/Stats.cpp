#include "Stats.h"
#include "../resources/strings/Paths.h"

Stats::Stats(int maxHealth) : Entity(Texture(Paths::Bitmaps::stats)) {
    this->maxHealth = maxHealth;
    hearth = std::make_unique<Hearth>();
    left = Texture(Paths::Bitmaps::stats_l);
    right = Texture(Paths::Bitmaps::stats_r);
}

void Stats::render(GameState &state, Vec position, bool withBackground) {
    int mappedHealth =
        map(state.playerCurrentHealth, 0, state.playerHealth, 1, maxHealth);
    int i;
    for (i = 0; i < mappedHealth && i < maxHealth; i++) {

        Vec pos = position.withX(i);

        if (withBackground) {
            if (i == 0) {
                left.renderBlock(pos);
            } else if (i == maxHealth - 1) {
                right.renderBlock(pos);
            } else {
                Entity::render(state, pos);
            }
        }

        hearth->render(state, pos);
    }

    if (withBackground) {
        for (int j = i; j < maxHealth; j++) {
            Vec pos = position.withX(j);
            if (i == 0) {
                left.renderBlock(pos);
            } else if (i == maxHealth - 1) {
                right.renderBlock(pos);
            } else {
                Entity::render(state, pos);
            }
        }
    }
}

int Stats::map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
