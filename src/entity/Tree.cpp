#include "Tree.h"
#include "../resources/strings/Paths.h"

Tree::Tree() : BlockEntity(Texture(Paths::Bitmaps::tree, true)) {}

EntityType Tree::getType() const noexcept { return EntityType::TREE; }