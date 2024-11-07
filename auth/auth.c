#include <stdio.h>
#include <string.h>
#include "../structs.h"
#include "../db/db.h"
#include "auth.h"

player *authUser(char email[50], char pass[50])
{
    for (int ii = 0; ii < 14; ii++)
    {
        if (strcmp(players[ii].email, email) == 0)
        {
            if (strcmp(players[ii].password, pass) == 0)
            {
                return &players[ii];
            }
        }
    }

    return NULL;
}

void login()
{
    char l_email[50], l_pass[50];
    printf("========================| LOGIN |========================\n");
    printf("Informe seu e-mail: ");
    fflush(stdout);
    scanf("%s", &l_email);

    printf("Informe sua senha: ");
    fflush(stdout);
    scanf("%s", &l_pass);

    player *p = authUser(l_email, l_pass);

    if (p == NULL)
    {
        printf("❌ Credenciais inválidas!\n\n");
    }
    else
    {
        authenticatedUser = p->code;
        printf("\n☑ Bem vindo(a) de volta %s.\n\n", p->name);
    }
}

void registerPlayer()
{
    printf("========================| REGISTER |========================\n");
    printf("Informe seu nome: ");
    fflush(stdout);
    scanf("%s", &players[contPlayers].name);

    printf("Informe seu e-mail: ");
    fflush(stdout);
    scanf("%s", players[contPlayers].email);

    char pass[50], confPass[50];
    do
    {
        printf("Informe sua senha: ");
        fflush(stdout);
        scanf("%s", pass);

        printf("Confirme sua senha: ");
        fflush(stdout);
        scanf("%s", confPass);

        if (strcmp(pass, confPass) == 0)
        {
            strcpy(players[contPlayers].password, pass);
        }
        else
        {
            printf("⚠️ Senhas não são iguais!\n\n");
        }
    } while (strcmp(pass, confPass) != 0);

    players[contPlayers].code = contPlayers;
    players[contPlayers].balance = 0.0;
    players[contPlayers].category = 'A';
    printf("\n☑ Conta registrada com sucesso! Seja bem-vindo(a) %s.\n\n", players[contPlayers].name);
    contPlayers++;
}

void logoutAccount()
{
    printf("Até mais, %s 👋\n", players[authenticatedUser].name);
    authenticatedUser = -1;
}