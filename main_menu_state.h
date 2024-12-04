#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <vector>
#include <string>
#include "game_state.h"

struct MenuItem {
    std::string text;
    SDL_Rect bounds;
    bool isSelected;
};

class MainMenuState : public GameState {
public:
    MainMenuState();
    void enter() override;
    void exit() override;
    void processInput(Game& game, const SDL_Event& event) override;
    void update(Game& game, float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
private:
    std::vector<MenuItem> _menuItems;
    int _selectedItem;
    void initializeMenuItems();
};

#endif //MAIN_MENU_STATE_H
