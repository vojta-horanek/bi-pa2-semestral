#ifndef TPOHB_FIGHTSCREEN_H
#define TPOHB_FIGHTSCREEN_H


#include "Screen.h"
#include "GameState.h"
#include "entity/Monster.h"
#include "entity/Player.h"
#include <memory>

class FightScreen : public Screen {
private:
    bool fighting = true;
    Texture background;
    GameState * gameState;
    Player * player;
public:
    FightScreen(GameState * gameState, Player * player, int width, int height);

    ~FightScreen() override;

    void onRender() override;

    void onEvent(SDL_Event event) override;

    std::unique_ptr<Screen> getNavigationDestination() override;

    bool popSelf() override;

    bool clearBackStack() override;
};


#endif //TPOHB_FIGHTSCREEN_H
