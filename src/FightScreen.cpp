#include "FightScreen.h"

#include <utility>

#include "Renderer.h"
#include "entity/Weapon.h"
#include "resources/strings/Paths.h"
#include "ResumeMenu.h"
#include "Game.h"

FightScreen::FightScreen(
        std::shared_ptr<Player> player,
        std::shared_ptr<GameState> gameState,
        int width,
        int height
) : Screen(width, height), player(std::move(player)), gameState(std::move(gameState)) {
    background = Texture(Paths::Bitmaps::fighting_background);
    stats = std::make_unique<Stats>(3);
    this->gameState->fight->onFightBegin();
    this->player->onFightBegin();
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
            case SDLK_ESCAPE:
                navigateTo = std::make_unique<ResumeMenu>(width, height, false);
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

bool FightScreen::popSelf() {
    return fadeFinished;
}

FightScreen::~FightScreen() {
    player->onFightEnd();
    gameState->fight->onFightEnd();
    gameState->fight = nullptr;
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
        if (gameState->weapon != nullptr) {
            gameState->weapon->fadeOut();
        }
        fighting = false;
    } else if (gameState->fight->currentHealth <= 0) {
        gameState->fight->fadeOut();
        fighting = false;
    }
}

std::unique_ptr<Screen> FightScreen::getNavigationDestination() {
    return std::move(navigateTo);
}
