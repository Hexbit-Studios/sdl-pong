#ifndef GAME_H
#define GAME_H

#include <memory>
#include "game_state.h"

class Game {
public:
    Game();

    // Initializes the game
    bool init();

    // Runs the game loop until the game is over
    void run();

    // Shuts down the game
    void shutdown();

    void changeState(std::unique_ptr<GameState> newState) {
        if (_currentState) {
            _currentState->exit();
        }
        _currentState = std::move(newState);
        if (_currentState) {
            _currentState->enter();
        }
    };
    void quit() { _isRunning = false; }

    [[nodiscard]] SDL_Renderer* getRenderer() const { return _renderer; }

private:
    // Helper functions for the game loop
    void _processInput();
    void _update();
    void _render();

    // Window created by SDL
    SDL_Window* _window;

    // Renderer for 2D drawing by SDL
    SDL_Renderer* _renderer;

    // Game should continue to run
    bool _isRunning;

    // Game ticks
    Uint32 _ticksCount;

    // Current state
    std::unique_ptr<GameState> _currentState;
};

#endif //GAME_H
