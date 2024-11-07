#include <stdio.h>
#include "interface.h"

void showHomeMenu(int authenticatedUser)
{
    printf("===========================| MENU |===========================\n");
    if (authenticatedUser != -1)
    {
        printf("[3] Perfil\n");
        printf("[4] Jogar\n");
        printf("[5] Depositar\n");
        printf("[6] Sair da conta\n");
    }
    else
    {
        printf("[1] Entrar\n");
        printf("[2] Registrar-se\n");
    }
    printf("[7] Sair do Little Tiger 🐯\n");

    printf("______________________________________________________________\n");
}

void showGamesMenu()
{
    printf("========================| MENU DE JOGOS |=========================\n");
    printf("[1] Jogar BOMBS 💣\n");
    printf("[2] Jogar BLAZE 💎\n");
    printf("[3] Jogar ROULETTE 🎰\n");
    printf("______________________________________________________________\n");
}