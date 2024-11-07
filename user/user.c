#include <stdio.h>
#include "../structs.h"
#include "../db/db.h"
#include "user.h"

void setColor(int, int);

void getByIdUserDetails(int code)
{
    for (int ii = 0; ii < 14; ii++)
    {
        if (players[ii].code == code)
        {
            printf("\n===================| DETALHES DO USUÁRIO |====================\n");
            printf("Nome: %s\n", players[ii].name);
            printf("E-mail: %s\n", players[ii].email);
            printf("Saldo: R$%.2lf\n", players[ii].balance);
            printf("Categoria: %c\n", players[ii].category);
            printf("______________________________________________________________\n\n");
            return;
        }
    }

    printf("⚠️ Usuário não encontrado!\n");
}

void getAllUsersDetails()
{
    printf("\n========================| USERS DETAILS |=========================\n");
    for (int ii = 0; ii < 14; ii++)
    {
        printf("Nome: %s\n", players[ii].name);
        printf("E-mail: %s\n", players[ii].email);
        printf("Saldo: %.2lf\n", players[ii].balance);
        printf("Categoria: %c\n", players[ii].category);
        printf("______________________________________________________________\n\n");
    }
}

void depositMoney()
{
    for (int ii = 0; ii < 14; ii++)
    {
        if (players[ii].code == authenticatedUser)
        {
            printf("\n===================| DEPÓSITO |====================\n");
            double amount;
            printf("Qual o valor? ");
            fflush(stdout);
            scanf("%lf", &amount);

            if (amount > 0)
            {
                players[ii].balance += amount;
                printf("💲 Depósito realizado com sucesso!\n");
            }
            else
            {
                printf("⚠️ Valor inválido!\n");
            }

            printf("______________________________________________________________\n\n");
            return;
        }
    }

    printf("⚠️ Não foi possível depositar o dinheiro!\n");
}

void chargeValue(double value, int playerCode)
{
    players[playerCode].balance -= value;
    setColor(4, 0);
    printf("-R$%.2lf 💸", value);
    setColor(8, 0);
}