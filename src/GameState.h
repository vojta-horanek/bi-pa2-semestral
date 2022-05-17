#ifndef TPOHB_GAMESTATE_H
#define TPOHB_GAMESTATE_H

#include "entity/Monster.fwd.h"
#include "entity/PickupEntity.fwd.h"
#include "entity/Weapon.fwd.h"
#include "render/Vec.h"
#include <memory>
#include <vector>

struct GameState {
    /**
     * Game running flag
     */
    bool m_Running = false;
    /**
     * Player won flag
     */
    bool m_Won = false;
    /**
     * Current player position
     */
    Vec m_PlayerPosition = Vec::max();
    /**
     * Players m_Inventory
     */
    std::vector<std::unique_ptr<PickupEntity>> m_Inventory;
    /**
     * Players weapon, nullptr it no weapon
     */
    std::unique_ptr<Weapon> m_Weapon;
    /**
     * A monster the player should fight with, nullptr for no fight
     */
    std::unique_ptr<Monster> m_Monster;
    /**
     * Players maximum health
     */
    int m_PlayerMaxHealth = 255;
    /**
     * Players current health
     */
    int m_PlayerCurrentHealth = m_PlayerMaxHealth;
    /**
     * Players default damage
     */
    int m_PlayerDefaultDamage = 5;
};

#endif // TPOHB_GAMESTATE_H
