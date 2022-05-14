#ifndef TPOHB_HEARTH_H
#define TPOHB_HEARTH_H

#include "Entity.h"

class Hearth : public Entity {

  public:
    Hearth();

    EntityType getType() const noexcept override;
};

#endif // TPOHB_HEARTH_H
