#ifndef TPOHB_L10N_H
#define TPOHB_L10N_H

// Define used language
#define L10n L10n_en

using str = const char *const;

namespace L10n_en {
static constexpr str appName = "The planet of Hieronymus Bosch";
static constexpr str pressKeyToHide = "Press any key to hide...";
static constexpr str appNameShort = "TPOHB";
static constexpr str cannotInitializeSDL = "SDL Could not be initialized!";
static constexpr str cannotLoadBitmap = "Could not load bitmap from!";
static constexpr str unknownError = "Unknown error occured";
static constexpr str createCharacter =
    "Create you character. Each point gives you advantage in the game in "
    "specific areas. You might split points to the following attributes:";
static constexpr str health = "Health: ";
static constexpr str yourHealth = "Your health: ";
static constexpr str monsterHealth = "Monster health: ";
static constexpr str damage = "Damage: ";
static constexpr str noPointsAvailable =
    "You don't have any more points available...\nDecrease a different "
    "attribute to increase this one.";
static constexpr str cannotBeLessThanZero =
    "Attribute cannot be less than zero...";
static constexpr str createNewGame = "Create new game";
static constexpr str pointsAvailable = "Points available: ";
static constexpr str toContinuePressEnter = "To continue, press enter.";
static constexpr str useAllPoints = "You should probably use all your points.";
static constexpr str help = "Help";
static constexpr str loadGame = "Load game";
static constexpr str newGame = "New game";
static constexpr str saveGame = "Save game";
static constexpr str mainMenu = "Main menu";
static constexpr str resume = "Resume";
static constexpr str quit = "Quit";
static constexpr str helpText =
    "Arrow keys: movement\nQ: drop weapon\nSpace/Enter: attack (in fight)";

} // namespace L10n_en

#endif // TPOHB_L10N_H
