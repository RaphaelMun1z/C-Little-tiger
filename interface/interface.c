#include <stdio.h>
#include "interface.h"
#include "../db/db.h"

void setColor(int textColor, int backgroundColor);

void showHomeMenu(int authenticatedUser)
{
    printf("___________________________ MENU ___________________________\n");
    if (authenticatedUser != -1)
    {
        printf("[3] Perfil\n");
        printf("[4] Jogar\n");
        printf("[5] Depositar\n");
        printf("[6] Sacar\n");
        setColor(8, 0);
        if (players[authenticatedUser].accessLevel == 1){
            printf("[7] Consultar todos os usuário. \n");
            printf("[8] Deletar usuário. \n");
            printf("[9] Consultar usuário por código. \n");
        }
        printf("[10] Sair da conta\n");
        setColor(7, 0);
    }
    else
    {
        printf("[1] Entrar\n");
        printf("[2] Registrar-se\n");
    }

    setColor(12, 0);
    printf("[11] Sair do Little Tiger 🐯\n");
    setColor(7, 0);

    printf("______________________________________________________________\n");
}

void showGamesMenu()
{
    printf("________________________ MENU DE JOGOS ________________________=\n");
    printf("[1] Jogar BOMBS 💣\n");
    printf("[2] Jogar BLAZE 💎\n");
    printf("[3] Jogar ROULETTE 🎰\n");
    printf("______________________________________________________________\n");
}