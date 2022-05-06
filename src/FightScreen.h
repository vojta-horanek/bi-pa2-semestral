#ifndef TPOHB_FIGHTSCREEN_H
#define TPOHB_FIGHTSCREEN_H


#include "Screen.h"
#include "entity/Monster.h"
#include <memory>

class FightScreen : public Screen {
private:
    bool fighting = true;
    std::unique_ptr<Monster> monster;
public:
    FightScreen(std::unique_ptr<Monster> withMonster, int width, int height);

    void onRender() override;

    void onEvent(SDL_Event event) override;

    std::unique_ptr<Screen> getNavigationDestination() override;

    bool popSelf() override;

    bool clearBackStack() override;
};


#endif //TPOHB_FIGHTSCREEN_H
