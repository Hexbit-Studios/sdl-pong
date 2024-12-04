#include "game.h"
#include "main_menu_state.h"

constexpr int thickness = 15;

Game::Game() :
    _window(nullptr),
    _renderer(nullptr),
    _isRunning(true),
    _ticksCount(0) {
}

bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Create an SDL window
    _window = SDL_CreateWindow(
        "Pong", // Window title
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024, // Width of window
        768, // Height of window
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );
    if (!_window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // Create an SDL renderer
    _renderer = SDL_CreateRenderer(
        _window, // Window to create renderer for
        -1, // Let SDL pick first available graphics driver
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!_renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    // Start with main menu state
    _currentState = std::make_unique<MainMenuState>();
    _currentState->enter();

    return true;
}

void Game::shutdown() {
    SDL_Log("Shutting down game...");
    if (_currentState) {
        _currentState->exit();
    }
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}

void Game::run() {
    while (_isRunning) {
        _processInput();
        _update();
        _render();
    }
}

void Game::_processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            _isRunning = false;
            break;
        }

        if (_currentState) {
            _currentState->processInput(*this, event);
        }
    }
}

void Game::_update() {
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), _ticksCount + 16)) {
        // Do nothing
    }

    // Delta time is the difference in ticks from last frame
    // (converted to seconds)
    float deltaTime = static_cast<float>(SDL_GetTicks() - _ticksCount) / 1000.0f;
    // Update tick counts for next frame
    _ticksCount = SDL_GetTicks();

    // Clamp maximum delta time value
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    if (_currentState) {
        _currentState->update(*this, deltaTime);
    }
}

void Game::_render() {
    if (_currentState) {
        _currentState->render(_renderer);
    }
    SDL_RenderPresent(_renderer);
}


