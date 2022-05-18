#include "Boss.h"
#include "../render/Texture.h"
#include "../resources/strings/Paths.h"

// TODO Frame count
Boss::Boss() : Monster(Texture(Paths::Bitmaps::boss, true), 6, false, 5) {
    m_CurrentHealth = Boss::getMaxHealth();
}

int Boss::getDamage() { return 40; }

int Boss::getMaxHealth() { return 200; }

EntityType Boss::getType() const noexcept { return EntityType::BOSS; }
