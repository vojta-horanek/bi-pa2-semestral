#include "MapParserState.h"

#include <stdexcept>

MapParserState::MapParserState(value_type value) : ParserState(value) {}

MapParserState::MapParserState() : ParserState() {}

const std::pair<MapParserState::value_type, const std::string>
    MapParserState::m_StateTable[] = {
        {value_type::player, "PLAYER"},
        {value_type::default_section, "DEFAULT_SECTION"},
        {value_type::sections, "SECTIONS"},
        {value_type::section, "SECTION"},
        {value_type::define, "DEFINE"},
        {value_type::none, "NONE"},
        {value_type::monsters, "MONSTERS"}};

const size_t MapParserState::M_StateTableSize =
    sizeof(m_StateTable) / sizeof(m_StateTable[0]);

std::string MapParserState::toString() const {
    auto optValue = findValue(m_Value, m_StateTable, M_StateTableSize);
    if (!optValue)
        throw std::invalid_argument("Unknown state!");
    return *optValue;
}

MapParserState MapParserState::fromString(const std::string &str) {
    auto optValue = findValue(str, m_StateTable, M_StateTableSize);
    if (!optValue)
        return MapParserState(value_type::invalid);
    return MapParserState(*optValue);
}