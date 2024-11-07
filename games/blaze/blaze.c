#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINES 7
#define COLUMNS 100
char matriz[LINES][COLUMNS][3];
int gap = 11;
int squares[9][2];

void setColor(int textColor, int backgroundColor);

void BlazeCleanMap()
{
    for (int ii = 0; ii < LINES; ii++)
    {
        for (int jj = 0; jj < COLUMNS; jj++)
        {
            strcpy(matriz[ii][jj], " ");
        }
    }
}

void BlazeGenSquareInMap(int x, int ind)
{
    for (int ii = 0; ii < (gap - 1); ii++)
    {
        strcpy(matriz[1][x + ii], "-");
        strcpy(matriz[5][x + ii], "-");
    }

    for (int ii = 0; ii < 3; ii++)
    {
        strcpy(matriz[2 + ii][x], "|");
        strcpy(matriz[2 + ii][x + 9], "|");
        if (ii == 1)
        {
            strcpy(matriz[2 + ii][x + 8], "|");
            strcpy(matriz[2 + ii][x + 9], "");
        }
    }

    char num[3];
    sprintf(num, "%.2d", squares[ind][0]);
    strcpy(matriz[3][x + 4], num);

    if (ind == 4)
    {
        strcpy(matriz[3][x + 4], " +");
    }
}

void BlazeGenSquaresValues(int qntCards)
{
    for (int ii = 0; ii < qntCards; ii++)
    {
        if (ii % 2 == 0)
        {
            squares[ii][1] = 4;
        }
        else
        {
            squares[ii][1] = 1;
        }

        squares[ii][0] = (rand() % 14) + 1;
    }

    squares[4][1] = 7;
}

void BlazeGenMap(int qntSquares)
{
    int aux = 1;
    for (int ii = 0; ii < qntSquares; ii++)
    {
        BlazeGenSquareInMap(aux, ii);
        aux += gap;
    }
}

void BlazeSetArrowPos(int posX)
{
    for (int ii = 0; ii < COLUMNS; ii++)
    {
        strcpy(matriz[0][ii], " ");
        strcpy(matriz[6][ii], " ");
    }

    strcpy(matriz[0][posX], "▼");
    strcpy(matriz[6][posX], "▲");
}

void BlazeShowMap()
{
    int pont = 1;
    for (int ii = 0; ii < LINES; ii++)
    {
        for (int jj = 0; jj < COLUMNS; jj++)
        {
            setColor(8, 0);

            int find = 0;
            int ll = -1;
            while (ll < 9 && find == 0)
            {
                if ((ii >= 1 && ii <= 5) && (jj >= 1) && jj <= (pont + 10))
                {
                    setColor(squares[0][1], 0);
                    find = 1;
                }
                if (((ii >= 1 && ii <= 5) && (jj >= (pont + ((ll + 1) * 11)) && (jj <= (pont + ((ll + 1) * 11)) + 9))))
                {
                    setColor(squares[ll + 1][1], 0);
                    find = 1;
                }

                ll++;
            }

            printf("%s", matriz[ii][jj]);
            setColor(8, 0);
        }
        printf("\n");
    }
}

int BlazeGetWon(int value)
{
    int aux = 0;
    for (int ii = 0; ii < 9; ii++)
    {
        if (value <= ((ii + 1) * 11))
        {
            return aux;
        }
        aux++;
    }
}

void BlazeGenSelect(double money, char color)
{
    if (color == 0)
    {
        printf("Você apostou no Vermelho valendo R$%.2lf", money);
        color = 4;
    }
    else if (color == 1)
    {
        printf("Você apostou no Azul valendo R$%.2lf", money);
        color = 1;
    }
    else
    {
        printf("Você apostou no Branco valendo R$%.2lf", money);
        color = 7;
    }

    int value = (rand() % 100) + 1;
    while (value % 10 == 0)
    {
        value = (rand() % 100) + 1;
    }

    int won = BlazeGetWon(value);

    for (int ii = 1; ii < value; ii++)
    {
        system("cls");
        BlazeSetArrowPos(ii);
        BlazeShowMap();
        Sleep(1);
    }

    if (squares[won][1] == color)
        printf("Você venceu a aposta!\n");
    else
        printf("Você perdeu a aposta!\n");
}

void BlazePrepareMatch()
{
    double value;
    printf("Qual valor deseja aposta? ");
    fflush(stdout);
    scanf("%lf", &value);

    int color;
    printf("Qual cor? \n");
    printf("[0] - Vermelho\n");
    printf("[1] - Azul\n");
    printf("[2] - Branco\n");
    fflush(stdout);
    scanf("%d", &color);

    BlazeGenSelect(value, color);

    char opt;
    printf("Deseja jogar novamente (S/N)? ");
    fflush(stdout);
    getchar();
    scanf("%c", &opt);

    if (opt == 'S')
    {
        BlazePrepareMatch();
    }
}

void playBlaze()
{
    srand(time(NULL));
    BlazeCleanMap();
    BlazeGenSquaresValues(9);
    BlazeGenMap(9);
    BlazePrepareMatch();
}
