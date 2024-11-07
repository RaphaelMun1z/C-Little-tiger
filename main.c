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

int main()
{
    int opt;

    printf("====================| 🐯 LITTLE TIGER 🐯 |====================\n");

    do
    {
        showHomeMenu(authenticatedUser);
        printf("Enter the option: ");
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
                printf("❌ Você não está autenticado!\n");
            }
            break;

        case 2:
            if (authenticatedUser == -1)
            {
                registerPlayer();
            }
            else
            {
                printf("❌ Você não está autenticado!\n");
            }
            break;

        case 3:
            if (authenticatedUser != -1)
            {
                getByIdUserDetails(authenticatedUser);
            }
            else
            {
                printf("❌ Você não está autenticado!\n");
            }
            break;

        case 4:
            if (authenticatedUser != -1)
            {
                showGamesMenu();
                printf("Enter the game: ");
                fflush(stdout);
                scanf("%d", &opt);

                switch (opt)
                {
                case 1:
                    playBombs();
                    break;

                case 2:
                    playBlaze();
                    break;

                case 3:
                    playRoulette();
                    break;

                default:
                    printf("⚠️ Opção inválida!\n");
                    break;
                }
                printf("\n");
            }
            else
            {
                printf("❌ Você não está autenticado!\n");
            }
            break;

        case 5:
            if (authenticatedUser != -1)
            {
                depositMoney();
            }
            else
            {
                printf("❌ Você não está autenticado!\n");
            }
            break;

        case 6:
            if (authenticatedUser != -1)
            {
                printf("Saindo da conta...\n");
                logoutAccount();
            }
            else
            {
                printf("❌ Você não está autenticado!\n");
            }
            break;

        case 7:
            printf("Saindo...\n");
            break;

        default:
            printf("⚠️ Opção inválida!\n");
            break;
        }

    } while (opt != 7);

    return 0;
}