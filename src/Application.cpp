#include "Application.h"

#include "Window.h"
#include "menu/MainMenu.h"
#include "render/Renderer.h"
#include "render/Text.h"
#include "resources/strings/L10n.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stack>
#include <stdexcept>

Application::Application() : m_Window(Window(L10n::appName)) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        std::cerr << L10n::cannotInitializeSDL << " " << SDL_GetError()
                  << std::endl;
        return;
    }

    Renderer::getInstance().createRenderer(m_Window);

    if (!Text::initTTF()) {
        std::cerr << L10n::cannotInitializeTTF << " " << TTF_GetError()
                  << std::endl;
        return;
    }

    m_Backstack.emplace(
        std::make_unique<MainMenu>(m_Window.getSize().x, m_Window.getSize().y));
}

Application::~Application() {
    Text::destroyTTF();
    SDL_Quit();
}

int Application::run() {
    m_Window.show();

    while (!m_Backstack.empty()) {

        m_Backstack.top()->onLoop();

        if (m_Backstack.top()->m_ApplicationQuitRequested)
            break;

        auto nextScreen = m_Backstack.top()->getNavigationDestination();

        if (m_Backstack.top()->shouldClearBackStack()) {
            clearBackStack();
        } else if (m_Backstack.top()->shouldPopSelf()) {
            popBackStack();
            if (!m_Backstack.empty())
                m_Backstack.top()->onResume();
        }

        if (nextScreen != nullptr) {
            navigateTo(std::move(nextScreen));
        }
    }

    return EXIT_SUCCESS;
}

void Application::popBackStack() { m_Backstack.pop(); }

void Application::navigateTo(std::unique_ptr<Screen> destination) {
    m_Backstack.push(std::move(destination));
}

void Application::clearBackStack() {
    while (!m_Backstack.empty())
        m_Backstack.pop();
}
