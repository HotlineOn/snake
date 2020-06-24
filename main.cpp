#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

bool game_over;
const int width = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[30], tail_y[30], prev_x, prev_y, tail_length = 0;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void setup()
{
    game_over = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruit_x = rand() % (width - 1);
    fruit_y = rand() % height;
}

bool is_tail(int i, int j)
{
    bool flag = false;
    for(int n = 0; n < tail_length; n++)
        {
            if(i == tail_x[n] && j == tail_y[n])
                flag = true;
        }
    return flag;
}

void draw()
{
    system("cls");
    for (int i = 0; i <= width; i++)
        cout << "#";
    cout << endl;

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (i == 0 || i == width - 1)
                cout << "#";
            if (tail_length > 0)
            {

            }
            if ((i == x && j == y) || is_tail(i, j))
                cout << "0";
            else if (i == fruit_x && j == fruit_y)
                cout << "F";
            else
                cout << " ";
        }
        cout << endl;
    }
    for (int i = 0; i <= width; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
    Sleep(500.0 / (score+1));
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir == RIGHT) dir = RIGHT;
            else dir = LEFT;
            break;
        case 'd':
            if (dir == LEFT) dir = LEFT;
            else dir = RIGHT;
            break;
        case 'w':
            if (dir == DOWN) dir = DOWN;
            else dir = UP;
            break;
        case 's':
            if (dir == UP) dir = UP;
            else dir = DOWN;
            break;
        case 'x':
            game_over = true;
            break;
        }
    }
}

void logic()
{
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    if (tail_length > 0)
    {
        if (tail_length > 1)
        for (int i = tail_length; i > 0; i--)
        {
            tail_x[i] = tail_x[i-1];
            tail_y[i] = tail_y[i-1];
        }
        tail_x[0] = prev_x;
        tail_y[0] = prev_y;
    }
    for (int i = 0; i < tail_length; i++)
    {
        if (x == tail_x[i] && y == tail_y[i])
            game_over = true;
    }
    if (fruit_x == x && fruit_y == y)
    {
        score += 1;
        if (tail_length < 30) tail_length += 1;
        fruit_x = rand() % (width - 1);
        fruit_y = rand() % height;
    }
    if (x == 0)
        x = width - 2;
    if (x == width - 1)
        x = 0;
    if (y == 0)
        y = height -1;
    if (y == height)
        y = 0;
    prev_x = x;
    prev_y = y;
}

void print_game_over()
{
    cout << " 00     0    0   0  0000       00   0   0  0000  000\n"
         << "0      0 0   00 00  0         0  0  0   0  0     0  0\n"
         << "0 00  00000  0 0 0  0000      0  0  0   0  0000  000\n"
         << "0  0  0   0  0   0  0         0  0   0 0   0     0 0\n"
         << " 00   0   0  0   0  0000       00     0    0000  0  0\n";
}

int main()
{
    setup();
    while(!game_over)
    {
        draw();
        input();
        logic();
    }
    print_game_over();
    return 0;
}
