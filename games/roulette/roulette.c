#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

const char *emojis[5] = {"🐜", "🍏", "🍎", "🌟", "🚀"};
int result[3];

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
    if (RouletteGetResult() == 1)
        printf("\nVocê ganhou!\n");
    else
        printf("\nVocê perdeu!\n");
}

void playRoulette()
{
    double value;
    printf("Qual valor deseja aposta? ");
    fflush(stdout);
    scanf("%lf", &value);

    srand(time(NULL));
    RoulettePrepPreMap();
    RoulettePrepMap();
    RouletteShowResult();

    char opt;
    printf("Deseja jogar novamente (S/N)? ");
    fflush(stdout);
    getchar();
    scanf("%c", &opt);

    if (opt == 'S')
    {
        playRoulette();
    }
}