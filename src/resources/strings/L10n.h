#ifndef TPOHB_L10N_H
#define TPOHB_L10N_H

// Define used language
#define L10n L10n_en

using str = const char *const;

namespace L10n_en {
// section General
static constexpr str appName = "The planet of Hieronymus Bosch";
// section Errors
static constexpr str cannotInitializeSDL = "SDL Could not be initialized! (%s)";
static constexpr str cannotLoadBitmap = "Could not load bitmap from %s! (%s)";
// section Game
static constexpr str welcomeMessage = "Welcome";
} // namespace L10n_en

#endif // TPOHB_L10N_H
