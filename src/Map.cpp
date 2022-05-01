#include "Map.h"

bool Map::tryNavigateToSection(Vec inDirection) {
    Vec newSection = currentSection->first + inDirection;
    auto it = sections.find(newSection);
    if (it != sections.end()) {
        currentSection = it;
        return true;
    } else {
        return false;
    }
}

Map::MapSection &Map::getCurrentSection() {
    assert(currentSection != sections.end());
    return currentSection->second;
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
