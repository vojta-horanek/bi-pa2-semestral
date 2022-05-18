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
public:
    SaveParserState();

    explicit SaveParserState(value_type value);

    std::string toString() const override;

    static SaveParserState fromString(const std::string &str);

private:
    static const std::pair<value_type, const std::string> m_StateTable[];
    static const size_t m_StateTableSize;
};

#endif // TPOHB_SAVEPARSERSTATE_H