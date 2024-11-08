#include <stdio.h>
#include <string.h>
#include "../structs.h"
#include "../db/db.h"
#include "auth.h"

void setColor(int textColor, int backgroundColor);
int existUserByEmail(char emailParam[]);

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
        setColor(4, 0);
        printf("❌ Credenciais inválidas!\n\n");
        setColor(7, 0);
    }
    else
    {
        authenticatedUser = p->code;
        setColor(10, 0);
        printf("\n😀👍 Bem vindo(a) de volta %s.\n\n", p->name);
        setColor(7, 0);
    }
}

void registerPlayer()
{
    char name[50];
    printf("========================| REGISTRO |========================\n");
    printf("Informe seu nome: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    strcpy(players[contPlayers].name, name);

    char email[50];
    do
    {
        printf("Informe seu e-mail: ");
        fgets(email, sizeof(email), stdin);

        if (existUserByEmail(email) != -1)
        {
            setColor(6, 0);
            printf("⚠️  E-mail em uso!\n\n");
            setColor(7, 0);
        }
    } while (existUserByEmail(email) != -1);

    email[strcspn(email, "\n")] = 0;
    strcpy(players[contPlayers].email, email);

    char optSexo;
    do
    {
        printf("Informe seu sexo (M/F): ");
        scanf("%c", &optSexo);

        if (optSexo != 'M' && optSexo != 'F')
        {
            setColor(6, 0);
            printf("⚠️  Opção inválida!\n\n");
            setColor(7, 0);
        }
    } while (optSexo != 'M' && optSexo != 'F');

    players[contPlayers].sexo = optSexo;

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
            setColor(6, 0);
            printf("⚠️  Senhas não são iguais!\n\n");
            setColor(7, 0);
        }
    } while (strcmp(pass, confPass) != 0);

    players[contPlayers].code = contPlayers;
    players[contPlayers].balance = 0.0;

    if (contPlayers == 0)
        players[contPlayers].accessLevel = 1;
    else
        players[contPlayers].accessLevel = 0;

    setColor(10, 0);
    printf("\n✅ Conta registrada com sucesso! Seja bem-vindo(a) %s.\n\n", players[contPlayers].name);
    setColor(7, 0);
    contPlayers++;
}

void logoutAccount()
{
    setColor(10, 0);
    printf("Até mais, %s 👋\n\n", players[authenticatedUser].name);
    setColor(7, 0);
    authenticatedUser = -1;
}