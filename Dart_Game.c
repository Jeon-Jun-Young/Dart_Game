#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>

#define WIDTH 60
#define HEIGHT 30

void line(int, int, int, int);
char board[HEIGHT][WIDTH];

void initialize(void);
void display(void);
void below_move(void);
bool below_blocked(void);
void below_turn(void);

int p1_score = 0, p2_score = 0;
int below_x, below_y, right_x, right_y;
int dx, dy;

int main(void)
{
    initialize();
    line(29, 4, 28, 59);
    while (1)
    {
        while (below_blocked())
        {
            below_turn();
        }
        below_move();
        display();
        Sleep(30);
        system("cls");
    }
}

void initialize()
{
    int y_inter = 4;
    int x_inter = 2;
    int i, j;

    printf("°ø°£\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = ' ';
        }
    }


    for (i = 0; i < 9; i++)
    {
        for (j = y_inter; j < WIDTH - y_inter; j++)
        {
            board[x_inter][j] = board[HEIGHT - x_inter][j] = '*';
        }
        x_inter += 2;
        y_inter += 4;
    }

    board[29][3] = '*';
    board[29][59] = '*';
    board[2][59] = '*';

    x_inter = 2;
    y_inter = 4;

    for (i = 0; i < 9; i++)
    {
        for (j = x_inter; j < HEIGHT - x_inter + 1; j++)
        {
            board[j][y_inter] = board[j][WIDTH - y_inter] = '*';
        }
        x_inter += 2;
        y_inter += 4;
    }

    dx = dy = 1;
}

void line(int b_y, int b_x, int r_y, int r_x)
{
    below_y = b_y;  //29
    below_x = b_x;  //4
    right_y = r_y;  //28
    right_x = r_x;  //59

    board[below_y][below_x] = '|';
    board[right_y][right_x] = '<';
}

void below_move()
{
    board[below_y][below_x] = ' ';
    below_x += dx;
    board[below_y][below_x] = '|';
}

bool below_blocked() {
    return board[below_y][below_x + dx] == '*';
}

void below_turn()
{
    dx = -dx;
}

void right_move()
{
    board[right_y][right_x] = ' ';
    right_y -= dy;
    board[right_y][right_x] = '<';
}



void display() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}