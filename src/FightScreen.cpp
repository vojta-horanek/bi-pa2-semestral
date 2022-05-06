#include "FightScreen.h"

#include "Renderer.h"
#include "entity/Weapon.h"
#include "resources/strings/Paths.h"
#include <iostream>

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

    int monsterXPos = 1;
    if (!playerTurn && !justShown) monsterXPos--;

    int playerXPos = 3;
    if (playerTurn && !justShown) playerXPos++;

    player->render(*gameState, Vec(playerXPos, 4));
    gameState->fight->render(*gameState, Vec(width / 2 / REAL_PIXEL_SIZE / BLOCK_SIZE + monsterXPos, 4));

}


void FightScreen::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {

        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                if (!justShown) {
                    attack();
                } else {
                    justShown = false;
                    playerTurn = rand() % 2;
                }
                break;
            case SDLK_ESCAPE:
                fighting = false;
                break;
        }
    }
}

bool FightScreen::popSelf() {
    return !fighting;
}

FightScreen::~FightScreen() {
    player->onFightEnd();
    gameState->fight = nullptr;
}

void FightScreen::attack() {
    playerTurn = !playerTurn;

    player->health -= gameState->fight->getDamage();

    if (gameState->weapon != nullptr) {
        gameState->fight->currentHealth -= gameState->weapon->getDamage();
    } else {
        gameState->fight->currentHealth -= player->defaultDamage;
    }

    std::cout << player->health << std::endl;
    std::cout << gameState->fight->currentHealth << std::endl;

    if (player->health <= 0 || gameState->fight->currentHealth <= 0) {
        fighting = false;
    }
}
