#ifndef OPTIONS_STATE_H
#define OPTIONS_STATE_H

#include <vector>
#include <string>
#include "game_state.h"

class OptionsState final : public GameState {
public:
    OptionsState();
    void enter() override;
    void exit() override;
    void processInput(Game& game, const SDL_Event& event) override;
    void update(Game& game, float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
};

#endif //OPTIONS_STATE_H
