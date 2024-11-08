#ifndef STRUCT_H
#define STRUCT_H

typedef struct
{
    int code;
    char name[50];
    double balance;
    char sexo;
    int accessLevel;
    char email[50];
    char password[50];
} player;

typedef struct
{
    int code;
    player player;
    char date[11];
} match;

#endif