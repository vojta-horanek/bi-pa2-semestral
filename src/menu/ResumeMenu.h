#ifndef TPOHB_RESUMEMENU_H
#define TPOHB_RESUMEMENU_H

#include "../GameState.h"
#include "../Map.h"
#include "Menu.h"
#include <memory>

class ResumeMenu : public Menu {
  private:
    bool goToMainMenu = false;
    std::shared_ptr<GameState> gameState;
    std::shared_ptr<Map> map;

    void onItemSelected(size_t activeIndex) override;

    void onEscapePressed() override;

    void saveGame();

  public:
    ResumeMenu(int width, int height);

    ResumeMenu(int width, int height, std::shared_ptr<GameState> gameState,
               std::shared_ptr<Map> map);

    bool shouldClearBackStack() override;
};

#endif // TPOHB_RESUMEMENU_H