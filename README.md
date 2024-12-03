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
