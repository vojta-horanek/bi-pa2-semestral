#ifndef TPOHB_PARSERSTATE_H
#define TPOHB_PARSERSTATE_H

#include <optional>
#include <string>

template <typename Value> class ParserState {
  public:
    typedef Value value_type;

  protected:
    Value value = Value::none;

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

  public:
    ParserState() = default;
    explicit ParserState(Value value) : value(value) {}

    void reset() { value = Value::none; }
    void set(Value value) { this->value = value; };
    void set(const ParserState<Value> &state) { this->value = state.value; }
    Value get() const { return value; }

    bool operator==(const ParserState<Value> &rhs) const {
        return value == rhs.value;
    }
    bool operator!=(const ParserState<Value> &rhs) const {
        return !(rhs == *this);
    }
    bool operator==(Value rhs) const { return value == rhs; }
    bool operator!=(Value rhs) const { return !(value == rhs); }

    virtual std::string toString() const = 0;
};

#endif // TPOHB_PARSERSTATE_H