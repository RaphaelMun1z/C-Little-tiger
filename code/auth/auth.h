#ifndef AUTH_H
#define AUTH_H

#include "../structs.h"

player *authUser(char email[50], char pass[50]);
void login();
void registerPlayer();
void logoutAccount();

#endif