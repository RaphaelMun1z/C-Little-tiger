#include <stdio.h>
#include <string.h>
#include "../structs.h"
#include "../db/db.h"
#include "user.h"

void setColor(int, int);

int existUserByEmail(char emailParam[])
{
    for (int ii = 0; ii < 14; ii++)
    {
        if (strcmp(players[ii].email, emailParam) == 0)
        {
            return ii;
        }
    }
    return -1;
}

void getByIdUserDetails(int code)
{
    if (code >= contPlayers || code < 0 || code > 13)
    {
        setColor(6, 0);
        printf("⚠️  Código inválido!\n");
        setColor(8, 0);
        return;
    }

    for (int ii = 0; ii < 14; ii++)
    {
        if (players[ii].code == code)
        {
            printf("\n___________________ DETALHES DO USUÁRIO ___________________\n");
            setColor(11, 0);
            printf("Código: %d\n", players[ii].code);
            printf("Nome: %s\n", players[ii].name);
            printf("E-mail: %s\n", players[ii].email);
            printf("Saldo: R$%.2lf\n", players[ii].balance);
            printf("Sexo: %c\n", players[ii].sexo);
            if (players[ii].accessLevel == 1)
            {
                setColor(6, 0);
                printf("Nível de acesso: ADM\n");
                setColor(7, 0);
            }
            else
            {
                printf("Nível de acesso: Jogador\n");
            }
            setColor(7, 0);
            printf("______________________________________________________________\n\n");
            return;
        }
    }

    setColor(6, 0);
    printf("⚠️ Usuário não encontrado!\n");
    setColor(7, 0);
}

void getAllUsersDetails()
{
    printf("\n________________________ DETALHES DOS USUÁRIOS ________________________\n");
    for (int ii = 0; ii < contPlayers; ii++)
    {
        printf("Código: %d\n", players[ii].code);
        printf("Nome: %s\n", players[ii].name);
        printf("E-mail: %s\n", players[ii].email);
        printf("Saldo: %.2lf\n", players[ii].balance);
        printf("Sexo: %c\n", players[ii].sexo);
        if (players[ii].accessLevel == 1)
        {
            setColor(6, 0);
            printf("Nível de acesso: ADM\n");
            setColor(7, 0);
        }
        else
        {
            printf("Nível de acesso: Jogador\n");
        }
        printf("______________________________________________________________\n\n");
    }
}

void depositMoney()
{
    for (int ii = 0; ii < 14; ii++)
    {
        if (players[ii].code == authenticatedUser)
        {
            printf("\n___________________ DEPÓSITO ___________________\n");
            double amount;
            printf("Qual o valor? ");
            fflush(stdout);
            scanf("%lf", &amount);

            if (amount > 0)
            {
                players[ii].balance += amount;
                setColor(2, 0);
                printf("💲 Depósito realizado com sucesso!\n");
                setColor(7, 0);
            }
            else
            {
                setColor(6, 0);
                printf("⚠️ Valor inválido!\n");
                setColor(7, 0);
            }

            printf("______________________________________________________________\n\n");
            return;
        }
    }

    setColor(6, 0);
    printf("⚠️ Não foi possível depositar o dinheiro!\n");
    setColor(7, 0);
}

void withdrawMoney()
{
    for (int ii = 0; ii < 14; ii++)
    {
        if (players[ii].code == authenticatedUser)
        {
            if (players[authenticatedUser].balance < 100)
            {
                setColor(6, 0);
                printf("⚠️  Você não tem saldo mínimo: R$100,00\n");
                setColor(7, 0);
                return;
            }

            printf("\n___________________ SACAR ___________________\n");
            double amount;
            do
            {
                printf("Qual valor deseja sacar? Digite -1 para sair. ");
                scanf("%lf", &amount);

                if (amount == -1)
                    return;

                if (amount <= 0)
                {
                    setColor(6, 0);
                    printf("⚠️  Valor inválido!\n");
                    setColor(7, 0);
                }
                else if (amount > players[authenticatedUser].balance)
                {
                    setColor(6, 0);
                    printf("⚠️  Você não possui saldo suficiente!\n");
                    setColor(7, 0);
                }
            } while (amount <= 0 || amount > players[authenticatedUser].balance);

            players[authenticatedUser].balance -= amount;
            printf("💲 Saque realizado com sucesso!\n");

            printf("______________________________________________________________\n\n");
            return;
        }
    }

    setColor(4, 0);
    printf("⚠️ Não foi possível depositar o dinheiro!\n");
    setColor(8, 0);
}

void chargeValue(double value, int playerCode)
{
    players[playerCode].balance -= value;
    setColor(4, 0);
    printf("SALDO ALTERADO: -R$%.2lf 💸\n", value);
    setColor(8, 0);
}

void addValue(double value, int playerCode)
{
    players[playerCode].balance += value;
    setColor(2, 0);
    printf("SALDO ALTERADO: +R$%.2lf 🚀\n", value);
    setColor(8, 0);
}

void deleteUser()
{
    int code;
    printf("Qual o código do usuário que você deseja deletar? Digite -1 para sair. ");
    scanf("%d", &code);

    if (code == -1)
        return;

    if (code >= contPlayers || code < 0 || code > 13)
    {
        setColor(6, 0);
        printf("⚠️  Código inválido!\n");
        setColor(8, 0);
        return;
    }

    if (code == 0)
    {
        setColor(6, 0);
        printf("⚠️  Você não pode deletar um ADM!\n");
        setColor(8, 0);
        return;
    }

    for (int ii = code; ii < 14; ii++)
    {
        if (ii < 13)
        {
            int next = ii + 1;
            players[ii] = players[next];
        }
    }
    printf("✅ Usuário deletado com sucesso!\n");
    contPlayers--;
}