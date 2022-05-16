#ifndef TPOHB_L10N_H
#define TPOHB_L10N_H

// Define used language
#define L10n L10n_en

using str = const char *const;

namespace L10n_en {
// section General
static constexpr str appName = "The planet of Hieronymus Bosch";
static constexpr str pressKeyToHide = "Press any key to hide...";
static constexpr str appNameShort = "TPOHB";
// section Errors
static constexpr str cannotInitializeSDL = "SDL Could not be initialized! (%s)";
static constexpr str cannotLoadBitmap = "Could not load bitmap from %s! (%s)";
// section Game
static constexpr str welcomeMessage = "Welcome";
static constexpr str createCharacter =
    "Create you character. Each point gives you advantage in the game in "
    "specific areas. You might split points to the following attributes:";
} // namespace L10n_en

#endif // TPOHB_L10N_H
