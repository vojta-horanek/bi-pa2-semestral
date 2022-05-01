#ifndef TPOHB_STATS_H
#define TPOHB_STATS_H


#include "Entity.h"
#include "Hearth.h"
#include "../SDL_Helper.h"
#include <memory>

class Stats : Entity {
private:
    int maxHealth;
    std::unique_ptr<Hearth> hearth;

public:

    explicit Stats(int maxHealth) : Entity(Texture::create("resources/bitmaps/stats.bmp")) {
        this->maxHealth = maxHealth;
        hearth = std::make_unique<Hearth>();
    }

    void render(GameState &state, Vec position) override;
};


#endif //TPOHB_STATS_H
