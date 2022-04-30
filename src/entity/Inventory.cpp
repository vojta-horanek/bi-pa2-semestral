#include "Inventory.h"

#include "../Game.h"

void Inventory::render(GameState &state, Vec position) {


    // Draw items with background
    size_t i;
    for (i = 0;i < state.inventory.size(); i++) {
        Vec newPos = position;
        newPos.x += (int) i;
        renderBackground(newPos);
        state.inventory[i]->render(state, Vec((int) i, position.y));
    }

    // Draw remaining backgrounds
    for (size_t rem = i; rem < maxWidth; rem++) {
        Vec newPos = position;
        newPos.x += (int) rem;
        renderBackground(newPos);
    }
}

void Inventory::renderBackground(Vec position) {
    Vec size = Texture::getAdjustedSize(texture);
    Vec coords = position.getScaled();

    SDL_Rect dstRect;
    dstRect.w = size.x;
    dstRect.h = size.y;
    dstRect.x = coords.x;
    dstRect.y = coords.y;

    SDL_RenderCopy(Game::getRenderer(), texture, nullptr, &dstRect);
}
