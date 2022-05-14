#include "FightScreen.h"

#include <utility>

#include "Game.h"
#include "Renderer.h"
#include "ResumeMenu.h"
#include "entity/Weapon.h"
#include "resources/strings/Paths.h"

FightScreen::FightScreen(std::shared_ptr<Player> player, std::shared_ptr<GameState> gameState,
                         int width, int height)
    : Screen(width, height), player(std::move(player)), gameState(std::move(gameState)) {
    background = Texture(Paths::Bitmaps::fighting_background);
    stats = std::make_unique<Stats>(3);
    this->gameState->fight->onFightBegin();
    this->player->onFightBegin();
}

void FightScreen::onRender() {
    background.renderFullscreen();

    int monsterXPos = 1;
    if (!playerTurn && !justShown)
        monsterXPos--;

    int playerXPos = 3;
    if (playerTurn && !justShown)
        playerXPos++;

    player->render(*gameState, Vec(playerXPos, 4));
    gameState->fight->render(*gameState, Vec(width / 2 / BLOCK_PIXELS + monsterXPos, 4));

    if (!fighting && (player->isFadeOut() || gameState->fight->isFadeOut())) {
        fadeFinished = true;
    }

    if (gameState->playerCurrentHealth > 0) {
        stats->render(*gameState, Vec(0, height / BLOCK_PIXELS), false);
    }
}

void FightScreen::onEvent(SDL_Event event) {
    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                navigationDestination = std::make_unique<ResumeMenu>(width, height);
                break;
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

bool FightScreen::popSelf() { return fadeFinished; }

FightScreen::~FightScreen() {
    player->onFightEnd();
    gameState->fight->onFightEnd();
    gameState->fight = nullptr;
}

void FightScreen::attack() {
    playerTurn = !playerTurn;

    gameState->playerCurrentHealth -= gameState->fight->getDamage();

    if (gameState->weapon != nullptr) {
        gameState->fight->currentHealth -=
            gameState->weapon->getDamage() + gameState->playerDefaultDamage;
    } else {
        gameState->fight->currentHealth -= gameState->playerDefaultDamage;
    }

    if (gameState->playerCurrentHealth <= 0) {
        player->fadeOut();
        if (gameState->weapon != nullptr) {
            gameState->weapon->fadeOut();
        }
        fighting = false;
    } else if (gameState->fight->currentHealth <= 0) {
        gameState->fight->fadeOut();
        fighting = false;
    }
}
