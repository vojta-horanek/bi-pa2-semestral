#include "Game.h"

#include "EndScreen.h"
#include "FightScreen.h"
#include "MessageDialog.h"
#include "SaveManager.h"
#include "entity/Monster.h"
#include "menu/ResumeMenu.h"
#include "parser/SaveFileParser.h"
#include "render/FPSController.h"
#include "render/Renderer.h"
#include "utils/Result.h"

Game::Game(int screenWidth, int screenHeight, int damage, int health,
           const std::string &saveFile)
    : Screen(screenWidth, screenHeight),
      m_BlocksWidth(screenWidth / BLOCK_PIXELS),
      m_BlocksHeight((screenHeight / BLOCK_PIXELS) - 1) {
    m_GameState = std::make_shared<GameState>();
    m_Player = std::make_shared<Player>();
    m_GameMap = std::make_shared<Map>();
    m_Inventory = std::make_unique<Inventory>(screenWidth);
    m_Stats = std::make_unique<Stats>(3);

    m_GameState->m_Running = loadSave(saveFile);

    if (damage != -1) {
        m_GameState->m_PlayerDefaultDamage = (damage + 1) * 2;
    }

    if (health != -1) {
        m_GameState->m_PlayerMaxHealth = (health + 1) * 35;
        m_GameState->m_PlayerCurrentHealth = m_GameState->m_PlayerMaxHealth;
    }
}

Game::Game(int screenWidth, int screenHeight, const std::string &saveFile)
    : Game(screenWidth, screenHeight, -1, -1, saveFile) {}

Game::Game(int screenWidth, int screenHeight, int damage, int health)
    : Game(screenWidth, screenHeight, damage, health,
           SaveManager::getNewGameFilePath()) {}

void Game::onRender() {

    if (!m_GameState->m_Running)
        return;

    m_GameMap->getCurrentSection().render(*m_GameState);

    m_Player->render(*m_GameState, m_GameState->m_PlayerPosition);

    m_Inventory->render(*m_GameState, Vec(3, m_BlocksHeight));

    m_Stats->render(*m_GameState, Vec(0, m_BlocksHeight));
}

void Game::onEvent(SDL_Event event) {
    if (!m_GameState->m_Running)
        return;
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                m_Player->setDirection(0, -1);
                break;
            case SDLK_DOWN:
                m_Player->setDirection(0, 1);
                break;
            case SDLK_LEFT:
                m_Player->setDirection(-1, 0);
                break;
            case SDLK_RIGHT:
                m_Player->setDirection(1, 0);
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_LEFT:
            case SDLK_RIGHT:
                nextTurn();
                break;
            case SDLK_ESCAPE:
                m_NavigationDestination = std::make_unique<ResumeMenu>(
                    m_ScreenWidth, m_ScreenHeight, m_GameState, m_GameMap);
                break;
            case SDLK_q:
                dropWeapon();
                break;
        }
    }
}

bool Game::loadMap(const std::string &mapFile) {
    try {
        m_GameMap =
            Map::loadFromFile(mapFile, *m_GameState, m_BlocksWidth, m_BlocksHeight);
        return true;
    } catch (std::invalid_argument &ex) {
        showDialog(std::make_unique<MessageDialog>(m_ScreenWidth,
                                                   m_ScreenHeight, ex.what()));
        std::cerr << ex.what() << std::endl;
        return false;
    }
}

bool Game::loadSave(const std::string &saveFile) {

    SaveFileParser saveFileParser;

    Result saveFileResult = saveFileParser.loadSaveFromFile(saveFile);

    if (saveFileResult.isError) {
        std::cerr << saveFileResult.errorText << std::endl;
        showDialog(std::make_unique<MessageDialog>(m_ScreenWidth, m_ScreenHeight, saveFileResult.errorText));
        return false;
    }

    if (!loadMap(saveFileParser.getMapFilePath())) {
        return false;
    }

    m_GameState->m_PlayerMaxHealth = saveFileParser.getPlayerHealth();
    m_GameState->m_PlayerCurrentHealth =
        saveFileParser.getPlayerCurrentHealth();
    m_GameState->m_PlayerDefaultDamage =
        saveFileParser.getPlayerDefaultDamage();

    m_GameState->m_Inventory = saveFileParser.getInventory();
    m_GameState->m_Weapon = saveFileParser.getWeapon();
    return true;
}

void Game::dropWeapon() {

    if (m_GameState->m_Weapon != nullptr) {
        m_GameState->m_Weapon->unSync();
        m_GameMap->getCurrentSection().set(m_GameState->m_PlayerPosition,
                                           std::move(m_GameState->m_Weapon));
    }
}

void Game::nextTurn() {
    avoidPlayerCollision();
    m_Player->onTurn(*m_GameState, m_GameMap->getCurrentSection());

    m_GameMap->getCurrentSection().onTurn(*m_GameState);

    if (m_GameState->m_Monster != nullptr) {
        m_NavigationDestination = std::make_unique<FightScreen>(
            m_Player, m_GameState, m_ScreenWidth, m_ScreenHeight);
    }

    if (m_GameState->m_Won) {
        m_NavigationDestination =
            std::make_unique<EndScreen>(true, m_ScreenWidth, m_ScreenHeight);
    }
}

void Game::avoidPlayerCollision() {
    Vec playerNexPos = m_Player->getNextPosition(m_GameState->m_PlayerPosition);
    if (m_GameMap->getCurrentSection().isEdge(playerNexPos)) {

        Vec direction = m_Player->getDirection();

        m_Player->setDirection(0, 0);

        if (m_GameMap->tryNavigateToSection(direction)) {
            if (direction.x != 0) {
                int newX = 0;
                if (direction.x < 0) {
                    // Going from left screen to right screen
                    newX = m_BlocksWidth - 1;
                }
                m_GameState->m_PlayerPosition =
                    Vec(newX, m_GameState->m_PlayerPosition.y);
            } else if (direction.y != 0) {
                int newY = 0;
                if (direction.y < 0) {
                    // Going from bottom screen to top screen
                    newY = m_BlocksHeight - 1;
                }
                m_GameState->m_PlayerPosition =
                    Vec(m_GameState->m_PlayerPosition.x, newY);
            }
        }

    } else if (m_GameMap->getCurrentSection().collideWith(playerNexPos,
                                                          *m_GameState)) {
        m_Player->setDirection(0, 0);
    }
}

bool Game::shouldPopSelf() {
    return !m_GameState->m_Running && m_Dialog == nullptr;
}

bool Game::shouldClearBackStack() { return false; }

void Game::onResume() {
    if (m_GameState->m_PlayerCurrentHealth <= 0) {
        m_NavigationDestination =
            std::make_unique<EndScreen>(false, m_ScreenWidth, m_ScreenHeight);
    }
}