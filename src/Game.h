#ifndef TPOHB_GAME_H
#define TPOHB_GAME_H

#include "GameState.h"
#include "Map.h"
#include "Screen.h"
#include "Window.h"
#include "entity/Inventory.h"
#include "entity/Player.h"
#include "entity/Stats.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Game : public Screen {
  public:
    /**
     * Creates a new game with specified attributes
     * @param screenWidth
     * @param screenHeight
     * @param damage default damage of the player chosen in the game creation
     * screen
     * @param health health of the player chosen in the game creation screen
     */
    Game(int screenWidth, int screenHeight, int damage, int health);

    /**
     * Loads a game from save file
     * @param screenWidth
     * @param screenHeight
     * @param saveFile path to the save file
     */
    Game(int screenWidth, int screenHeight, const std::string &saveFile);

    bool shouldPopSelf() override;

    bool shouldClearBackStack() override;

    void onResume() override;

  private:
    std::shared_ptr<Player> m_Player;
    std::unique_ptr<Inventory> m_Inventory;
    std::unique_ptr<Stats> m_Stats;
    std::shared_ptr<GameState> m_GameState;
    std::shared_ptr<Map> m_GameMap;

    /**
     * Width and Height of the game in blocks
     */
    int m_GameWidth, m_GameHeight;

    void onRender() override;

    void onEvent(SDL_Event event) override;

    void nextTurn();

    void avoidPlayerCollision();

    bool loadSave(const std::string &saveFile);

    bool loadMap(const std::string &mapFile);

    void dropWeapon();

    Game(int screenWidth, int screenHeight, int damage, int health,
         const std::string &saveFile);
};

#endif // TPOHB_GAME_H
