#include "options_state.h"
#include "game.h"
#include "main_menu_state.h"

OptionsState::OptionsState() = default;

void OptionsState::enter() {
    // Initialize options state
}

void OptionsState::exit() {
    // Clean up options state
}

void OptionsState::processInput(Game &game, const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        game.changeState(std::make_unique<MainMenuState>());
    }
}

void OptionsState::update(Game &game, float deltaTime) {
    // Update options state
}

void OptionsState::render(SDL_Renderer *renderer) {
    // Draw a red background
    SDL_SetRenderDrawColor(renderer, 255, 120, 120, 255);
    SDL_RenderClear(renderer);
}

