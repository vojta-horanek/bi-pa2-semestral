#ifndef TPOHB_GAMESTATE_H
#define TPOHB_GAMESTATE_H


#include "Vec.h"
#include "entity/Entity.fwd.h"
#include <vector>
#include <memory>

class GameState {
public:
    bool running = true;

    Vec playerPosition;
    std::vector<std::unique_ptr<Entity>> inventory;

    std::unique_ptr<Entity> weapon;

    bool turnFinished = false;
};


#endif //TPOHB_GAMESTATE_H
