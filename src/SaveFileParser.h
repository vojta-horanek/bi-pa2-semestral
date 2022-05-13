#ifndef TPOHB_SAVEFILEPARSER_H
#define TPOHB_SAVEFILEPARSER_H

#include <memory>
#include <string>
#include <vector>

#include "Result.h"
#include "entity/PickupEntity.h"
#include "entity/Weapon.h"
#include "EntityManager.h"

class SaveParserState {
  public:
    enum class Value {
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

  private:
    Value value = Value::none;

  public:
    SaveParserState();

    explicit SaveParserState(Value value);

    std::string toString() const;

    void reset();

    void set(Value val);

    void set(const SaveParserState &state);

    Value get() const;

    static SaveParserState fromString(const std::string &str);

    bool operator==(const SaveParserState &rhs) const;

    bool operator!=(const SaveParserState &rhs) const;

    bool operator==(Value rhs) const;

    bool operator!=(Value rhs) const;
};

class SaveFileParser {
  private:
    SaveParserState currentState;

    std::string mapFilePath;

    int playerHealth = -1;

    int playerCurrentHealth = -1;

    int playerDefaultDamage = -1;

    std::vector<std::unique_ptr<PickupEntity>> inventory;

    std::unique_ptr<Weapon> weapon = nullptr;

    std::map<int, EntityManger::Type> types;

    static std::pair<Result, int> readIntCommand(const std::string &line,
                                                 const std::string &expectedCommnad);

    Result parseNextLine(const std::string &line);

    Result areAllValuesSet() const;

  public:
    SaveFileParser();

    Result loadSaveFromFile(const std::string &fileName);

    std::string getMapFilePath() const;
    int getPlayerHealth() const;
    int getPlayerCurrentHealth() const;
    int getPlayerDefaultDamage() const;
    std::vector<std::unique_ptr<PickupEntity>> getInventory();
    std::unique_ptr<Weapon> getWeapon();
};

#endif // TPOHB_SAVEFILEPARSER_H
