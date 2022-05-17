#ifndef TPOHB_FIGHTSCREEN_H
#define TPOHB_FIGHTSCREEN_H

#include "GameState.h"
#include "Screen.h"
#include "entity/Monster.h"
#include "entity/Player.h"
#include "entity/Stats.h"
#include "render/Text.h"
#include <memory>

class FightScreen : public Screen {
  public:
    FightScreen(std::shared_ptr<Player> player,
                std::shared_ptr<GameState> gameState, int screenWidth,
                int screenHeight);

    ~FightScreen() override;

    void onRender() override;

    void onEvent(SDL_Event event) override;

    bool shouldPopSelf() override;

    void attack();

  private:
    bool m_IsJustShown = true;
    bool m_IsFadeFinished = false;
    bool m_IsFighting = true;
    bool m_IsPlayerTurn = true;
    std::shared_ptr<Player> m_Player;
    std::unique_ptr<Stats> m_Stats;
    std::shared_ptr<GameState> m_GameState;
    Texture m_BackgroundTexture;
    Text m_PlayerHealthText;
    Text m_MonsterHealthText;
};

#endif // TPOHB_FIGHTSCREEN_H
