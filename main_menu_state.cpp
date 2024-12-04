#include "main_menu_state.h"
#include "game.h"
#include "practice_mode_state.h"

MainMenuState::MainMenuState() : _selectedItem(0) {}

void MainMenuState::enter() {
    initializeMenuItems();
}

void MainMenuState::exit() {
    _menuItems.clear();
}

void MainMenuState::initializeMenuItems() {
    constexpr int menuStartY = 250;

    const std::vector<std::string> items = {
        "Practice Mode",
        "1 Player",
        "2 Player",
        "Options",
        "Quit"
    };

    int y = menuStartY;
    for (const auto& text: items) {
        constexpr int menuItemHeight = 50;
        MenuItem item;
        item.text = text;
        item.bounds = {412, y, 200, menuItemHeight};
        item.isSelected = false;
        _menuItems.push_back(item);
        y += menuItemHeight + 20;
    }

    _menuItems[_selectedItem].isSelected = true;
}

void MainMenuState::processInput(Game &game, const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                _menuItems[_selectedItem].isSelected = false;
                _selectedItem = (_selectedItem - 1 + _menuItems.size()) % _menuItems.size();
                _menuItems[_selectedItem].isSelected = true;
                break;
            case SDLK_DOWN:
                _menuItems[_selectedItem].isSelected = false;
                _selectedItem = (_selectedItem + 1) % _menuItems.size();
                _menuItems[_selectedItem].isSelected = true;
                break;
            case SDLK_RETURN:
                switch (_selectedItem) {
                    case 0: // Practice Mode
                        game.changeState(std::make_unique<PracticeModeState>());
                        break;
                    case 1: // 1 Player
                        // game.changeState(std::make_unique<PlayGameState>());
                        break;
                    case 2: // 2 Player
                        break;
                    case 3: // Options
                        break;
                    case 4: // Quit
                        game.quit();
                        break;
                    default:
                        SDL_Log("Unsupported option selected %d", _selectedItem);
                        break;
                }
                break;
            case SDLK_ESCAPE:
                game.quit();
                break;
            default:
                break;
        }
    }
}

void MainMenuState::update(Game &game, float deltaTime) {
    // NOTE: Menu animations could go here...
}

void MainMenuState::render(SDL_Renderer* renderer) {
    // Set background color
    SDL_SetRenderDrawColor(renderer, 55, 125, 255, 255);
    SDL_RenderClear(renderer);

    // Draw menu items
    for (const auto& item: _menuItems) {
        auto [r, g, b, a] = item.isSelected ? SDL_Color{255, 255, 255, 255} : SDL_Color{200, 200, 200, 255};
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderFillRect(renderer, &item.bounds);


    }
}