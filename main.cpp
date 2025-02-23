#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;


const int height         = 20;
const int width          = 2*height;
const int scoreIncrement = 10;

int ntail      = -1;
int foodx      = 1;
int foody      = 1;
int tailx[100] = {};
int taily[100] = {};
bool gameover  = false;

enum edirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
edirection dir;

int x     = width  / 2;
int y     = height / 2;
int score = -scoreIncrement;

void update() {
    score += 10;
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
    srand(time(NULL)); // used to set the food spawn location at run time instead of compile time (so the food spawn changes every game)
    update();
    system("CLS"); // send out a clear screen command to the virtial terminal to not have the previous commands appear outside the boarder of the play area
}
// TODO: only have the changes chars update

// Function to draw the game screen
void draw()
{
    // Get a handler for the consoles and set the cursor position in a fixed location 
    // So, the game is redraws over the same place. 
    // Otherwise, new drawings will be made  every refresh at new terminal lines and the drawings 'char' continunuty will not be maintained.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    
    // Set the cursur to be invisable. 
    // Yes you need both arguements, with dwSize (1-100 [percent, DWORD = unsigned long = 32-bit unsigned integer]) being the height of the curson 
    // and bVisible (BOOL) setting the cursor to disapear as it changes each char in the specified area. 
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    // Draw top border
    for (int i = 0; i <= width; i++)
    {
        if (i == 0 || i == width)
            cout << ".";
        else
            cout << "-";
    }
    cout << endl;

    // Draw game area
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            // Draw left and right borders
            if (j == 0 || j == width)
                cout << "|";
            // Draw snake head
            else if (i == y && j == x)
                cout << "0";
            // Draw food
            else if (i == foody && j == foodx)
                cout << "*";
            else
            {
                // Draw tail segments
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (i == taily[k] && j == tailx[k])
                    {
                        cout << "o";
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
            cout << ".";
        else
            cout << "-";
    }
    cout << endl;

    // Display the score
    cout << "Score: " << score << endl;
}

// Function to handle player input
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


// Function to update game logic
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
        gameover = true;
    }

    // Check for collisions with the tail
    for (int i = 0; i < ntail; i++)
    {
        if (y == taily[i]){
            if ((x == tailx[i]) || ((dir == LEFT) && ((x+1) == tailx[i])) || ((dir == RIGHT) && ((x-1) == tailx[i]))) {
                gameover = true;
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

int main()
{
    setup(); // Initialize the game
    
    while (!gameover)
    {
        input();
        logic();
        draw();
        Sleep(120); // Adjust sleep duration based on mode
    }

    cout << "GAME OVER" << endl;

    return 0;
}
