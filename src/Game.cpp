#include "Game.h"

#include "Texture.h"

bool Game::render() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        onEvent(event);
    }
    onUpdate();
    onRender();
    // TODO Wait FPS

    return gameState.running;
}

void Game::onRender() {
    SDL_RenderClear(getRenderer());

    Texture texture("resources/bitmaps/bricks.bmp", getRenderer());

    SDL_RenderCopy(getRenderer(), texture.get(), nullptr, nullptr);


    SDL_RenderPresent(getRenderer());
}

void Game::onUpdate() {

}

void Game::onEvent(SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT:
            gameState.running = false;
            break;
    }
}
