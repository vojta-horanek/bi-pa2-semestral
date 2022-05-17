#ifndef TPOHB_MAP_H
#define TPOHB_MAP_H

#include "MapSection.h"
#include "entity/Apple.h"
#include "entity/Axe.h"
#include "entity/Bricks.h"
#include "entity/Entity.h"
#include "entity/Grass.h"
#include "entity/Sword.h"
#include "entity/Tree.h"
#include "parser/MapParserState.h"
#include "render/Vec.h"
#include "utils/Result.h"
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
    std::map<Vec, MapSection> m_Sections;
    std::map<Vec, MapSection>::iterator currentSection = m_Sections.end();

    MapSection &getCurrentSection();

    bool tryNavigateToSection(Vec inPlayerDirection);

    Result saveToFile(const std::string &path, const GameState &gameState);

    static std::shared_ptr<Map> loadFromFile(const std::string &fileName,
                                             GameState &gameState, int width,
                                             int height);

  private:
    static void
    writeSection(const MapParserState &section, std::ostream &output,
                 const std::function<void(std::ostream &ostream)> &writeFun);
};

#endif // TPOHB_MAP_H
