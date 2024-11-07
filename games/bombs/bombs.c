#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINES 21
#define COLUMNS 100
char matriz[LINES][COLUMNS][3];
int posFields[16][3];
int openedFields[16];
int gameover = 0;

void chargeValue(double value, int playerCode);

void setColor(int textColor, int backgroundColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor + (backgroundColor * 16));
}

void prepMap()
{
    gameover = 0;

    for (int ii = 0; ii < LINES; ii++)
    {
        for (int jj = 0; jj < COLUMNS; jj++)
        {
            strcpy(matriz[ii][jj], " ");
        }
    }

    int auxX = 1;
    int auxY = 1;
    int aux = 0;
    for (int ii = 0; ii < 4; ii++)
    {
        for (int jj = 0; jj < 4; jj++)
        {
            posFields[aux][0] = auxX;
            posFields[aux][1] = auxY;
            posFields[aux][2] = 0;
            auxY += 10;
            aux++;
        }
        auxY = 1;
        auxX += 5;
    }

    for (int ii = 0; ii < 6; ii++)
    {
        openedFields[ii] = 0;
    }
}

int haBomba(int x, int y)
{
    for (int ii = 0; ii < 16; ii++)
    {
        if (posFields[ii][0] == x && posFields[ii][1] == y && posFields[ii][2] == 1)
        {
            return 1;
        }
    }

    return 0;
}

int bombAmount()
{
    int qntBombas;
    printf("Quantidade de bombas: (1-15)? ");
    scanf("%d", &qntBombas);
    return qntBombas;
}

void genBomb(int qntBombas)
{
    for (int ii = 0; ii < qntBombas;)
    {
        int pos = rand() % 16;
        if (posFields[pos][2] == 0)
        {
            posFields[pos][2] = 1;
            ii++;
        }
    }
}

void genMapField(int x, int y)
{
    strcpy(matriz[x][y], "-");
    strcpy(matriz[x][y + 1], "-");
    strcpy(matriz[x][y + 2], "-");
    strcpy(matriz[x][y + 3], "-");
    strcpy(matriz[x][y + 4], "-");
    strcpy(matriz[x][y + 5], "-");
    strcpy(matriz[x][y + 6], "-");
    strcpy(matriz[x][y + 7], "-");
    strcpy(matriz[x][y + 8], "-");
    strcpy(matriz[x + 1][y], "|");
    strcpy(matriz[x + 2][y], "|");
    strcpy(matriz[x + 3][y], "|");
    strcpy(matriz[x + 4][y], "-");
    strcpy(matriz[x + 4][y + 1], "-");
    strcpy(matriz[x + 4][y + 2], "-");
    strcpy(matriz[x + 4][y + 3], "-");
    strcpy(matriz[x + 4][y + 4], "-");
    strcpy(matriz[x + 4][y + 5], "-");
    strcpy(matriz[x + 4][y + 6], "-");
    strcpy(matriz[x + 4][y + 7], "-");
    strcpy(matriz[x + 4][y + 8], "-");
    strcpy(matriz[x + 1][y + 8], "|");
    strcpy(matriz[x + 2][y + 8], "|");
    strcpy(matriz[x + 3][y + 8], "|");

    strcpy(matriz[x + 2][y + 4], "🐯");
}

void genGame()
{
    int auxX = 1;
    int auxY = 1;
    for (int ii = 0; ii < 4; ii++)
    {
        for (int jj = 0; jj < 4; jj++)
        {
            genMapField(auxX, auxY);
            auxY += 10;
        }
        auxY = 1;
        auxX += 5;
    }
}

void showGame()
{
    setColor(8, 0);
    for (int ii = 0; ii < LINES; ii++)
    {
        for (int jj = 0; jj < COLUMNS; jj++)
        {
            printf("%s", matriz[ii][jj]);
        }
        printf("\n");
    }
}

