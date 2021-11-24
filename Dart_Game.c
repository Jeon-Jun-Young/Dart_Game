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
    printf("��Ʈ �����Դϴ�!\n\n1���� ������ ���� �� 3��Ʈ�� ������ �˴ϴ�.\n\n");
    printf("x��� y���� ȭ��ǥ�� ��ŭ �̵����� �Է����ּ���!\n(�Է��� ���� ���� ������ ��ǥ�� �������ϴ�)\n");
    initialize();
    line_draw(29, 4, 28, 59);
    display();

    int x, y;
    int set_cnt = 0;
    
    for (int i = 0; i < 6; i++)
    {
        if ((i%2)==0) printf("\n[ Player A ]\n");
        if ((i%2)==1) printf("\n[ Player B ]\n");

        printf("�ϴ��� ȭ��ǥ($)�� ����(x��)�� �󸶳� �̵��Ͻðڽ��ϱ�? (100 ������ ��) ");
        scanf("%d", &x);
        while (x > 100)
        {
            printf("100������ ���� �Է����ּ���!");
            scanf("%d", &x);
        }
        printf("������ ȭ��ǥ(@)�� ����(y��)�� �󸶳� �̵��Ͻðڽ��ϱ�? (50 ������ ��) ");
        scanf("%d", &y);
        while (y > 50)
        {
            printf("50������ ���� �Է����ּ���!");
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
                printf(" ���� : %d\n", y_cnt);
            }
            else
            {
                p1_score += x_cnt;
                printf(" ���� : %d\n", x_cnt);
            }
        }
        else
        {
            printf("\n\nPlayer B");
            if (x_cnt < y_cnt)
            {
                p2_score += y_cnt;
                printf(" ����: %d\n", y_cnt);
            }
            else
            {
                p2_score += x_cnt;
                printf(" ����: %d\n", x_cnt);
            }
        }

        if ((i % 2) == 0)
        {
            set_cnt++;
        }
        
        printf("\n----- [%d��° ��Ʈ] -----\n\n", set_cnt);

        printf("     A ��������  = %d\n", p1_score);
        printf("     B ��������  = %d\n", p2_score);
        printf("\n------------------------\n");
        x_cnt = 1;
        y_cnt = 1;
    }
    if (p1_score < p2_score)
    {
        printf("-------------------------\n");
        printf("\nA ��������  = %d\n", p1_score);
        printf("\nB ��������  = %d\n\n", p2_score);
        printf("Player B�� �¸��߽��ϴ�!\n");
    }
    else if (p2_score < p1_score)
    {
        printf("-------------------------\n");
        printf("\nA ��������  = %d\n", p1_score);
        printf("\nB ��������  = %d\n\n", p2_score);
        printf("Player A�� �¸��߽��ϴ�!\n");
    }
    else
    {
        printf("-------------------------\n");
        printf("\nA ��������  = %d\n", p1_score);
        printf("\nB ��������  = %d\n\n", p2_score);
        printf("���º��Դϴ�!\n");
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