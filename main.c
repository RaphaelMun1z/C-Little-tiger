#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "db/db.h"
#include "interface/interface.h"
#include "auth/auth.h"
#include "user/user.h"
#include "games/bombs/bombs.h"
#include "games/blaze/blaze.h"
#include "games/roulette/roulette.h"

void setColor(int textColor, int backgroundColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor + (backgroundColor * 16));
}

void withdrawMoney();

int main()
{
    int opt;

    printf("====================| 🐯 LITTLE TIGER 🐯 |====================\n");

    do
    {
        setColor(7, 0);
        showHomeMenu(authenticatedUser);
        printf("Opção: ");
        fflush(stdout);
        scanf("%d", &opt);
        printf("\n");

        switch (opt)
        {
        case 1:
            if (authenticatedUser == -1)
            {
                login();
            }
            else
            {
                setColor(4, 0);
                printf("❌ Você já está autenticado!\n");
                setColor(7, 0);
            }
            break;

        case 2:
            if (authenticatedUser == -1)
            {
                registerPlayer();
            }
            else
            {
                setColor(4, 0);
                printf("❌ Você já está autenticado!\n");
                setColor(7, 0);
            }
            break;

        case 3:
            if (authenticatedUser != -1)
            {
                getByIdUserDetails(authenticatedUser);
            }
            else
            {
                setColor(4, 0);
                printf("❌ Você não está autenticado!\n");
                setColor(7, 0);
            }
            break;

        case 4:
            if (authenticatedUser != -1)
            {
                showGamesMenu();
                printf("Escolha o jogo: ");
                fflush(stdout);
                scanf("%d", &opt);

                switch (opt)
                {
                case 1:
                    if (players[authenticatedUser].balance <= 0)
                    {
                        setColor(4, 0);
                        printf("Saldo insuficiente!\n");
                        setColor(7, 0);
                    }
                    else
                    {
                        playBombs();
                    }
                    break;

                case 2:
                    if (players[authenticatedUser].balance <= 0)
                    {
                        setColor(4, 0);
                        printf("Saldo insuficiente!\n");
                        setColor(7, 0);
                    }
                    else
                    {
                        playBlaze();
                    }
                    break;

                case 3:
                    if (players[authenticatedUser].balance <= 0)
                    {
                        setColor(4, 0);
                        printf("Saldo insuficiente!\n");
                        setColor(7, 0);
                    }
                    else
                    {
                        playRoulette();
                    }

                    break;

                default:
                    setColor(6, 0);
                    printf("⚠️  Opção inválida!\n");
                    setColor(7, 0);
                    break;
                }
                printf("\n");
            }
            else
            {
                setColor(4, 0);
                printf("❌ Você não está autenticado!\n");
                setColor(7, 0);
            }
            break;

        case 5:
            if (authenticatedUser != -1)
            {
                depositMoney();
            }
            else
            {
                setColor(4, 0);
                printf("❌ Você não está autenticado!\n");
                setColor(7, 0);
            }
            break;

        case 6:
            if (authenticatedUser != -1)
            {
                withdrawMoney();
            }
            else
            {
                setColor(4, 0);
                printf("❌ Você não está autenticado!\n");
                setColor(7, 0);
            }
            break;

        case 7:
            if (authenticatedUser != -1 && players[authenticatedUser].accessLevel == 1)
            {
                getAllUsersDetails();
            }
            else
            {
                setColor(4, 0);
                printf("❌ Você não tem acesso a essa função!\n");
                setColor(7, 0);
            }
            break;

        case 8:
            if (authenticatedUser != -1)
            {
                setColor(8, 0);
                printf("Saindo da conta...\n");
                setColor(7, 0);
                logoutAccount();
            }
            else
            {
                setColor(4, 0);
                printf("❌ Você não está autenticado!\n");
                setColor(7, 0);
            }
            break;

        case 9:
            setColor(8, 0);
            printf("Saindo...\n");
            setColor(7, 0);
            break;

        default:
            setColor(6, 0);
            printf("⚠️  Opção inválida!\n");
            setColor(7, 0);
            break;
        }
    } while (opt != 9);

    return 0;
}