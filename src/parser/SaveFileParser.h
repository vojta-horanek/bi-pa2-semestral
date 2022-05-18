#ifndef TPOHB_SAVEFILEPARSER_H
#define TPOHB_SAVEFILEPARSER_H

#include <memory>
#include <string>
#include <vector>

#include "../EntityManager.h"
#include "../entity/PickupEntity.h"
#include "../entity/Weapon.h"
#include "../utils/Result.h"
#include "SaveParserState.h"

class SaveFileParser {
  public:
    SaveFileParser();

    Result loadSaveFromFile(const std::string &fileName);

    std::string getMapFilePath() const;

    int getPlayerHealth() const;

    int getPlayerCurrentHealth() const;

    int getPlayerDefaultDamage() const;

    std::vector<std::unique_ptr<PickupEntity>> getInventory();

    std::unique_ptr<Weapon> getWeapon();

  private:
    SaveParserState m_CurrentState;

    std::string m_MapFilePath;

    int m_PlayerMaxHealth = -1;

    int m_PlayerCurrentHealth = -1;

    int m_PlayerDefaultDamage = -1;

    std::vector<std::unique_ptr<PickupEntity>> m_Inventory;

    std::unique_ptr<Weapon> m_Weapon = nullptr;

    std::map<int, EntityType> m_Types;

    static std::pair<Result, int>
    readIntCommand(const std::string &line, const std::string &expectedCommnad);

    Result parseNextLine(const std::string &line);

    Result areAllValuesSet() const;
};

#endif // TPOHB_SAVEFILEPARSER_H
