#ifndef TPOHB_MAP_H
#define TPOHB_MAP_H

#include <map>
#include <vector>
#include <cassert>
#include <string>
#include <memory>
#include "Vec.h"
#include "entity/Entity.h"
#include "entity/Grass.h"
#include "entity/Tree.h"
#include "entity/Bricks.h"
#include "entity/Apple.h"
#include "entity/Sword.h"
#include "entity/Axe.h"
#include "MapSection.h"
#include "Result.h"
#include <utility>

class Map {
private:
public:
    std::map<Vec, MapSection> sections;
    std::map<Vec, MapSection>::iterator currentSection = sections.end();
    MapSection &getCurrentSection();

     bool tryNavigateToSection(Vec inPlayerDirection);

     static Map loadFromFile(const std::string & fileName, GameState & gameState);
};


#endif //TPOHB_MAP_H
