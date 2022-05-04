#include "Tree.h"
#include "../resources/strings/Paths.h"


Tree::Tree() : Entity(Texture(Paths::Bitmaps::tree, true)) {
    hasCollision = true;
}

