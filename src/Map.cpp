#include "Map.h"
#include "entity/EntityType.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <locale>

// TODO Separate
// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

bool Map::tryNavigateToSection(Vec inPlayerDirection) {
    // If player is going up/down its direction is negative/positive. Multiply by -1 to convert to map coordinates
    inPlayerDirection.y *= -1;
    Vec newSection = currentSection->first + inPlayerDirection;
    auto it = sections.find(newSection);
    if (it != sections.end()) {
        currentSection = it;
        return true;
    } else {
        return false;
    }
}

void unexpected(const std::string &line, int lineNum) {
    std::cerr << "Unexpected `" << line << "` at line " << lineNum << std::endl;
}


Map::MapSection &Map::getCurrentSection() {
    assert(currentSection != sections.end());
    return currentSection->second;
}

Map Map::loadFromFile(const std::string &fileName) {

    enum state {
        none,
        define,
        background,
        _sections,
        section,
        default_section,
        player
    };

    std::ifstream mapFile(fileName);
    if (!mapFile) throw std::invalid_argument("Could not open " + fileName);

    Map m;
    std::map<int, EntityType> types;
    int backgroundId = -1;

    std::string line;

    std::map<Vec, MapSection>::iterator currentSec;

    state currentState = none;

    int lineNum = 0;

    while (std::getline(mapFile, line)) {
        lineNum++;
        trim(line);
        if (line.empty() || line[0] == ';') continue;

        std::istringstream lineStream(line);

        if (line == "DEFINE") {
            if (currentState != none) {
                unexpected(line, lineNum);
            }
            currentState = define;
        } else if (line == "BACKGROUND") {
            if (currentState != none) {
                unexpected(line, lineNum);
            }
            currentState = background;
        } else if (line == "SECTIONS") {
            if (currentState != none) {
                unexpected(line, lineNum);
            }
            currentState = _sections;
        } else if (currentState == _sections) {
            if (line == "END SECTIONS") {
                currentState = none;
            } else {
                std::string typeDef;
                int x, y;
                lineStream >> typeDef >> x >> y;
                if (typeDef != "SECTION") {
                    unexpected(line, lineNum);
                }
                currentState = section;
                auto back = toNewEntity(types[backgroundId]);
                auto in = m.sections.emplace(Vec(x,y), MapSection(11, 7, std::move(back)));
                if (!in.second) {
                    unexpected(line, lineNum);
                }
                currentSec = in.first;
            }
        } else if (currentState == section) {
            if (line == "END SECTION") {
                currentState = _sections;
            } else {

                std::vector<std::unique_ptr<Entity>> row;
                // Parse map
                std::string token;
                while (std::getline(lineStream, token, ' ')) {
                    int num = -1;
                    std::istringstream tokenStream(token);
                    tokenStream >> num;
                    auto eType = types.find(num);
                    if (!tokenStream || eType == types.end()) {
                        unexpected(token, lineNum);
                    } else {
                        row.emplace_back(toNewEntity(eType->second));
                    }
                }
                currentSec->second.entities.emplace_back(std::move(row));

            }
        }  else if (currentState == define) {
            if (line == "END DEFINE") {
                currentState = none;
            } else {
                int number = -1;
                std::string typeName;
                lineStream >> number >> typeName;
                EntityType type = fromStr(typeName);
                if (type != INVALID && number >= 0 && lineStream) {
                    types[number] = type;
                } else {
                    unexpected(line, lineNum);
                }
            }
        } else if (currentState == background) {
            if (line == "END BACKGROUND") {
                currentState = none;
            } else {
                int number = -1;
                std::string action;
                lineStream >> action >> number;
                if (action == "SET"
                    && number >= 0
                    && types.find(number) != types.end()
                    && lineStream) {
                    backgroundId = number;
                } else {
                    unexpected(line, lineNum);
                }

            }
        }
    }


    for (
        const auto &item
            : types) {
        std::cout << item.first << " " << item.second <<
                  std::endl;
    }

    std::cout << backgroundId << std::endl;

    mapFile.

            close();

    return
            std::move(m);
}


void Map::MapSection::render(GameState &state) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (backgroundEntity != nullptr) {
                backgroundEntity->render(state, Vec(i, j));
            }
            if (entities[i][j] != nullptr) {
                entities[i][j]->render(state, Vec(i, j));
                if (entities[i][j]->removeOnNextRender) {
                    entities[i][j] = nullptr;
                }
            }
        }
    }
}
