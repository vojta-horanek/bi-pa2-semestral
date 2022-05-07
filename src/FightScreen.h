#ifndef TPOHB_FIGHTSCREEN_H
#define TPOHB_FIGHTSCREEN_H


#include "Screen.h"
#include "GameState.h"
#include "entity/Monster.h"
#include "entity/Player.h"
#include "entity/Stats.h"
#include <memory>

class FightScreen : public Screen {
private:
    bool justShown = true;
    bool fadeFinished = false;
    bool fighting = true;
    bool playerTurn = true;
    Player *player;
    Texture background;
    GameState *gameState;
    std::unique_ptr<Stats> stats;
    std::unique_ptr<Screen> navigateTo = nullptr;
public:
    FightScreen(GameState *gameState, Player *player, int width, int height);

    ~FightScreen() override;

    void onRender() override;

    void onEvent(SDL_Event event) override;

    bool popSelf() override;

    void attack();

    std::unique_ptr<Screen> getNavigationDestination() override;

};


#endif //TPOHB_FIGHTSCREEN_H
