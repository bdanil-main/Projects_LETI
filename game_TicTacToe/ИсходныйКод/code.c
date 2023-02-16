#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define ABYSS ' '
char board[3][3] = { {ABYSS, ABYSS, ABYSS},{ABYSS, ABYSS, ABYSS},{ABYSS, ABYSS, ABYSS} };

void AI_move(), Alive_move(), visualize();
char win_check();

int main()
{
    char win;
    printf("Welcome to the Tic-Tac-Toe game!\nYou'll be playing against computer\n\nYou need to enter 2 coordinates to place your cross\nIt works in the very same way as game called \"Sea battle\" works\nFirst of all, you need to enter the row (vertical coordinate of your cross)\nNext number to enter is the column (horizontal coordinate of your cross)\n");
    win = ABYSS;
    visualize();
    do {

        Alive_move();
        visualize();
        win = win_check();
        if (win != ABYSS) break;
        AI_move();
        visualize();
        win = win_check();
    } while (win == ABYSS);
    if (win == 'X') printf("You won\n");
    else printf("You lost\n");
    visualize();
    return 0;
}

int panic()
{
    char* s;
    s = (char*)board;
    int mirage[] = { 0,0,0,0,0,0,0,0,0 };
    for (int i = 0; i < 9; i++)
    {
        if (s[i] == 'X')
        {
            mirage[i] = 1;
        }
    }

    printf("\n");
    if ((s[1] == 'O' && s[2] == 'O' && !mirage[0]) || (s[4] == 'O' && s[8] == 'O' && !mirage[0]) || (s[3] == 'O' && s[6] == 'O' && !mirage[0])) { return 0; }
    if ((s[0] == 'O' && s[2] == 'O' && !mirage[1]) || (s[4] == 'O' && s[7] == 'O' && !mirage[1])) { return 1; }
    if ((s[0] == 'O' && s[1] == 'O' && !mirage[2]) || (s[6] == 'O' && s[4] == 'O' && !mirage[2]) || (s[8] == 'O' && s[5] == 'O' && !mirage[0])) { return 2; }
    if ((s[4] == 'O' && s[5] == 'O' && !mirage[3]) || (s[0] == 'O' && s[6] == 'O' && !mirage[3])) { return 3; }
    if ((s[3] == 'O' && s[4] == 'O' && !mirage[5]) || (s[2] == 'O' && s[8] == 'O' && !mirage[5])) { return 5; }
    if ((s[0] == 'O' && s[3] == 'O' && !mirage[6]) || (s[2] == 'O' && s[4] == 'O' && !mirage[6]) || (s[7] == 'O' && s[8] == 'O' && !mirage[6])) { return 6; }
    if ((s[6] == 'O' && s[8] == 'O' && !mirage[7]) || (s[1] == 'O' && s[4] == 'O' && !mirage[7])) { return 7; }
    if ((s[6] == 'O' && s[7] == 'O' && !mirage[8]) || (s[0] == 'O' && s[4] == 'O' && !mirage[8]) || (s[2] == 'O' && s[5] == 'O' && !mirage[8])) { return 8; }
    if ((mirage[1] && mirage[2] && s[0] == ABYSS) || (mirage[3] && mirage[6] && s[0] == ABYSS) || (mirage[4] && mirage[8] && s[0] == ABYSS)) { return 0; }
    if ((mirage[0] && mirage[2] && s[1] == ABYSS) || (mirage[4] && mirage[7] && s[1] == ABYSS)) { return 1; }
    if ((mirage[0] && mirage[1] && s[2] == ABYSS) || (mirage[6] && mirage[4] && s[2] == ABYSS) || (mirage[8] && mirage[5] && s[0] == ABYSS)) { return 2; }
    if ((mirage[4] && mirage[5] && s[3] == ABYSS) || (mirage[0] && mirage[6] && s[3] == ABYSS)) { return 3; }
    if ((mirage[3] && mirage[4] && s[5] == ABYSS) || (mirage[2] && mirage[8] && s[5] == ABYSS)) { return 5; }
    if ((mirage[0] && mirage[3] && s[6] == ABYSS) || (mirage[2] && mirage[4] && s[6] == ABYSS) || (mirage[7] && mirage[8] && s[6] == ABYSS)) { return 6; }
    if ((mirage[6] && mirage[8] && s[7] == ABYSS) || (mirage[1] && mirage[4] && s[7] == ABYSS)) { return 7; }
    if ((mirage[6] && mirage[7] && s[8] == ABYSS) || (mirage[0] && mirage[4] && s[8] == ABYSS) || (mirage[2] && mirage[5] && s[8] == ABYSS)) { return 8; }
    return 10;
}

