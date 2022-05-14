#include "SaveParserState.h"

#include <stdexcept>
#include <string>

SaveParserState::SaveParserState(value_type value) : ParserState(value) {}

SaveParserState::SaveParserState() = default;

const std::pair<SaveParserState::value_type, const std::string>
    SaveParserState::typeTable[] = {
        {value_type::mapfile, "MAPFILE"},
        {value_type::inventory, "INVENTORY"},
        {value_type::weapon, "WEAPON"},
        {value_type::health, "HEALTH"},
        {value_type::current_health, "CURRENT_HEALTH"},
        {value_type::default_damage, "DEFAULT_DAMAGE"},
        {value_type::define, "DEFINE"},
        {value_type::none, "NONE"}};

const size_t SaveParserState::typeTableSize =
    sizeof(typeTable) / sizeof(typeTable[0]);

std::string SaveParserState::toString() const {
    auto optValue = findValue(value, typeTable, typeTableSize);
    if (!optValue)
        throw std::invalid_argument("Unknown state!");
    return *optValue;
}

SaveParserState SaveParserState::fromString(const std::string &str) {
    auto optValue = findValue(str, typeTable, typeTableSize);
    if (!optValue)
        return SaveParserState(value_type::invalid);
    return SaveParserState(*optValue);
}