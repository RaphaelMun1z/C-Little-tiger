#include <stdio.h>
#include "interface.h"
#include "../db/db.h"

void setColor(int textColor, int backgroundColor);

void showHomeMenu(int authenticatedUser)
{
    printf("∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎ MENU ∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎\n");
    if (authenticatedUser != -1)
    {
        printf("③ Perfil\n");
        printf("④ Jogar\n");
        printf("⑤ Depositar\n");
        printf("⑥ Sacar\n");
        setColor(8, 0);
        if (players[authenticatedUser].accessLevel == 1){
            printf("⑦ Consultar todos os usuário. \n");
            printf("⑧ Deletar usuário. \n");
            printf("⑨ Consultar usuário por código. \n");
        }
        printf("⑩ Sair da conta\n");
        setColor(7, 0);
    }
    else
    {
        printf("➀ Entrar\n");
        printf("➁ Registrar-se\n");
    }

    setColor(12, 0);
    printf("⑪ Sair do Little Tiger 🐯\n");
    setColor(7, 0);

    printf("∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎\n");
}

void showGamesMenu()
{
    printf("∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎ MENU DE JOGOS ∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎\n");
    printf("① Jogar BOMBS 💣\n");
    printf("② Jogar BLAZE 💎\n");
    printf("③ Jogar ROULETTE 🎰\n");
    printf("∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎\n");
}