#include "Inventory.h"

#include "../Game.h"
#include "../resources/strings/Paths.h"

Inventory::Inventory(int maxItems)
    : Entity(Texture(Paths::Bitmaps::inventory)), m_MaxItems(maxItems) {}

void Inventory::render(GameState &state, Vec position) {

    // Draw backgrounds
    Vec backgroundPos = position;
    for (int i = 0; i < m_MaxItems; i++) {
        Entity::render(state, backgroundPos);
        backgroundPos.x++;
    }

    // Draw items
    Vec newPos = position;
    for (int i = 0; i < (int)state.m_Inventory.size() && i <= m_MaxItems; i++) {
        state.m_Inventory[i]->render(state, newPos);
        newPos.x++;
    }
}
