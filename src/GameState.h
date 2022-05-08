#ifndef TPOHB_GAMESTATE_H
#define TPOHB_GAMESTATE_H


#include "Vec.h"
#include "entity/Entity.fwd.h"
#include "entity/Weapon.fwd.h"
#include "entity/Monster.fwd.h"
#include <vector>
#include <memory>

struct GameState {
    bool running = true;
    bool won = false;
    Vec playerPosition = Vec::max();
    std::vector<std::unique_ptr<Entity>> inventory;
    std::unique_ptr<Weapon> weapon;
    std::unique_ptr<Monster> fight;
};


#endif //TPOHB_GAMESTATE_H
