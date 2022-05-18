#ifndef TPOHB_MAPPARSERSTATE_H
#define TPOHB_MAPPARSERSTATE_H

#include "ParserState.h"

enum class MapParserStateValue {
    player,
    default_section,
    section,
    sections,
    define,
    none,
    invalid,
    monsters
};

class MapParserState : public ParserState<MapParserStateValue> {
  private:
    static const std::pair<value_type, const std::string> m_StateTable[];
    static const size_t M_StateTableSize;

  public:
    MapParserState();

    explicit MapParserState(value_type value);

    std::string toString() const override;

    static MapParserState fromString(const std::string &str);
};

#endif // TPOHB_MAPPARSERSTATE_H