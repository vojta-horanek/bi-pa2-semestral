#ifndef TPOHB_RESUMEMENU_H
#define TPOHB_RESUMEMENU_H

#include "../GameState.h"
#include "../Map.h"
#include "Menu.h"
#include <memory>

class ResumeMenu : public Menu {
  public:
    ResumeMenu(int width, int height);

    ResumeMenu(int width, int height, std::shared_ptr<GameState> gameState,
               std::shared_ptr<Map> map);

    bool shouldClearBackStack() override;

  private:
    bool m_GoToMainMenu = false;
    std::shared_ptr<GameState> m_GameState;
    std::shared_ptr<Map> m_Map;

    void onItemSelected(int activeIndex) override;

    void onEscapePressed() override;

    void saveGame();
};

#endif // TPOHB_RESUMEMENU_H
