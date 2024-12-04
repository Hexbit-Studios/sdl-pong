#include "practice_mode_state.h"
#include "game.h"
#include "main_menu_state.h"

constexpr int thickness = 15;

PracticeModeState::PracticeModeState() :
    _paddlePosition({0 + thickness * 2, 768 / 2.0f}),
    _paddleDirection(0),
    _ballPosition({1024 / 2.0f, 768 / 2.0f}),
    _ballVelocity({-200.0f, 235.0f}) {}

void PracticeModeState::enter() {
    // Initialize practice mode
}

void PracticeModeState::exit() {
    // Clean up practice mode
}

void PracticeModeState::processInput(Game &game, const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        game.changeState(std::make_unique<MainMenuState>());
        return;
    }

    // Get keyboard state for paddle control
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    _paddleDirection = 0;
    if (state[SDL_SCANCODE_W]) {
        _paddleDirection -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        _paddleDirection += 1;
    }
}

void PracticeModeState::update(Game &game, const float deltaTime) {
    if (_paddleDirection != 0) {
        _paddlePosition.y += static_cast<float>(_paddleDirection) * 300.0f * deltaTime;

        if (_paddlePosition.y < 50 + thickness) {
            _paddlePosition.y = 50 + thickness;
        } else if (_paddlePosition.y > 768 - 50 - thickness) {
            _paddlePosition.y = 768 - 50 - thickness;

        }
    }

    // Update ball position based on ball velocity
    _ballPosition.x += _ballVelocity.x * deltaTime;
    _ballPosition.y += _ballVelocity.y * deltaTime;

    // Handle ball hitting walls
    if (_ballPosition.y <= thickness && _ballVelocity.y < 0.0f) {
        _ballVelocity.y *= -1;
    }
    if (_ballPosition.y >= 768 - thickness && _ballVelocity.y > 0.0f) {
        _ballVelocity.y *= -1;
    }
    if (_ballPosition.x >= 1024 - thickness && _ballVelocity.x > 0.0f) {
        _ballVelocity.x *= -1;
    }
    // If ball goes off-screen, reset ball
    if (_ballPosition.x <= 0) {
        _ballPosition = {1024 / 2.0f, 768 / 2.0f};
        _ballVelocity = {-200.0f, 235.0f};
    }

    // Ball paddle collision
    auto diff = _paddlePosition.y - _ballPosition.y;
    // Take absolute value of difference
    diff = (diff > 0.0f) ? diff : -diff;
    if (
        // Ball is moving left
        _ballVelocity.x < 0.0f &&
        // Ball is aligned with paddle
        _ballPosition.x <= 40.0f && _ballPosition.x >= 30.0f &&
        // And ball is within paddle range
        diff <= 50.0f
    ) {
        _ballVelocity.x *= -1;
    }
}

void PracticeModeState::render(SDL_Renderer *renderer) {
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
    // Right wall
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 768;
    SDL_RenderFillRect(renderer, &wall);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Ball
    SDL_Rect ball {
        static_cast<int>(_ballPosition.x - thickness / 2.0f),
        static_cast<int>(_ballPosition.y - thickness / 2.0f),
        thickness,
        thickness
    };
    SDL_RenderFillRect(renderer, &ball);

    // Paddle
    SDL_Rect paddle {
        static_cast<int>(_paddlePosition.x - thickness / 2.0f),
        static_cast<int>(_paddlePosition.y - 50),
        thickness,
        100
    };
    SDL_RenderFillRect(renderer, &paddle);
}
