#include "Inventory.h"

#include "../Game.h"

void Inventory::render(GameState &state, Vec position) {

    // Draw items with background
    size_t i;
    for (i = 0;i < state.inventory.size(); i++) {
        Vec newPos = position;
        newPos.x += (int) i;
        Entity::render(state, newPos);
        state.inventory[i]->render(state, newPos);
    }

    // Draw remaining backgrounds
    for (size_t rem = i; rem < maxWidth; rem++) {
        Vec newPos = position;
        newPos.x += (int) rem;
        Entity::render(state, newPos);
    }
}