#include<conio.h>
#include<windows.h>
#include<bits/stdc++.h>

using namespace std;

// TODO: also check if the var inits should go in main for garbage collectuin reasons

// Set the play area height and width, chosen to be square arbirary. 
// The width is twice the height since chars are about twice as tall as they are wide ...
// and the player moves two chares to the side for each char up/down to make movment more consistant.
// The score incrment is used to indicates to the player that a given action, collecting fruit, is desired as it increase the score variable which is printed to the player. 
const int height         = 20;
const int width          = 2*height;
const int scoreIncrement = 10;
const int sleepDuration = 120; // in millisecond

// used when drawing the game on the console
const char *fruitChar             =  "*";
const char *snakeHeadChar         =  "0";
const char *snakeTailChar         =  "o";
const char *horizontalBoarderChar =  "-";
const char *verticalBoarderChar   =  "|";
const char *cornerBoarderChar     =  ".";
const char *scoreText             = "Score: ";
const char *gameOverText          = "GAME OVER";

// Initialize size of tail, set to -1 since a function will set it to 0 on startup and allows for function reuse, ...
// a food location, that the game is not over ... since it is just starting, and the tail array.
int ntail     = -1;
int foodx     =  1;
int foody     =  1;
bool gameOver = false;
int tailx[height * width] = {};
int taily[height * width] = {};

// Setup game functions so main is understood first when reading code
void update();
void setup();
void input();
void logic();
void draw();

// Stores player diection
enum edirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
edirection dir;

// Initialize the player to start in the center of the play area, so they can get to any first fruit on average at the same speed initially, ...
// and the score, -scoreIncrement initially as it will be set to 0 on startup and allows for function reuse. 
int x     = width  / 2;
int y     = height / 2;
int score = -scoreIncrement;

int main()
{
    setup(); // Initialize the game
    
    while (!gameOver)
    {
        input();
        logic();
        draw();
        Sleep(sleepDuration); // wait to get inouts and redraw for this length
    }

    cout << gameOverText << endl;

    return 0;
}

// Function to update the score, spawn new food, and increase the tail length number
void update() {
    score += scoreIncrement;
    do {
        foodx = (rand() % (width /2))*2;
    } while ((foodx) == 0 || (foodx == width));
    do {
        foody = (rand() % (height));
    } while ((foody == 0) || (foody == height));
    ntail++;
}

// Function to initialize the game state
void setup()
{  
    srand(time(NULL)); // Used to set the food spawn location at run time instead of compile time (so the food spawn changes every game)
    update();          // Set the score and tail length to 0
    system("CLS");     // Send out a clear screen command to the virtial terminal to not have the previous commands appear outside the boarder of the play area
}

// Function to handle player keyboard input
void input()
{
    if (_kbhit())
    {
        char key = _getch();
        switch (key)
        {
        case 'w':
        case 'W':
        case 72: // ASCII code for up arrow key
            if(dir!=DOWN)
            {
                dir = UP;
            }
            break;
        case 's':
        case 'S':
        case 80: // ASCII code for down arrow key
            if(dir!=UP)
            {
                dir = DOWN;
            }
            break;
        case 'a':
        case 'A':
        case 75: // ASCII code for left arrow key
            if(dir!=RIGHT)
            {
                dir = LEFT;
            }
            break;
        case 'd':
        case 'D':
        case 77: // ASCII code for right arrow key
            if(dir!=LEFT)
            {
                dir = RIGHT;
            }
            break;
        default:
            break;
        }
    }
}

// Function to update game player position and check if they collided with food, their tail of a wall
void logic()
{
    // Update tail positions
    for (int i = ntail - 1; i > 0; --i)
    {
        tailx[i] = tailx[i - 1];
        taily[i] = taily[i - 1];
    }

    // Move the head to the new position
    tailx[0] = x;
    taily[0] = y;

    // Move the head based on the direction
    switch (dir)
    {
        case UP:
            y--;  break;
        case DOWN:
            y++;  break;
        case LEFT:
            x-=2; break;
        case RIGHT:
            x+=2; break;
        default:
            break;
    }

    // Check for collisions with the borders
    if (x <= 0 || x >= width || y < 0 || y > height)
    {
        gameOver = true;
    }

    // Check for collisions with the tail
    for (int i = 0; i < ntail; i++)
    {
        if (y == taily[i]){
            if ((x == tailx[i]) || ((dir == LEFT) && ((x+1) == tailx[i])) || ((dir == RIGHT) && ((x-1) == tailx[i]))) {
                gameOver = true;
            }
        }
    }

    // Check for collision with food and update score
    if (y == foody){
        if ((x == foodx) || ((dir == LEFT) && ((x+1) == foodx)) || ((dir == RIGHT) && ((x-1) == foodx))) {
            update();
        }
    }
}

// Function to draw the game screen
void draw()
{
    // Get a handler for the console and set the cursor position in a fixed location 
    // So, the game is redrawn over the same place. 
    // Otherwise, new drawings will be made  every refresh at new terminal line and the drawings 'char' continunuty will not be maintained.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    
    // Set the cursur to be invisable. 
    // Yes you need both arguements, with dwSize (1-100 [percent, DWORD = unsigned long = 32-bit unsigned integer]) being the height of the curson 
    // and bVisible (BOOL) setting the cursor to disapear as it changes each char in the specified area. 
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    // TODO: only have the changes chars update
    // Draw top border
    for (int i = 0; i <= width; i++)
    {
        if (i == 0 || i == width)
            cout << cornerBoarderChar;
        else
            cout << horizontalBoarderChar;
    }
    cout << endl;

    // Draw game area
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            // Draw left and right borders
            if (j == 0 || j == width)
                cout << verticalBoarderChar;
            // Draw snake head
            else if (i == y && j == x)
                cout << snakeHeadChar;
            // Draw food
            else if (i == foody && j == foodx)
                cout << fruitChar;
            else
            {
                // Draw tail segments
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (i == taily[k] && j == tailx[k])
                    {
                        cout << snakeTailChar;
                        print = true;
                    }

                // Draw empty space if no snake or food
                }
                if(!print)
                    cout << " ";
            }

        }
        cout << endl;
    }

    // Draw bottom border
    for (int i = 0; i <= width; i++)
    {
        if (i == 0 || i == width)
            cout << cornerBoarderChar;
        else
            cout << horizontalBoarderChar;
    }
    cout << endl;

    // Display the score
    cout << scoreText << score << endl;
}