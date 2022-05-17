#ifndef TPOHB_STATS_H
#define TPOHB_STATS_H

#include "Entity.h"
#include "Hearth.h"
#include <memory>

/**
 * This entity occupies more than one block
 * Renders players hearths
 */
class Stats : public Entity {
  public:
    explicit Stats(int maxHearthCount);

    void render(GameState &state, Vec position, bool withBackground = true);

  private:
    int m_MaxHealthCount;
    std::unique_ptr<Hearth> m_Hearth;
    Texture m_BackgroundLeft, m_BackgroundRight;

    /**
     * Re-maps a number from one range to another
     * from https://www.arduino.cc/reference/en/language/functions/math/map/
     * @param x the value
     * @param inMin minimal input value
     * @param inMax maximal input value
     * @param outMin minimal output value
     * @param outMax maximal output value
     * @return the value x mapped from range (inMin, inMax) to (outMin, outMax)
     */
    static int mapValue(int x, int inMin, int inMax, int outMin, int outMax);
};

#endif // TPOHB_STATS_H
