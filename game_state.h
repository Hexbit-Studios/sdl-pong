#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL2/SDL.h>

class Game;

class GameState {
public:
    virtual ~GameState() = default;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void processInput(Game& game, const SDL_Event& event) = 0;
    virtual void update(Game& game, float deltaTime) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};

#endif //GAME_STATE_H
