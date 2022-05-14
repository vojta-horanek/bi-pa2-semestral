#ifndef TPOHB_SAVEFILEPARSER_H
#define TPOHB_SAVEFILEPARSER_H

#include <memory>
#include <string>
#include <vector>

#include "EntityManager.h"
#include "Result.h"
#include "SaveParserState.h"
#include "entity/PickupEntity.h"
#include "entity/Weapon.h"

class SaveFileParser {
  private:
    SaveParserState currentState;

    std::string mapFilePath;

    int playerHealth = -1;

    int playerCurrentHealth = -1;

    int playerDefaultDamage = -1;

    std::vector<std::unique_ptr<PickupEntity>> inventory;

    std::unique_ptr<Weapon> weapon = nullptr;

    std::map<int, EntityType> types;

    static std::pair<Result, int>
    readIntCommand(const std::string &line, const std::string &expectedCommnad);

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
