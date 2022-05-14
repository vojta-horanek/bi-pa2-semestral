#ifndef TPOHB_SAVEPARSERSTATE_H
#define TPOHB_SAVEPARSERSTATE_H

#include "ParserState.h"
#include <string>

enum class SaveParserStateValue {
    mapfile,
    inventory,
    weapon,
    health,
    current_health,
    default_damage,
    define,
    none,
    invalid
};

class SaveParserState : public ParserState<SaveParserStateValue> {
  private:
    static const std::pair<value_type, const std::string> typeTable[];
    static const size_t typeTableSize;

  public:
    SaveParserState();

    explicit SaveParserState(value_type value);

    std::string toString() const override;

    static SaveParserState fromString(const std::string &str);
};

#endif // TPOHB_SAVEPARSERSTATE_H