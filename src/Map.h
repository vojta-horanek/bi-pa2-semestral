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

    /**
     * An iterator to the current section in the map
     * Since map does not change in runtime, this
     */
    std::map<Vec, MapSection>::iterator m_CurrentSectionIt = m_Sections.end();

    /**
     *
     * @return a reference to the current map section
     */
    MapSection &getCurrentSection();

    /**
     * Tries to navigate the player to a different section based on their
     * direction
     * @param playerDirection
     * @return true if navigation succeeded, else otherwise
     */
    bool tryNavigateToSection(Vec playerDirection);

    /**
     * Saves the map to the file provided in path
     * @param path
     * @param gameState
     * @return
     */
    Result saveToFile(const std::string &path, const GameState &gameState);

    /**
     * Loads the map from the filename
     * @param fileName
     * @param gameState
     * @param blocksWidth
     * @param blocksHeight
     * @return a shared pointer to the map object
     */
    static std::shared_ptr<Map> loadFromFile(const std::string &fileName,
                                             GameState &gameState,
                                             int blocksWidth, int blocksHeight);

  private:
    /**
     * Writes a section in file.
     * @param section the section to write
     * @param output the stream to write to
     * @param writeFun a function invoked between the begging and end of the
     * section
     */
    static void writeFileSection(
        const MapParserState &section, std::ostream &output,
        const std::function<void(std::ostream &ostream)> &writeFun);
};

#endif // TPOHB_MAP_H
