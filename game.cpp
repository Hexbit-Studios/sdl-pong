#include "game.h"

constexpr int thickness = 15;

Game::Game():
    mWindow(nullptr),
    mRenderer(nullptr),
    mIsRunning(true),
    mPaddlePos({0 + thickness * 2, 768 / 2.0f}),
    mPaddleDir(0),
    mBallPos({1024 / 2.0f, 768 / 2.0f}),
    mBallVelocity({-200.0f, 235.0f}),
    mTicksCount(0) {
}

bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Create an SDL window
    mWindow = SDL_CreateWindow(
        "Pong", // Window title
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024, // Width of window
        768, // Height of window
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // Create an SDL renderer
    mRenderer = SDL_CreateRenderer(
        mWindow, // Window to create renderer for
        -1, // Let SDL pick first available graphics driver
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::shutdown() {
    SDL_Log("Shutting down game...");
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::run() {
    while (mIsRunning) {
        _processInput();
        _update();
        _generateOutput();
    }
}

void Game::_processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            default:
                break;
        }
    }

    // Get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    // If escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
    // If F is pressed, toggle fullscreen
    if (state[SDL_SCANCODE_F]) {
        constexpr Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
        const bool isFullscreen = SDL_GetWindowFlags(mWindow) & FullscreenFlag;
        SDL_SetWindowFullscreen(mWindow, isFullscreen ? 0 : FullscreenFlag);
    }

    // Update paddle direction based on W/S keys
    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W]) {
        mPaddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        mPaddleDir += 1;
    }
}

void Game::_update() {
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)) {
        // Do nothing
    }

    // Delta time is the difference in ticks from last frame
    // (converted to seconds)
    float deltaTime = static_cast<float>(SDL_GetTicks() - mTicksCount) / 1000.0f;
    // Update tick counts for next frame
    mTicksCount = SDL_GetTicks();

    // Clamp maximum delta time value
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    if (mPaddleDir != 0) {
        mPaddlePos.y += static_cast<float>(mPaddleDir) * 300.0f * deltaTime;

        if (mPaddlePos.y < 50 + thickness) {
            mPaddlePos.y = 50 + thickness;
        } else if (mPaddlePos.y > 768 - 50 - thickness) {
            mPaddlePos.y = 768 - 50 - thickness;

        }
    }

    // Update ball position based on ball velocity
    mBallPos.x += mBallVelocity.x * deltaTime;
    mBallPos.y += mBallVelocity.y * deltaTime;

    // Handle ball hitting walls
    if (mBallPos.y <= thickness && mBallVelocity.y < 0.0f) {
        mBallVelocity.y *= -1;
    }
    if (mBallPos.y >= 768 - thickness && mBallVelocity.y > 0.0f) {
        mBallVelocity.y *= -1;
    }
    if (mBallPos.x >= 1024 - thickness && mBallVelocity.x > 0.0f) {
        mBallVelocity.x *= -1;
    }
    // If ball goes off-screen, reset ball
    if (mBallPos.x <= 0) {
        mBallPos = {1024 / 2.0f, 768 / 2.0f};
        mBallVelocity = {-200.0f, 235.0f};
    }

    // Ball paddle collision
    auto diff = mPaddlePos.y - mBallPos.y;
    // Take absolute value of difference
    diff = (diff > 0.0f) ? diff : -diff;
    if (
        // Ball is moving left
        mBallVelocity.x < 0.0f &&
        // Ball is aligned with paddle
        mBallPos.x <= 40.0f && mBallPos.x >= 30.0f &&
        // And ball is within paddle range
        diff <= 50.0f
    ) {
        mBallVelocity.x *= -1;
    }
}

void Game::_generateOutput() {
    // Set draw color for renderer
    SDL_SetRenderDrawColor(mRenderer, 55, 100, 255, 255);
    // Clear back buffer to current draw color
    SDL_RenderClear(mRenderer);

    // Draw the game world
    SDL_SetRenderDrawColor(mRenderer, 180, 180, 180, 255);
    SDL_Rect wall {};
    // Top wall
    wall.x = 0;
    wall.y = 0;
    wall.w = 1024;
    wall.h = thickness;
    SDL_RenderFillRect(mRenderer, &wall);
    // Bottom wall
    wall.y = 768 - thickness;
    SDL_RenderFillRect(mRenderer, &wall);
    // Right wall
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 768;
    SDL_RenderFillRect(mRenderer, &wall);

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    // Ball
    SDL_Rect ball {
        static_cast<int>(mBallPos.x - thickness / 2.0f),
        static_cast<int>(mBallPos.y - thickness / 2.0f),
        thickness,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &ball);

    // Paddle
    SDL_Rect paddle {
        static_cast<int>(mPaddlePos.x - thickness / 2.0f),
        static_cast<int>(mPaddlePos.y - 50),
        thickness,
        100
    };
    SDL_RenderFillRect(mRenderer, &paddle);

    // Swap the front and back buffers
    SDL_RenderPresent(mRenderer);
}


