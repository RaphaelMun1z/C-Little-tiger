#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "../../db/db.h"

const char *emojis[5] = {"🐜", "🍏", "🍎", "🌟", "🚀"};
int result[3];
double amountBet;

void setColor(int textColor, int backgroundColor);
void addValue(double value, int playerCode);
void chargeValue(double value, int playerCode);

void RoulettePrepPreMap()
{
    system("cls");

    for (int ii = 0; ii < 3; ii++)
    {
        printf("|       |  ");
    }

    printf("\n");

    for (int ii = 0; ii < 3; ii++)
    {
        printf("---------  ");
    }

    printf("\n");

    printf("\x1b[32m\n");

    for (int ii = 0; ii < 3; ii++)
    {
        printf("---------  ");
    }

    printf("\n");
}

int RouletteGetResult()
{
    if (result[0] == result[1] && result[0] == result[2] && result[1] == result[2])
    {
        return 1;
    }

    return 0;
}

void RouletteSetResult()
{
    for (int ii = 0; ii < 3; ii++)
    {
        result[ii] = rand() % 5;
    }
}

void RoulettePrepMap()
{
    RouletteSetResult();

    for (int jj = 0; jj < 3; jj++)
    {
        for (int ii = 0; ii < 3; ii++)
        {
            if (jj == 1)
            {
                printf("|   ");
                fflush(stdout);
                sleep(2);
                printf("%s", emojis[result[ii]]);
                printf("  |  ");
            }
            else
            {
                printf("|       |  ");
            }
        }
        printf("\n");
    }

    for (int ii = 0; ii < 3; ii++)
    {
        printf("---------  ");
    }

    printf("\n");

    printf("\e[0;37m\n");

    for (int ii = 0; ii < 3; ii++)
    {
        printf("---------  ");
    }

    printf("\n");

    for (int ii = 0; ii < 3; ii++)
    {
        printf("|       |  ");
    }
}

void RouletteShowResult()
{
    int indHistory = players[authenticatedUser].matchesFinished;
    players[authenticatedUser].matchesFinished++;

    time_t now;
    now = time(NULL);
    strcpy(players[authenticatedUser].history[indHistory].game, "ROULETTE");
    strcpy(players[authenticatedUser].history[indHistory].date, ctime(&now));

    if (RouletteGetResult() == 1)
    {
        setColor(2, 0);
        printf("\nVocê ganhou R$%.2lf. \n", amountBet);
        addValue(amountBet, authenticatedUser);
        setColor(8, 0);

        players[authenticatedUser].history[indHistory].result = amountBet;
    }
    else
    {
        setColor(4, 0);
        printf("\nVocê perdeu R$%.2lf. \n", amountBet);
        chargeValue(amountBet, authenticatedUser);
        setColor(8, 0);

        players[authenticatedUser].history[indHistory].result = amountBet * -1;
    }
}

void playRoulette()
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

    srand(time(NULL));
    RoulettePrepPreMap();
    RoulettePrepMap();
    RouletteShowResult();

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
        playRoulette();
}