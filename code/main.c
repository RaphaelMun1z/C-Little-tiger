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

#ifdef _WIN32
    #include <windows.h>
    void setColor(int textColor, int backgroundColor){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, textColor + (backgroundColor * 16));
    }
#else
    void setColor(int textColor, int backgroundColor) {
        // Ajuste para mapeamento ANSI
        const char *colorCodes[] = {
            "30", "34", "32", "36", "31", "35", "33", "37" // Preto, Azul, Verde, Ciano, Vermelho, Magenta, Amarelo, Branco
        };
        const char *bgColorCodes[] = {
            "40", "44", "42", "46", "41", "45", "43", "47" // Fundo: Preto, Azul, Verde, Ciano, Vermelho, Magenta, Amarelo, Branco
        };

        if (textColor >= 0 && textColor < 8 && backgroundColor >= 0 && backgroundColor < 8) {
            printf("\033[%s;%sm", colorCodes[textColor], bgColorCodes[backgroundColor]);
        }
    }
#endif

void withdrawMoney();
void deleteUser();

int main()
{
    int opt;

    setColor(6, 0);
    printf("\n");
    printf(" _    〔 〕 _______  _______  _     _____                    \n");
    printf("¦ ¦    ¦ ¦ ¦__  __¦ ¦__  __¦ ¦ ¦    ¦ ___¦                   \n");
    printf("¦ ¦    ¦ ¦    ¦ ¦      ¦ ¦   ¦ ¦    ¦ ¦_                     \n");
    printf("¦ ¦    ¦ ¦    ¦ ¦      ¦ ¦   ¦ ¦    ¦  _¦                    \n");
    printf("¦ ¦___ ¦ ¦    ¦ ¦      ¦ ¦   ¦ ¦__  ¦ ¦__                    \n");
    printf("¦____¦ ¦_¦    ¦_¦      ¦_¦   ¦____¦ ¦____¦                   \n");
    printf("                                                             \n");
    printf("            _______ 〔 〕 ___ _   ____   _ __                 \n");
    printf("            ¦__  __¦ ¦ ¦ ╱  _╰ ¦ ¦ __¦ ¦ ╯__¦                \n");
    printf("               ¦ ¦   ¦ ¦ ¦ ╱_¦ ¦ ¦ ╲   ¦ ¦                   \n");
    printf("               ¦ ¦   ¦ ¦ ╲___, ¦ ¦ ╱_  ¦ ¦                   \n");
    printf("               ¦ ¦   ¦_¦ ¦_____╱ ¦___¦ ¦_¦                   \n");
    printf("               ¦_¦   ========================                \n");
    printf("\n");
    setColor(7, 0);

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
                        setColor(6, 0);
                        printf("⚠️  Saldo insuficiente!\n");
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
                        setColor(6, 0);
                        printf("⚠️  Saldo insuficiente!\n");
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
                        setColor(6, 0);
                        printf("⚠️  Saldo insuficiente!\n");
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
            if (authenticatedUser != -1 && players[authenticatedUser].accessLevel == 1)
            {
                deleteUser();
            }
            else
            {
                setColor(4, 0);
                printf("❌ Você não tem acesso a essa função!\n");
                setColor(7, 0);
            }
            break;

        case 9:
        {
            int userCode;
            printf("Informe o código: ");
            scanf("%d", &userCode);
            getByIdUserDetails(userCode);
            break;
        }

        case 10:
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

        case 11:
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
    } while (opt != 11);

    return 0;
}