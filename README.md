# SDL Pong

Recreation of Pong using C++ and SDL framework.

## Overview

I'm learning to use the SDL framework in C++ for game development. I'm currently reading Game Programming in C++: Creating 3D Games, and while this isn't a 3D game, the first project to get you acquainted with SDL was Pong. Or rather it was a simplified version of the game where you bounce a ball off of a wall.

I want to take this further and make it a more complete game even though I haven't covered all the topics of the book yet. I know that this may mean that I'm not learning the "proper" way to do things in SDL, but I think it'll still be a good learning experience overall.

### Features

Main Menu:
- Practice Mode
- Start Game
  - 1 Player (vs CPU)
  - 2 Player
- Options
  - Toggle Sound FX
  - Toggle VSync
  - Toggle Fullscreen
  - Set resolution (based on hardware somehow?)

### Practice Mode

- Single player against "wall"
- Ball is always returned
- Score goes up when the ball hits the player's paddle
- Game ends when player misses the ball
- Ball speed gradually increases

### Game

- 1 Player vs CPU: Single player plays against a computer-controlled paddle
- 2 Player: 2 players play against each other
- First to 10 wins
- Ball speed gradually increases

### Add Sound FX
### Support gamepads

Allow force feedback for gamepads.

### Support multiple resolutions (game renders correctly at all resolutions)

## Building & Running the Game

This was developed on a Mac running macOS Sequoia (15.1.1) using CLion as the IDE, so your mileage may vary.

To build the game, you'll need to have the SDL2 library installed on your system. You can download it from the [SDL GitHub](https://github.com/libsdl-org/SDL/releases).
Personally, I just installed it via homebrew on my Mac:

```bash
brew install sdl2
```

You'll also need to have CMake installed. You can download it from the [CMake website](https://cmake.org/download/), or you can install it via homebrew:

```bash
brew install cmake
```

You can build and run the game from your IDE using the provided CMakeLists.txt file. If you're using CLion, you can just open the project and run it from there.

If you're using the command line, you can build the game by running the following command:

```bash
cmake -B build && cmake --build build
```

This will build the game and place the executable in the `build` directory. You can then run the game by executing the `pong` executable:

```bash
./build/pong
```