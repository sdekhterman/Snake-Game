#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;

bool gameover;
const int height = 20;
const int width = 40;

int x, y, foodx, foody, score;

enum edirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
edirection dir;

int tailx[100], taily[100], ntail;

// Function to initialize the game state
void setup()
{  
    srand(time(NULL)); // used to set the food spawn location at run time instead of compile time (so the food spawn changes every game)
    gameover = false;
    x = width / 2;
    y = height / 2;

    // TODO: make sure it doesn't spawn on the boarders
    do {
        foodx = (rand() % (width /2))*2;
    } while ((foodx) == 0 || (foodx == width));


    do {
        foody = (rand() % (height /2))*2;
    } while ((foody == 0) || (foody == height));
    cout << "x = " << foodx << ", y = " << foody; 

    score = 0;

    system("CLS"); // send out a clear screen command to the virtial terminal to not have the previous commands appear outside the boarder of the play area
}
// TODO: only have the changes chars update

// Function to draw the game screen
void draw()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    // Draw top border
    for (int i = 0; i <= width; i++)
    {
        if (i == 0 || i == width)
            cout << "#";
        else
            cout << "#";
    }
    cout << endl;

    // Draw game area
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            // Draw left and right borders
            if (j == 0 || j == width)
                cout << "#";
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
            cout << "#";
        else
            cout << "#";
    }
    cout << endl;

    // Display the score
    cout << "Score : " << score << endl;
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
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x-=2;
        break;
    case RIGHT:
        x+=2;
        break;
    default:
        break;
    }

    // TODO: combine these checks for gameover

    // Check for collisions with the borders
    if (x < 0 || x > width || y < 0 || y > height)
    {
        gameover = true;
    }

    // Check for collisions with the tail
    for (int i = 0; i < ntail; i++)
    {
        if (x == tailx[i] && y == taily[i])
        {
            gameover = true;
        }

        // TODO: need collision checks for up and down
        if((dir == LEFT)){
            if ((x+1) == tailx[i] && y == foody)
            {
                gameover = true;
            }
        } 
        if((dir == RIGHT)){
            if ((x-1) == tailx[i] && y == foody)
            {
                gameover = true;
            }
        } 
    }

    // Check for collision with food and update score
    if (x == foodx && y == foody)
    {
        // TODO: turn the food spawn, tail extension, and score increment into a function
        score += 10;
        do {
            foodx = (rand() % (width /2))*2;
        } while ((foodx) == 0 || (foodx == width));
        do {
            foody = (rand() % (height /2))*2;
        } while ((foody == 0) || (foody == height));
        ntail++;
    }
    if((dir == LEFT)){
        if ((x+1) == foodx && y == foody)
        {
            score += 10;
            do {
                foodx = (rand() % (width /2))*2;
            } while ((foodx) == 0 || (foodx == width));
            do {
                foody = (rand() % (height /2))*2;
            } while ((foody == 0) || (foody == height));
            ntail++;
        }
    } 
    if((dir == RIGHT)){
        if ((x-1) == foodx && y == foody)
        {
            score += 10;
            do {
                foodx = (rand() % (width /2))*2;
            } while ((foodx) == 0 || (foodx == width));
            do {
                foody = (rand() % (height /2))*2;
            } while ((foody == 0) || (foody == height));
            ntail++;
        }
    } 
}

int main()
{

    cout << "Use arrow keys to move the snake." << endl;

    setup(); // Initialize the game

    while (!gameover)
    {
        draw();
        input();
        logic();
        Sleep(100); // Adjust sleep duration based on mode
    }

    cout << "GAME OVER" << endl;

    return 0;
}


