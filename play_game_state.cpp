#include "play_game_state.h"
#include "game.h"
#include "main_menu_state.h"

constexpr int thickness = 15;

PlayGameState::PlayGameState() :
    _paddleOnePosition({0 + thickness * 2, 768 / 2.0f}),
    _paddleOneDirection(0),
    _paddleTwoPosition({1024 - thickness * 2, 768 / 2.0f}),
    _paddleTwoDirection(0),
    _ballPosition({1024 / 2.0f, 768 / 2.0f}),
    _ballVelocity({-200.0f, 235.0f}) {}

void PlayGameState::enter() {
    // Initialize play game state
}

void PlayGameState::exit() {
    // Clean up play game state
}

void PlayGameState::processInput(Game &game, const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        game.changeState(std::make_unique<MainMenuState>());
        return;
    }

    // Get keyboard state for paddle control
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    _paddleOneDirection = 0;
    if (state[SDL_SCANCODE_W]) {
        _paddleOneDirection -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        _paddleOneDirection += 1;
    }

    _paddleTwoDirection = 0;
    if (state[SDL_SCANCODE_I]) {
        _paddleTwoDirection -= 1;
    }
    if (state[SDL_SCANCODE_K]) {
        _paddleTwoDirection += 1;
    }
}

void PlayGameState::update(Game &game, float deltaTime) {
    if (_paddleOneDirection != 0) {
        _paddleOnePosition.y += static_cast<float>(_paddleOneDirection) * 300.0f * deltaTime;

        if (_paddleOnePosition.y < 50 + thickness) {
            _paddleOnePosition.y = 50 + thickness;
        } else if (_paddleOnePosition.y > 768 - 50 - thickness) {
            _paddleOnePosition.y = 768 - 50 - thickness;
        }
    }
    if (_paddleTwoDirection != 0) {
        _paddleTwoPosition.y += static_cast<float>(_paddleTwoDirection) * 300.0f * deltaTime;

        if (_paddleTwoPosition.y < 50 + thickness) {
            _paddleTwoPosition.y = 50 + thickness;
        } else if (_paddleTwoPosition.y > 768 - 50 - thickness) {
            _paddleTwoPosition.y = 768 - 50 - thickness;
        }
    }
}

void PlayGameState::render(SDL_Renderer *renderer) {
    // Set draw color for renderer
    SDL_SetRenderDrawColor(renderer, 55, 125, 255, 255);
    // Clear back buffer to current draw color
    SDL_RenderClear(renderer);

    // Draw the game world
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
    SDL_Rect wall {};
    // Top wall
    wall.x = 0;
    wall.y = 0;
    wall.w = 1024;
    wall.h = thickness;
    SDL_RenderFillRect(renderer, &wall);
    // Bottom wall
    wall.y = 768 - thickness;
    SDL_RenderFillRect(renderer, &wall);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Paddles
    SDL_Rect paddleOne {
        static_cast<int>(_paddleOnePosition.x - thickness / 2.0f),
        static_cast<int>(_paddleOnePosition.y - 50),
        thickness,
        100
    };
    SDL_RenderFillRect(renderer, &paddleOne);
    SDL_Rect paddleTwo {
        static_cast<int>(_paddleTwoPosition.x - thickness / 2.0f),
        static_cast<int>(_paddleTwoPosition.y - 50),
        thickness,
        100
    };
    SDL_RenderFillRect(renderer, &paddleTwo);
}
