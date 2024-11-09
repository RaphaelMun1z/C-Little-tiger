#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../../db/db.h"

#define LINES 7
#define COLUMNS 100
char matriz[LINES][COLUMNS][3];
int gap = 11;
int squares[9][2];
double amountBet;
int colorSelected;

void setColor(int textColor, int backgroundColor);
void addValue(double value, int playerCode);
void chargeValue(double value, int playerCode);

void BlazeCleanMap()
{
    colorSelected = -1;

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

    int value;
    do
    {
        value = rand() % 100;
    } while (value % 11 == 1);

    int won = BlazeGetWon(value);

    for (int ii = 1; ii < value; ii++)
    {
        system("cls");
        BlazeSetArrowPos(ii);
        BlazeShowMap();
        Sleep(1);
    }

    if (squares[won][1] == color)
    {
        double money = amountBet * squares[won][0];
        setColor(2, 0);
        printf("\nVocê ganhou %d x %.2lf = R$%.2lf. \n", squares[won][0], amountBet, money);
        addValue(money, authenticatedUser);
        setColor(8, 0);
    }
    else
    {
        setColor(4, 0);
        printf("\nVocê perdeu R$%.2lf. \n", amountBet);
        chargeValue(amountBet, authenticatedUser);
        setColor(8, 0);
    }
}

void BlazePrepareMatch()
{
    do
    {
        setColor(6, 0);
        printf("Qual o valor da aposta? Digite -1 para sair. ");
        scanf("%lf", &amountBet);
        setColor(7, 0);

        if (amountBet == -1)
            return;

        if (amountBet < 20)
        {
            setColor(6, 0);
            printf("⚠️  Valor mínimo de aposta R$20,00!\n");
            setColor(7, 0);
        }
        else if (amountBet > players[authenticatedUser].balance)
        {
            setColor(6, 0);
            printf("⚠️  Você não tem saldo suficiente!\n");
            setColor(7, 0);
        }
    } while (amountBet < 20 || amountBet > players[authenticatedUser].balance);

    do
    {
        setColor(7, 0);
        printf("Qual cor? \n");
        setColor(4, 0);
        printf("[0] - Vermelho\n");
        setColor(1, 0);
        printf("[1] - Azul\n");
        setColor(7, 0);
        printf("[2] - Branco\n");
        fflush(stdout);
        scanf("%d", &colorSelected);

        if (colorSelected != 0 && colorSelected != 1 && colorSelected != 2)
        {
            setColor(6, 0);
            printf("⚠️  Cor inválida!\n");
            setColor(7, 0);
        }
    } while (colorSelected != 0 && colorSelected != 1 && colorSelected != 2);

    BlazeGenSelect(amountBet, colorSelected);

    char opt;
    do
    {
        printf("Deseja jogar novamente (S/N)? ");
        fflush(stdout);
        getchar();
        scanf("%c", &opt);

        if (toupper(opt) != 'S' && toupper(opt) != 'N')
        {
            setColor(6, 0);
            printf("⚠️  Opção inválida!\n");
            setColor(7, 0);
        }
    } while (toupper(opt) != 'S' && toupper(opt) != 'N');

    if (toupper(opt) == 'S')
        BlazePrepareMatch();
}

void playBlaze()
{
    srand(time(NULL));
    BlazeCleanMap();
    BlazeGenSquaresValues(9);
    BlazeGenMap(9);
    BlazePrepareMatch();
}
