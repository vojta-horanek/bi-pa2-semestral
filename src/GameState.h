#ifndef TPOHB_GAMESTATE_H
#define TPOHB_GAMESTATE_H


#include "Vec.h"
#include "entity/Entity.fwd.h"
#include "entity/Weapon.fwd.h"
#include <vector>
#include <memory>

class GameState {
public:
    bool running = true;

    Vec playerPosition = Vec(1,1);
    int health = 3;
    std::vector<std::unique_ptr<Entity>> inventory;

    std::unique_ptr<Weapon> weapon;

};


#endif //TPOHB_GAMESTATE_H
