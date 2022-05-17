#include "Game.h"

#include "EndScreen.h"
#include "FPSController.h"
#include "FightScreen.h"
#include "MessageDialog.h"
#include "Renderer.h"
#include "Result.h"
#include "ResumeMenu.h"
#include "SaveFileParser.h"
#include "SaveManager.h"
#include "entity/Monster.h"

Game::Game(int width, int height, int damage, int health)
    : Screen(width, height), gameWidth(width / BLOCK_PIXELS),
      gameHeight((height / BLOCK_PIXELS) - 1) {
    gameState = std::make_shared<GameState>();
    player = std::make_shared<Player>();
    gameMap = std::make_shared<Map>();
    inventory = std::make_unique<Inventory>(width);
    stats = std::make_unique<Stats>(3);

    if (saveFilePath.empty()) {
        saveFilePath = SaveManager::getNewGameFilePath();
    }

    gameState->running = loadSave();

    if (damage != -1) {
        gameState->playerDefaultDamage = (damage + 1) * 2;
    }

    if (health != -1) {
        gameState->playerHealth = (health + 1) * 35;
        gameState->playerCurrentHealth = gameState->playerHealth;
    }
}

Game::Game(int width, int height, const std::string &saveFile)
    : Game(width, height, -1, -1) {
    saveFilePath = saveFile;
}

void Game::onRender() {

    if (!gameState->running)
        return;

    gameMap->getCurrentSection().render(*gameState);

    player->render(*gameState, gameState->playerPosition);

    inventory->render(*gameState, Vec(3, gameHeight));

    stats->render(*gameState, Vec(0, gameHeight));
}

void Game::onEvent(SDL_Event event) {
    if (!gameState->running)
        return;
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                player->setDirection(0, -1);
                break;
            case SDLK_DOWN:
                player->setDirection(0, 1);
                break;
            case SDLK_LEFT:
                player->setDirection(-1, 0);
                break;
            case SDLK_RIGHT:
                player->setDirection(1, 0);
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
                navigationDestination = std::make_unique<ResumeMenu>(
                    width, height, gameState, gameMap);
                break;
        }
    }
}

bool Game::loadMap(const std::string &file) {
    try {
        gameMap = Map::loadFromFile(file, *gameState, gameWidth, gameHeight);
        return true;
    } catch (std::invalid_argument &ex) {
        showDialog(std::make_unique<MessageDialog>(width, height, ex.what()));
        std::cerr << ex.what() << std::endl;
        return false;
    }
}

bool Game::loadSave() {

    SaveFileParser saveFileParser;

    Result saveFileResult = saveFileParser.loadSaveFromFile(saveFilePath);

    if (saveFileResult.isError) {
        std::cerr << saveFileResult.errorText << std::endl;
        return false;
    }

    if (!loadMap(saveFileParser.getMapFilePath())) {
        return false;
    }

    gameState->playerHealth = saveFileParser.getPlayerHealth();
    gameState->playerCurrentHealth = saveFileParser.getPlayerCurrentHealth();
    gameState->playerDefaultDamage = saveFileParser.getPlayerDefaultDamage();

    gameState->inventory = saveFileParser.getInventory();
    gameState->weapon = saveFileParser.getWeapon();
    return true;
}

void Game::nextTurn() {
    avoidPlayerCollision();
    player->onTurn(*gameState, gameMap->getCurrentSection());

    gameMap->getCurrentSection().onTurn(*gameState);

    if (gameState->fight != nullptr) {
        navigationDestination =
            std::make_unique<FightScreen>(player, gameState, width, height);
    }

    if (gameState->won) {
        navigationDestination =
            std::make_unique<EndScreen>(true, width, height);
    }
}

void Game::avoidPlayerCollision() {
    Vec playerNexPos = player->getNextPosition(gameState->playerPosition);
    if (gameMap->getCurrentSection().isEdge(playerNexPos)) {

        Vec direction = player->getDirection();

        player->setDirection(0, 0);

        if (gameMap->tryNavigateToSection(direction)) {
            if (direction.x != 0) {
                int newX = 0;
                if (direction.x < 0) {
                    // Going from left screen to right screen
                    newX = gameWidth - 1;
                }
                gameState->playerPosition =
                    Vec(newX, gameState->playerPosition.y);
            } else if (direction.y != 0) {
                int newY = 0;
                if (direction.y < 0) {
                    // Going from bottom screen to top screen
                    newY = gameHeight - 1;
                }
                gameState->playerPosition =
                    Vec(gameState->playerPosition.x, newY);
            }
        }

    } else if (gameMap->getCurrentSection().collideWith(playerNexPos,
                                                        *gameState)) {
        player->setDirection(0, 0);
    }
}

bool Game::popSelf() { return !gameState->running && m_Dialog == nullptr; }

bool Game::clearBackStack() { return false; }

void Game::onResume() {
    if (gameState->playerCurrentHealth <= 0) {
        navigationDestination =
            std::make_unique<EndScreen>(false, width, height);
    }
}

void Game::onCreate() {}
