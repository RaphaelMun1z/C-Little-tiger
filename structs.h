#ifndef STRUCT_H
#define STRUCT_H

typedef struct
{
    char game[25];
    double result;
    char date[25];
} match;

typedef struct
{
    int code;
    char name[50];
    double balance;
    char sexo;
    int accessLevel;
    char email[50];
    char password[50];
    int matchesFinished;
    match history[30];
} player;

#endif