#ifndef TPOHB_STATS_H
#define TPOHB_STATS_H


#include "Entity.h"
#include "Hearth.h"
#include <memory>

class Stats : public Entity {
private:
    int maxHealth;
    std::unique_ptr<Hearth> hearth;
    static int map(int x, int in_min, int in_max, int out_min, int out_max);
public:
    explicit Stats(int maxHealth);

    void render(GameState &state, int playerHealth, int playerCurrentHealth, Vec position);
};


#endif //TPOHB_STATS_H
