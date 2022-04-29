#include "Game.h"

#include "FPSController.h"
#include "enitity/Grass.h"

bool Game::render() {
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


    for (const auto &item: entities) {
        item->render(gameState);
    }

    player->render(gameState);

    SDL_RenderPresent(getRenderer());
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
                player->setDirection(0, 0);
                break;
        }
    }

}

void Game::loadTestEntities() {
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            Entity * entity = new Grass();
            entity->setPosition(x, y);
            entities.emplace_back(entity);
        }
    }
}
