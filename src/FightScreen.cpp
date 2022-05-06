#include "FightScreen.h"

#include "Renderer.h"
#include "resources/strings/Paths.h"

// TODO Figure out how to pass around the weapon...
FightScreen::FightScreen(
        GameState *gameState,
        Player *player,
        int width, int height) : Screen(width, height),
                                 gameState(gameState),
                                 player(player) {
    background = Texture(Paths::Bitmaps::fighting_background);
    gameState->fight->onFightBegin();
    player->onFightBegin();
}

void FightScreen::onRender() {
    background.renderFullscreen();
    gameState->fight->render(*gameState, Vec(2, 4));
    player->render(*gameState, Vec(width / 2 / REAL_PIXEL_SIZE / BLOCK_SIZE + 2, 4));
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

FightScreen::~FightScreen() {
    player->onFightEnd();
    gameState->fight = nullptr;
}
