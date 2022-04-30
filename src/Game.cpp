#include "Game.h"

#include "FPSController.h"
#include "entity/Grass.h"
#include "entity/Tree.h"
#include "entity/Bricks.h"
#include <iostream>

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
    SDL_RenderClear(getRenderer());

    gameMap.getCurrentSection().render(gameState);

    player->render(gameState, gameState.playerPosition);

    inventory->render(gameState, Vec(0, SCREEN_HEIGHT));

    SDL_RenderPresent(getRenderer());
}


void Game::onEvent(SDL_Event event) {
    if (event.type == SDL_QUIT) {
        gameState.running = false;
    } else if (event.type == SDL_KEYDOWN && !gameState.turnFinished) {
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
                gameState.turnFinished = false;
                break;
        }
    }


    Vec playerNexPos = player->getNextPosition(gameState.playerPosition);
    if (gameMap.getCurrentSection().isEdge(playerNexPos)) {
        // TODO Set new section
        player->setDirection(0, 0);
    } else if (gameMap.getCurrentSection().wouldCollide(playerNexPos) &&
               gameMap.getCurrentSection().get(playerNexPos)->onCollision(gameState)) {
        player->setDirection(0, 0);
    }

}

void Game::loadTestEntities() {
    gameMap.test();
}