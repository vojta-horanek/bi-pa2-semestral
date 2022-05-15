#ifndef TPOHB_PATHS_H
#define TPOHB_PATHS_H

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "resources/"
#endif

#define BITMAPS_PATH RESOURCES_PATH "bitmaps/"

#define FONTS_PATH RESOURCES_PATH "fonts/"

#include <string>

using str = const char *const;

namespace Paths {
namespace Bitmaps {
static constexpr str apple = BITMAPS_PATH "apple.bmp";
static constexpr str axe = BITMAPS_PATH "axe.bmp";
static constexpr str player_axe = BITMAPS_PATH "player-axe.bmp";
static constexpr str bricks = BITMAPS_PATH "bricks.bmp";
static constexpr str grass = BITMAPS_PATH "grass.bmp";
static constexpr str hearth = BITMAPS_PATH "hearth.bmp";
static constexpr str inventory = BITMAPS_PATH "inventory.bmp";
static constexpr str zombie = BITMAPS_PATH "zombie.bmp";
static constexpr str player = BITMAPS_PATH "player.bmp";
static constexpr str player_anim = BITMAPS_PATH "player-anim.bmp";
static constexpr str stats = BITMAPS_PATH "stats.bmp";
static constexpr str stats_l = BITMAPS_PATH "stats-l.bmp";
static constexpr str stats_r = BITMAPS_PATH "stats-r.bmp";
static constexpr str sword = BITMAPS_PATH "sword.bmp";
static constexpr str player_sword = BITMAPS_PATH "player-sword.bmp";
static constexpr str tree = BITMAPS_PATH "tree.bmp";
static constexpr str invalid = BITMAPS_PATH "invalid.bmp";
static constexpr str menu_new = BITMAPS_PATH "new.bmp";
static constexpr str menu_new_selected = BITMAPS_PATH "new-selected.bmp";
static constexpr str menu_load = BITMAPS_PATH "load.bmp";
static constexpr str menu_load_selected = BITMAPS_PATH "load-selected.bmp";
static constexpr str menu_quit = BITMAPS_PATH "quit.bmp";
static constexpr str menu_quit_selected = BITMAPS_PATH "quit-selected.bmp";
static constexpr str menu_resume = BITMAPS_PATH "resume.bmp";
static constexpr str menu_resume_selected = BITMAPS_PATH "resume-selected.bmp";
static constexpr str menu_main_menu = BITMAPS_PATH "main-menu.bmp";
static constexpr str menu_main_menu_selected =
    BITMAPS_PATH "main-menu-selected.bmp";
static constexpr str menu_save = BITMAPS_PATH "save.bmp";
static constexpr str menu_save_selected = BITMAPS_PATH "save-selected.bmp";
static constexpr str title = BITMAPS_PATH "title.bmp";
static constexpr str fighting_background =
    BITMAPS_PATH "fighting-background.bmp";
static constexpr str menu_backdrop = BITMAPS_PATH "menu-backdrop.bmp";
static constexpr str screen_won = BITMAPS_PATH "screen-won.bmp";
static constexpr str screen_lost = BITMAPS_PATH "screen-lost.bmp";
} // namespace Bitmaps
namespace Fonts {
static constexpr str pixel = FONTS_PATH "pixel.ttf";
}
} // namespace Paths

#endif // TPOHB_PATHS_H
