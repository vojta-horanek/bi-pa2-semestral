#ifndef TPOHB_FIGHTSCREEN_H
#define TPOHB_FIGHTSCREEN_H

#include "GameState.h"
#include "Screen.h"
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
    std::shared_ptr<Player> player;
    std::shared_ptr<GameState> gameState;
    Texture background;
    std::unique_ptr<Stats> stats;

  public:
    FightScreen(std::shared_ptr<Player> player,
                std::shared_ptr<GameState> gameState, int width, int height);

    ~FightScreen() override;

    void onRender() override;

    void onEvent(SDL_Event event) override;

    bool popSelf() override;

    void attack();
};

#endif // TPOHB_FIGHTSCREEN_H
