#include "FightScreen.h"

#include "Renderer.h"
#include "entity/Weapon.h"
#include "resources/strings/Paths.h"

FightScreen::FightScreen(
        GameState *gameState,
        Player *player,
        int width, int height) : Screen(width, height),
                                 gameState(gameState),
                                 player(player) {
    background = Texture(Paths::Bitmaps::fighting_background);
    stats = std::make_unique<Stats>(3);
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

    if (!fighting && (player->isFadeOut() || gameState->fight->isFadeOut())) {
        fadeFinished = true;
    }

    if (player->currentHealth > 0) {
        stats->render(
                *gameState,
                player->health,
                player->currentHealth,
                Vec(0, height / REAL_PIXEL_SIZE / BLOCK_SIZE),
                false
        );
    }

}


void FightScreen::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
            case SDLK_SPACE:
                if (!justShown && fighting) {
                    attack();
                } else if (justShown) {
                    justShown = false;
                    playerTurn = rand() % 2;
                }
                break;
        }
    }
}

bool FightScreen::popSelf() {
    return fadeFinished;
}

FightScreen::~FightScreen() {
    if (player != nullptr && gameState != nullptr && gameState->fight != nullptr) {
        player->onFightEnd();
        gameState->fight->onFightEnd();
        gameState->fight = nullptr;
    }
}

void FightScreen::attack() {
    playerTurn = !playerTurn;

    player->currentHealth -= gameState->fight->getDamage();

    if (gameState->weapon != nullptr) {
        gameState->fight->currentHealth -= gameState->weapon->getDamage();
    } else {
        gameState->fight->currentHealth -= player->defaultDamage;
    }

    if (player->currentHealth <= 0) {
        player->fadeOut();
        fighting = false;
    } else if (gameState->fight->currentHealth <= 0) {
        gameState->fight->fadeOut();
        fighting = false;
    }
}
