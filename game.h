#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
struct SDL_Window;
struct SDL_Renderer;

struct Vector2 {
    float x;
    float y;
};

class Game {
public:
    Game();

    // Initializes the game
    bool init();

    // Runs the game loop until the game is over
    void run();

    // Shuts down the game
    void shutdown();

private:
    // Helper functions for the game loop
    void _processInput();
    void _update();
    void _generateOutput(); // maybe change to render???

    // Window created by SDL
    SDL_Window* mWindow;

    // Renderer for 2D drawing by SDL
    SDL_Renderer* mRenderer;

    // Game should continue to run
    bool mIsRunning;

    // Paddle position
    Vector2 mPaddlePos;

    // Paddle direction
    int mPaddleDir;

    // Ball position
    Vector2 mBallPos;

    // Ball velocity
    Vector2 mBallVelocity;

    // Game ticks
    Uint32 mTicksCount;
};

#endif //GAME_H
