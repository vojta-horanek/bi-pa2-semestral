#include "Entity.h"
#include "../Game.h"
#include <iostream>

void Entity::render(GameState &state, Vec position) {

    updateState(state);

    Vec size = Texture::getAdjustedSize(texture);
    Vec coords = position.getScaled();

    SDL_Rect dstRect;
    dstRect.w = size.x;
    dstRect.h = size.y;
    dstRect.x = coords.x;
    dstRect.y = coords.y;

    SDL_RenderCopy(Game::getRenderer(), texture, nullptr, &dstRect);
}
