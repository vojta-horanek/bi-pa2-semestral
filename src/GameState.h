#ifndef TPOHB_GAMESTATE_H
#define TPOHB_GAMESTATE_H

#include "Vec.h"
#include "entity/Monster.fwd.h"
#include "entity/PickupEntity.fwd.h"
#include "entity/Weapon.fwd.h"
#include <memory>
#include <vector>

struct GameState {
    bool running = false;
    bool won = false;
    Vec playerPosition = Vec::max();
    std::vector<std::unique_ptr<PickupEntity>> inventory;
    std::unique_ptr<Weapon> weapon;
    std::unique_ptr<Monster> fight;
    int playerHealth = 255;
    int playerCurrentHealth = playerHealth;
    int playerDefaultDamage = 5;
};

#endif // TPOHB_GAMESTATE_H
