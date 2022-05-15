#ifndef TPOHB_MAP_H
#define TPOHB_MAP_H

#include "MapParserState.h"
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
#include <functional>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

class Map {
  public:
    std::map<Vec, MapSection> sections;
    std::map<Vec, MapSection>::iterator currentSection = sections.end();

    MapSection &getCurrentSection();

    bool tryNavigateToSection(Vec inPlayerDirection);

    Result saveToFile(const std::string &path, const GameState &gameState);

    static std::shared_ptr<Map> loadFromFile(const std::string &fileName, GameState &gameState,
                            int width, int height);

  private:
    void writeSection(MapParserState section, std::ostream &output,
                      std::function<void(std::ostream &ostream)> writeFun);
};

#endif // TPOHB_MAP_H
