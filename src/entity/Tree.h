#ifndef TPOHB_TREE_H
#define TPOHB_TREE_H

#include "BlockEntity.h"

class Tree : public BlockEntity {
  public:
    Tree();

    EntityType getType() const noexcept override;
};

#endif // TPOHB_TREE_H
