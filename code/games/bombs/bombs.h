#ifndef BOMBS_H
#define BOMBS_H

void setColor(int textColor, int backgroundColor);
void prepMap();
int haBomba(int x, int y);
int bombAmount();
void genBomb(int qntBombas);
void genMapField(int x, int y);
void genGame();
void showGame();
void showGameResult();
void openField(int ind);
int askCard();
void playBombs();

#endif