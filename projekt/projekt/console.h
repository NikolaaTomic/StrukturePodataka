#ifndef CONSOLE_H
#define CONSOLE_H

#include "snake.h"
#include "food.h"

void hideCursor();
void gotoxy(int x, int y);
void clearScreen();
void printMap(point head, pfood fhead);
void printAll();
void gameOver();

#endif // !CONSOLE_H