void showGameResult()
{
    int x = 1;
    int y = 1;
    int aux = 0;
    for (int ii = 0; ii < 4; ii++)
    {
        for (int jj = 0; jj < 4; jj++)
        {
            strcpy(matriz[x][y], "-");
            strcpy(matriz[x][y + 1], "-");
            strcpy(matriz[x][y + 2], "-");
            strcpy(matriz[x][y + 3], "-");
            strcpy(matriz[x][y + 4], "-");
            strcpy(matriz[x][y + 5], "-");
            strcpy(matriz[x][y + 6], "-");
            strcpy(matriz[x][y + 7], "-");
            strcpy(matriz[x][y + 8], "-");
            strcpy(matriz[x + 1][y], "|");
            strcpy(matriz[x + 2][y], "|");
            strcpy(matriz[x + 3][y], "|");
            strcpy(matriz[x + 4][y], "-");
            strcpy(matriz[x + 4][y + 1], "-");
            strcpy(matriz[x + 4][y + 2], "-");
            strcpy(matriz[x + 4][y + 3], "-");
            strcpy(matriz[x + 4][y + 4], "-");
            strcpy(matriz[x + 4][y + 5], "-");
            strcpy(matriz[x + 4][y + 6], "-");
            strcpy(matriz[x + 4][y + 7], "-");
            strcpy(matriz[x + 4][y + 8], "-");
            strcpy(matriz[x + 1][y + 8], "|");
            strcpy(matriz[x + 2][y + 8], "|");
            strcpy(matriz[x + 3][y + 8], "|");

            if (posFields[aux][0] == x && posFields[aux][1] == y && posFields[aux][2] == 1)
                strcpy(matriz[x + 2][y + 4], "💣");
            else
                strcpy(matriz[x + 2][y + 4], "💰");

            y += 10;
            aux++;
        }
        y = 1;
        x += 5;
    }

    showGame();
}

void openField(int ind)
{
    if (openedFields[ind - 1] == 1)
    {
        printf("Card já está aberto!\n");
        return;
    }

    if (posFields[ind - 1][2] == 1)
    {
        strcpy(matriz[posFields[ind - 1][0] + 2][posFields[ind - 1][1] + 4], "💣");
        gameover = 1;
        setColor(4, 0);
        printf("--> VOCÊ PERDEU!\n");
        setColor(8, 0);
        chargeValue(10.0, 0);
        return;
    }
    else
    {
        strcpy(matriz[posFields[ind - 1][0] + 2][posFields[ind - 1][1] + 4], "💰");
        return;
    }

    return;
}

int askCard()
{
    printf("Qual card gostaria de abrir? \n");
    int aux = 1;
    setColor(2, 0);
    for (int ii = 1; ii <= 4; ii++)
    {
        for (int jj = 1; jj <= 4; jj++)
        {
            printf(" %.2d |", aux);
            aux++;
        }
        printf("\n--------------------\n");
    }
    setColor(8, 0);
    int opt;
    fflush(stdout);
    scanf("%d", &opt);
    return opt;
}

void playBombs()
{
    printf("\n===================================| BOMBS |===================================\n");
    setColor(8, 0);
    system("cls");

    prepMap();

    int qntBombas = bombAmount();
    genBomb(qntBombas);
    setColor(6, 0);
    printf("Quantidade de bombas: %d", qntBombas);
    setColor(8, 0);

    genGame();
    showGame();

    int opt;
    while (opt != -1 && gameover == 0)
    {
        system("\n");
        opt = askCard();
        setColor(6, 0);
        printf("--> Você escolheu o card %d. \n", opt);
        setColor(8, 0);
        openField(opt);
        showGame();
    }

    showGameResult();

    char optPlay;
    printf("Deseja jogar novamente (S/N)? \n");
    fflush(stdout);
    scanf(" %c", &optPlay);
    if (optPlay == 'S')
    {
        playBombs();
    }

    setColor(8, 0);
}