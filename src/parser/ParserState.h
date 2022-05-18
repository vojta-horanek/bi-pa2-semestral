#ifndef TPOHB_PARSERSTATE_H
#define TPOHB_PARSERSTATE_H

#include <optional>
#include <string>

template <typename Value> class ParserState {
  public:
    typedef Value value_type;

    ParserState() = default;

    virtual ~ParserState() = default;

    explicit ParserState(Value value) : m_Value(value) {}

    void reset() { m_Value = Value::none; }

    void set(Value value) { m_Value = value; };

    void set(const ParserState<Value> &state) { m_Value = state.m_Value; }

    Value get() const { return m_Value; }

    bool operator==(const ParserState<Value> &rhs) const {
        return m_Value == rhs.m_Value;
    }

    bool operator!=(const ParserState<Value> &rhs) const {
        return !(rhs == *this);
    }

    bool operator==(Value rhs) const { return m_Value == rhs; }

    bool operator!=(Value rhs) const { return m_Value != rhs; }

    virtual std::string toString() const = 0;

protected:
    Value m_Value = Value::none;

    static std::optional<Value>
    findValue(const std::string &name,
              const std::pair<Value, const std::string> *table,
              size_t tableSize) {
        for (size_t i = 0; i < tableSize; i++) {
            if (table[i].second == name)
                return table[i].first;
        }
        return {};
    }

    static std::optional<std::string>
    findValue(Value type, const std::pair<Value, const std::string> *table,
              size_t tableSize) {
        for (size_t i = 0; i < tableSize; i++) {
            if (table[i].first == type)
                return table[i].second;
        }
        return {};
    }

};

#endif // TPOHB_PARSERSTATE_H