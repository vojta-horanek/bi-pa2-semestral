#ifndef TPOHB_STATS_H
#define TPOHB_STATS_H


#include "Entity.h"
#include "Hearth.h"
#include "../SDL_Helper.h"
#include <memory>

class Stats : public Entity {
private:
    int maxHealth;
    std::unique_ptr<Hearth> hearth;
public:
    explicit Stats(int maxHealth);

    void render(GameState &state, Vec position) override;
};


#endif //TPOHB_STATS_H