void Alive_move()
{
    int x, y;
    char coordsX[10], coordsY[10];
    printf("Enter coordinates for your cross.\n\n");
    printf("Row? (vertical coordinate) ");
    scanf("%s", coordsX);
    coordsX[strlen(coordsX)] = '\0';
    if (strlen(coordsX) != 1 || !isdigit(coordsX[0]))
    {
        printf("Something went wrong, do another move\n\n");
        Alive_move();
        return;
    }
    else
    {
        x = atoi(coordsX) - 1;
    }
    printf("Column?(horizontal coordinate) ");
    scanf("%s", coordsY);
    if (strlen(coordsY) != 1 || !isdigit(coordsY[0]))
    {
        printf("Something went wrong, do another move\n\n");
        Alive_move();
        return;
    }
    else {
        y = atoi(coordsY) - 1;
    }

    if (x < 0 || y < 0 || x>2 || y>2 || board[x][y] != ABYSS || board[x][y] == 'X')
    {
        printf("Something went wrong, do another move\n\n");
        Alive_move();
    }
    else
    {
        board[x][y] = 'X';
        return;
    }
}

void AI_move()
{
    int d9;
    int i, stime;
    long ltime;
    char* s;
    s = (char*)board;
    int boardScan = panic();
    if (boardScan < 10 && s[boardScan] == ABYSS)
    {
        s[boardScan] = 'O';
        return;
    }

    if (s[4] == ABYSS) {
        s[4] = 'O';
        return;
    }
    if (s[4] != ABYSS) {
        ltime = time(NULL);
        stime = (unsigned int)ltime / 2;
        srand(stime);
        d9 = rand() % 9;

        if (s[d9] != ABYSS || d9 % 2 != 0) {
            while (d9 % 2 != 0 || s[d9] != ABYSS) { if (s[0] == ABYSS || s[2] == ABYSS || s[4] == ABYSS || s[6] == ABYSS || s[8] == ABYSS) { d9 = rand() % 9; } else { break; } }
        }
        if (s[d9] != ABYSS || d9 % 2 == 0) {
            while (d9 % 2 == 0 || s[d9] != ABYSS) { if (s[0] != ABYSS && s[2] != ABYSS && s[4] != ABYSS && s[6] != ABYSS && s[8] != ABYSS) { if (s[1] == ABYSS || s[3] == ABYSS || s[5] == ABYSS || s[7] == ABYSS) { d9 = rand() % 9; } else { break; } } else { break; } }
        }

        if (s[d9] == ABYSS) {
            s[d9] = 'O';
            return;
        }


        for (i = 0; *s != ABYSS && i < 9; ++i) { s++; }
        if (i == 9)
        {
            printf("Draw\n");
            visualize();
            exit(0);
        }

        return;
    }
}

void visualize()
{
    int t;
    printf("\n ___ ___ ___\n");
    for (t = 0; t < 3; t++)
    {
        printf("| %c | %c | %c |\n", board[t][0], board[t][1], board[t][2]);
        printf("|___|___|___|\n");
    }
    printf("\n");
}

char win_check()
{
    int i;
    char* s;
    for (i = 0; i < 3; i++) {
        s = &board[i][0];
        if (*s == *(s + 1) && *(s + 1) == *(s + 2)) return *s;
    }
    for (i = 0; i < 3; i++) {
        s = &board[0][i];
        if (*s == *(s + 3) && *(s + 3) == *(s + 6)) return *s;
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) { return board[0][0]; }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) { return board[0][2]; }
    return ABYSS;

}