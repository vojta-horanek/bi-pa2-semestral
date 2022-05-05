#include "Game.h"

#include "FPSController.h"
#include "entity/Monster.h"
#include "Renderer.h"


Game::Game(int width, int height) : width(width), height(height) {
    inventory = std::make_unique<Inventory>(width);
    player = std::make_unique<Player>();
    stats = std::make_unique<Stats>(3);
}

Game::~Game() {
    Texture::clearStore();
}

bool Game::loop() {
    FPSController::renderStart();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        onEvent(event);
    }
    onRender();

    FPSController::renderEnd();

    return gameState.running;
}

void Game::onRender() {
    Renderer::getInstance().clear();

    gameMap.getCurrentSection().render(gameState);

    player->render(gameState, gameState.playerPosition);

    inventory->render(gameState, Vec(3, height));

    stats->render(gameState, Vec(0, height));

    Renderer::getInstance().present();
}


void Game::onEvent(SDL_Event event) {
    if (event.type == SDL_QUIT) {
        gameState.running = false;
    } else if (event.type == SDL_KEYDOWN) {
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
        }
    }
}

bool Game::loadMap(const std::string &file) {
    try {
        gameMap = Map::loadFromFile(file, gameState, width, height);
        return true;
    } catch (std::invalid_argument &ex) {
        std::cerr << ex.what() << std::endl;
        return false;
    }
}

void Game::nextTurn() {
    avoidPlayerCollision();
    player->onTurn(gameState, gameMap.getCurrentSection());

    gameMap.getCurrentSection().onTurn(gameState);
}

void Game::avoidPlayerCollision() {
    Vec playerNexPos = player->getNextPosition(gameState.playerPosition);
    if (gameMap.getCurrentSection().isEdge(playerNexPos)) {

        Vec direction = player->getDirection();

        player->setDirection(0, 0);

        if (gameMap.tryNavigateToSection(direction)) {
            if (direction.x != 0) {
                int newX = 0;
                if (direction.x < 0) {
                    // Going from left screen to right screen
                    newX = width - 1;
                }
                gameState.playerPosition = Vec(newX, gameState.playerPosition.y);
            } else if (direction.y != 0) {
                int newY = 0;
                if (direction.y < 0) {
                    // Going from bottom screen to top screen
                    newY = height - 1;
                }
                gameState.playerPosition = Vec(gameState.playerPosition.x, newY);
            }
        }

    } else if (gameMap.getCurrentSection().wouldCollide(playerNexPos) &&
               gameMap.getCurrentSection().get(playerNexPos)->onCollision(gameState)
            ) {
        player->setDirection(0, 0);
    }
}
