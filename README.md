# Snake Game in C++ (Console)

Welcome to the classic Snake Game implementation in C++! This simple console-based game allows players to control a snake, collect food, and grow longer, all while aiming for the highest score without colliding with borders or the snake's tail.

## Features
- Responsive arrow key controls.
- Score tracking.
- Game-over screen.

## How to Play

1. **Clone the repository** to your local machine.
2. **Compile the code** using a C++ compiler.
```
g++ -o snake_game main.cpp
```
3. **Execute the compiled executable** to start the game.
```
./snake_game.exe
```
4. Use arrow keys (up, down, left, right) to control the snake.
    - Up Arrow: Move Up
    - Down Arrow: Move Down
    - Left Arrow: Move Left
    - Right Arrow: Move Right
5. The game continues until you collide with borders or the snake's tail.

## Demo Video

Check out the gameplay in action on our [YouTube Demo](https://youtu.be/0yA8jrbZhTM).

## Code Overview

### Initialization

- Snake starts in the center with random food placement.
- Score begins at zero.

### Drawing

- Console-based drawing with snake represented by "0", food by "*", and tail segments by "o".
- Score displayed at the bottom of the screen.

### Input

- Arrow keys control snake direction using `_kbhit()` and `_getch()` functions.

### Logic

- Update snake positions and check for collisions.
- Tail segments follow the head.
- Borders, snake's own tail, and food collisions are checked.

Enjoy the Game! 🐍
