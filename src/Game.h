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
    int m_BlocksWidth, m_BlocksHeight;

    /**
     * Called when the game should render
     */
    void onRender() override;

    /**
     * Called when an event occurs
     * @param event
     */
    void onEvent(SDL_Event event) override;

    /**
     * Called when a player finishes their turn
     */
    void nextTurn();

    /**
     * Avoids player collision if necessary.
     * Calls collision methods on entities.
     * Navigates to a different map section if needed.
     */
    void playerCollision();

    /**
     * Loads a save from the save file
     * @param saveFile
     * @return true if successful, false otherwise
     */
    bool loadSave(const std::string &saveFile);

    /**
     * Loads a map from the map file
     * @param mapFile
     * @return true if successful, false otherwise
     */
    bool loadMap(const std::string &mapFile);

    /**
     * Called when player attempts to drop their weapon
     */
    void dropWeapon();

    Game(int screenWidth, int screenHeight, int damage, int health,
         const std::string &saveFile);
};

#endif // TPOHB_GAME_H
