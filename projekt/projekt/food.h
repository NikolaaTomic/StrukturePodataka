#ifndef FOOD_H
#define FOOD_H

#include "snake.h"

typedef struct food* pfood;
typedef struct food {
    int x;
    int y;
    pfood next;
} fd;

int findFood(int x, int y, pfood fhead);
void addFood(pfood fhead, point snake);
void deleteFood(pfood fhead, pfood target);
void checkFood(pfood fhead, point snake);

#endif // !FOOD_H