#ifndef TPOHB_GAMESTATE_H
#define TPOHB_GAMESTATE_H


#include "Vec.h"
#include "entity/Entity.fwd.h"
#include "entity/Weapon.fwd.h"
#include <vector>
#include <memory>

struct GameState {
    bool running = true;
    Vec playerPosition;
    int health = 3;
    std::vector<std::unique_ptr<Entity>> inventory;
    std::unique_ptr<Weapon> weapon;
};


#endif //TPOHB_GAMESTATE_H
