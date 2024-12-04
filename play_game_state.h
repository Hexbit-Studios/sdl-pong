#ifndef PLAY_GAME_STATE_H
#define PLAY_GAME_STATE_H

#include "game_state.h"
#include "vector2.h"

class PlayGameState final : public GameState {
public:
    PlayGameState();
    void enter() override;
    void exit() override;
    void processInput(Game& game, const SDL_Event& event) override;
    void update(Game& game, float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
private:
    Vector2 _paddleOnePosition;
    int _paddleOneDirection;
    Vector2 _paddleTwoPosition;
    int _paddleTwoDirection;
    Vector2 _ballPosition;
    Vector2 _ballVelocity;
};

#endif //PLAY_GAME_STATE_H
