#include "FightScreen.h"

#include "Renderer.h"

FightScreen::FightScreen(std::unique_ptr<Monster> withMonster, int width, int height) : Screen(width, height) {
    Renderer::getInstance().selectDrawColor(0, 0xff, 0, 0xff);
    monster = std::move(withMonster);
}

void FightScreen::onRender() {

}


void FightScreen::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {

        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                fighting = false;
                break;
        }
    }


}

std::unique_ptr<Screen> FightScreen::getNavigationDestination() {
    return nullptr;
}

bool FightScreen::popSelf() {
    return !fighting;
}

bool FightScreen::clearBackStack() {
    return false;
}
