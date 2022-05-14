#ifndef TPOHB_MAP_H
#define TPOHB_MAP_H

#include "MapSection.h"
#include "Result.h"
#include "Vec.h"
#include "entity/Apple.h"
#include "entity/Axe.h"
#include "entity/Bricks.h"
#include "entity/Entity.h"
#include "entity/Grass.h"
#include "entity/Sword.h"
#include "entity/Tree.h"
#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Map {
  public:
    std::map<Vec, MapSection> sections;
    std::map<Vec, MapSection>::iterator currentSection = sections.end();

    MapSection &getCurrentSection();

    bool tryNavigateToSection(Vec inPlayerDirection);

    static Map loadFromFile(const std::string &fileName, GameState &gameState,
                            int width, int height);
};

#endif // TPOHB_MAP_H
