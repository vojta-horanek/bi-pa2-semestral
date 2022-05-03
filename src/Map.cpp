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

Map Map::loadFromFile(const std::string &fileName, GameState &gameState) {

    enum state {
        none,
        define,
        _sections,
        section,
        default_section,
        player
    };

    std::ifstream mapFile(fileName);
    if (!mapFile) throw std::invalid_argument("Could not open " + fileName);

    Map m;
    std::map<int, EntityType> types;
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
        } else if (line == "SECTIONS") {
            if (currentState != none) {
                unexpected(line, lineNum);
            }
            currentState = _sections;
        } else if (line == "DEFAULT SECTION") {
            if (currentState != none) {
                unexpected(line, lineNum);
            }
            currentState = default_section;
        } else if (line == "PLAYER") {
            if (currentState != none) {
                unexpected(line, lineNum);
            }
            currentState = player;
        } else if (currentState == player) {
            if (line == "END PLAYER") {
                currentState = none;
            } else {
                std::string command;
                int x, y;
                lineStream >> command >> x >> y;
                if (command != "SET" || !lineStream) {
                    unexpected(line, lineNum);
                }
                gameState.playerPosition = Vec(x, y);
            }
        } else if (currentState == default_section) {
            if (line == "END DEFAULT SECTION") {
                currentState = none;
            } else {
                std::string command;
                int x, y;
                lineStream >> command >> x >> y;
                if (command != "SET" || !lineStream) {
                    unexpected(line, lineNum);
                }
                m.currentSection = m.sections.find(Vec(x, y));
                if (m.currentSection == m.sections.end()) {
                    std::cerr << "Invalid section: " << x << " " << y << std::endl;
                }
            }
        } else if (currentState == _sections) {
            if (line == "END SECTIONS") {
                currentState = none;
            } else {
                std::string typeDef;
                int x, y, background = -1;
                lineStream >> typeDef >> x >> y >> background;
                if (typeDef != "SECTION" || !lineStream) {
                    unexpected(line, lineNum);
                }
                currentState = section;

                auto backgroundType = types.find(background);

                if (backgroundType == types.end()) {
                    unexpected(line, lineNum);
                }

                auto back = toNewEntity(backgroundType->second);
                auto in = m.sections.emplace(Vec(x, y), MapSection(SCREEN_WIDTH, SCREEN_HEIGHT, std::move(back)));
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
                        row.emplace_back(std::move(toNewEntity(eType->second)));
                    }
                }
                currentSec->second.entities.emplace_back(std::move(row));

            }
        } else if (currentState == define) {
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
        }
    }

    mapFile.close();

    return std::move(m);
}


void Map::MapSection::render(GameState &state) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (backgroundEntity != nullptr) {
                backgroundEntity->render(state, Vec(x, y));
            }
            if (entities[y][x] != nullptr) {
                entities[y][x]->render(state, Vec(x, y));
                if (entities[y][x]->removeOnNextRender) {
                    entities[y][x] = nullptr;
                }
            }
        }
    }
}
