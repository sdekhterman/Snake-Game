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

## Developer Commentary (Sam)
Classes were not used. Separate class files with headers would be a reasonable addition to this codebase. For code this short and simple, that was not necessary. If more play features were to be added, it would make sense to add classes. The drawing function is also inefficient, but the repo developer, Sam, did not encounter issues with the drawing slowing down the game. As such, the developer did not draw the snake separately from drawing the border. Feel free to implement this feature as needed. The dev also altered the movement in the horizontal direction to move every two characters so movement felt more consistent with the speed experienced when moving vertically. This was implemented at the preference of the developer. this fork was made from Maria Mariam's snake game code.
