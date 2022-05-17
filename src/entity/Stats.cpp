#include "Stats.h"
#include "../resources/strings/Paths.h"

Stats::Stats(int maxHearthCount) : Entity(Texture(Paths::Bitmaps::stats)) {
    m_MaxHealthCount = maxHearthCount;
    m_Hearth = std::make_unique<Hearth>();
    m_BackgroundLeft = Texture(Paths::Bitmaps::stats_l);
    m_BackgroundRight = Texture(Paths::Bitmaps::stats_r);
}

void Stats::render(GameState &state, Vec position, bool withBackground) {
    int mappedHealth = mapValue(state.m_PlayerCurrentHealth, 0,
                                state.m_PlayerMaxHealth, 1, m_MaxHealthCount);

    // Render background
    Vec backgroundPos = position;
    for (int i = 0; i < m_MaxHealthCount; i++) {
        if (withBackground) {
            if (i == 0) {
                m_BackgroundLeft.renderBlock(backgroundPos);
            } else if (i == m_MaxHealthCount - 1) {
                m_BackgroundRight.renderBlock(backgroundPos);
            } else {
                Entity::render(state, backgroundPos);
            }
        }
        backgroundPos.x++;
    }

    Vec hearthPos = position;
    for (int i = 0; i < mappedHealth && i < m_MaxHealthCount; i++) {
        m_Hearth->render(state, hearthPos);
        hearthPos.x++;
    }
}

int Stats::mapValue(int x, int inMin, int inMax, int outMin, int outMax) {
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
