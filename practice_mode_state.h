#ifndef PRACTICE_MODE_STATE_H
#define PRACTICE_MODE_STATE_H

#include "game_state.h"
#include "vector2.h"

class PracticeModeState : public GameState {
public:
    PracticeModeState();
    void enter() override;
    void exit() override;
    void processInput(Game& game, const SDL_Event& event) override;
    void update(Game& game, float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
private:
    Vector2 _paddlePosition;
    int _paddleDirection;
    Vector2 _ballPosition;
    Vector2 _ballVelocity;
};

#endif //PRACTICE_MODE_STATE_H
