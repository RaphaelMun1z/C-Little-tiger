#ifndef BLAZE_H
#define BLAZE_H

void BlazeCleanMap();
void BlazeGenSquareInMap(int x, int ind);
void BlazeGenSquaresValues(int qntCards);
void BlazeGenMap(int qntSquares);
void BlazeSetArrowPos(int posX);
void BlazeShowMap();
int BlazeGetWon(int value);
void BlazeGenSelect(double money, char color);
void BlazePrepareMatch();
void playBlaze();

#endif