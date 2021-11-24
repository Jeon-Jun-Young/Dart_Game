#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>

#define WIDTH 60
#define HEIGHT 30

void line_draw(int, int, int, int);
char board[HEIGHT][WIDTH];

void initialize(void);
void display(void);
void below_move(void);
bool below_blocked(void);
void below_turn(void);
void right_move(void);
bool right_blocked(void);
void right_turn();

int p1_score = 0, p2_score = 0;
int below_x, below_y, right_x, right_y;
int dx, dy;

int main(void)
{
    printf("다트 게임입니다!\n\n1번씩 번갈아 던져 총 3세트를 던지게 됩니다.\n\n");
    printf("x축과 y축의 화살표를 얼만큼 이동할지 입력해주세요!\n(입력한 값에 따라 던지는 좌표가 정해집니다)\n");
    initialize();
    line_draw(29, 4, 28, 59);
    display();

    int x, y;
    int set_cnt = 0;
    
    for (int i = 0; i < 6; i++)
    {
        if ((i%2)==0) printf("\n[ Player A ]\n");
        if ((i%2)==1) printf("\n[ Player B ]\n");

        printf("하단의 화살표($)를 가로(x축)로 얼마나 이동하시겠습니까? (100 이하의 수) ");
        scanf("%d", &x);
        while (x > 100)
        {
            printf("100이하의 수를 입력해주세요!");
            scanf("%d", &x);
        }
        printf("우측의 화살표(@)를 세로(y축)로 얼마나 이동하시겠습니까? (50 이하의 수) ");
        scanf("%d", &y);
        while (y > 50)
        {
            printf("50이하의 수를 입력해주세요!");
            scanf("%d", &y);
        }

        for (int i = 0; i < x; i++)
        {

            while (below_blocked())
            {
                below_turn();
            }
            below_move();
            display();
            Sleep(50);
            system("cls");
        }

        for (int j = 0; j < y; j++)
        {

            while (right_blocked())
            {
                right_turn();
            }
            right_move();
            display();
            Sleep(50);
            system("cls");
        }
        
        int x_cnt = 1;
        int y_cnt = 1;
   
        int x_remain = x % 52;

        for (int i = 0; i<49; i+=4)
        {
            if ((i <= x_remain)&&(x_remain < (i + 4))) break;

            if (i + 4 < 27) x_cnt++;
            else x_cnt--;
        }

        int y_remain = x % 26;
        for (int j= 0; j < 27; j += 2)
        {
            if ((j <= y_remain)&&(y_remain < (j + 2))) break;

            if (j + 2 < 14) y_cnt++;
            else y_cnt--;
        }

        initialize();
        line_draw(29, 4, 28, 59);
        display();
        
        if ((i % 2) == 0)
        {
            printf("\n\nPlayer A ");
            if (x_cnt < y_cnt)
            {
                p1_score += y_cnt;
                printf(" 점수 : %d\n", y_cnt);
            }
            else
            {
                p1_score += x_cnt;
                printf(" 점수 : %d\n", x_cnt);
            }
        }
        else
        {
            printf("\n\nPlayer B");
            if (x_cnt < y_cnt)
            {
                p2_score += y_cnt;
                printf(" 점수: %d\n", y_cnt);
            }
            else
            {
                p2_score += x_cnt;
                printf(" 점수: %d\n", x_cnt);
            }
        }

        if ((i % 2) == 0)
        {
            set_cnt++;
        }
        
        printf("\n----- [%d번째 세트] -----\n\n", set_cnt);

        printf("     A 누적점수  = %d\n", p1_score);
        printf("     B 누적점수  = %d\n", p2_score);
        printf("\n------------------------\n");
        x_cnt = 1;
        y_cnt = 1;
    }
    if (p1_score < p2_score)
    {
        printf("-------------------------\n");
        printf("\nA 최종점수  = %d\n", p1_score);
        printf("\nB 최종점수  = %d\n\n", p2_score);
        printf("Player B가 승리했습니다!\n");
    }
    else if (p2_score < p1_score)
    {
        printf("-------------------------\n");
        printf("\nA 최종점수  = %d\n", p1_score);
        printf("\nB 최종점수  = %d\n\n", p2_score);
        printf("Player A가 승리했습니다!\n");
    }
    else
    {
        printf("-------------------------\n");
        printf("\nA 최종점수  = %d\n", p1_score);
        printf("\nB 최종점수  = %d\n\n", p2_score);
        printf("무승부입니다!\n");
    }
    
}

void initialize()
{
    int y_inter = 4;
    int x_inter = 2;
    int i, j;

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

void line_draw(int b_y, int b_x, int r_y, int r_x)
{
    below_y = b_y;  //29
    below_x = b_x;  //4
    right_y = r_y;  //28
    right_x = r_x;  //59

    board[below_y][below_x] = '$';
    board[right_y][right_x] = '@';
}

void below_move()
{
    board[below_y][below_x] = ' ';
    below_x += dx;
    board[below_y][below_x] = '$';
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
    board[right_y][right_x] = '@';
}

bool right_blocked() {
    return board[right_y-dy][right_x] == '*';
}

void right_turn() {
    dy = -dy;
}

void display() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}