#include "Game.h"

#include "FPSController.h"
#include "entity/Monster.h"
#include "Renderer.h"
#include "FightScreen.h"
#include "ResumeMenu.h"
#include "EndScreen.h"


Game::Game(int width, int height) : Screen(width, height),
                                    gameWidth(width / (REAL_PIXEL_SIZE * BLOCK_SIZE)),
                                    gameHeight(height / (REAL_PIXEL_SIZE * BLOCK_SIZE)) {
    gameState = std::make_shared<GameState>();
    inventory = std::make_unique<Inventory>(width);
    player = std::make_shared<Player>();
    stats = std::make_unique<Stats>(3);
}

Game::Game(int width, int height, const std::string &saveFile) : Game(width, height) {
    // TODO Load save file
}

Game::~Game() = default;


void Game::onRender() {

    if (!gameState->running) return;

    gameMap.getCurrentSection().render(*gameState);

    player->render(*gameState, gameState->playerPosition);

    inventory->render(*gameState, Vec(3, gameHeight));

    stats->render(*gameState, player->health, player->currentHealth, Vec(0, gameHeight));
}

void Game::onEvent(SDL_Event event) {
    if (!gameState->running) return;
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
                navigationDestination = std::make_unique<ResumeMenu>(width, height);
                break;
        }
    }
}

bool Game::loadMap(const std::string &file) {
    try {
        gameMap = Map::loadFromFile(file, *gameState, gameWidth, gameHeight);
        return true;
    } catch (std::invalid_argument &ex) {
        std::cerr << ex.what() << std::endl;
        return false;
    }
}

void Game::nextTurn() {
    avoidPlayerCollision();
    player->onTurn(*gameState, gameMap.getCurrentSection());

    gameMap.getCurrentSection().onTurn(*gameState);

    if (gameState->fight != nullptr) {
        navigationDestination = std::make_unique<FightScreen>(player, gameState, width, height);
    }

    if (gameState->won) {
        navigationDestination = std::make_unique<EndScreen>(true, width, height);
    }
}

void Game::avoidPlayerCollision() {
    Vec playerNexPos = player->getNextPosition(gameState->playerPosition);
    if (gameMap.getCurrentSection().isEdge(playerNexPos)) {

        Vec direction = player->getDirection();

        player->setDirection(0, 0);

        if (gameMap.tryNavigateToSection(direction)) {
            if (direction.x != 0) {
                int newX = 0;
                if (direction.x < 0) {
                    // Going from left screen to right screen
                    newX = gameWidth - 1;
                }
                gameState->playerPosition = Vec(newX, gameState->playerPosition.y);
            } else if (direction.y != 0) {
                int newY = 0;
                if (direction.y < 0) {
                    // Going from bottom screen to top screen
                    newY = gameHeight - 1;
                }
                gameState->playerPosition = Vec(gameState->playerPosition.x, newY);
            }
        }

    } else if (gameMap.getCurrentSection().collideWith(playerNexPos, *gameState)) {
        player->setDirection(0, 0);
    }
}

bool Game::popSelf() {
    return !gameState->running;
}

bool Game::clearBackStack() {
    return false;
}

void Game::onResume() {
    if (player->currentHealth <= 0) {
        navigationDestination = std::make_unique<EndScreen>(false, width, height);
    }
}

void Game::onCreate() {
    // TODO path

    if (args.empty()) {
        std::cerr << "Cannot run without a map file!" << std::endl;
        std::cerr << "You probably meant to run it like this: ./horanvoj examples/map" << std::endl;
        gameState->running = false;
    } else if (!loadMap(args[0])) {
        gameState->running = false;
    } else {
        gameState->running = true;
    }
}
