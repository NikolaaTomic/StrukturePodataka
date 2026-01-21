#include <stdlib.h>
#include "food.h"
#include "snake.h"

int findFood(int x, int y, pfood fhead) {
    pfood i = fhead->next;
    while (i != NULL) {
        if (i->x == x && i->y == y) {
            return 1;
        }
        i = i->next;
    }
    return 0;
}

void addFood(pfood fhead, point snake) {

    pfood temp = malloc(sizeof(fd));

    do {
        temp->x = rand() % 10;
        temp->y = rand() % 10;

    } while (find(temp->x, temp->y, snake) || findFood(temp->x, temp->y, fhead));

    temp->next = fhead->next;
    fhead->next = temp;

}

void deleteFood(pfood fhead, pfood target) {
    pfood i = fhead;
    while (i->next->x != target->x && i->next->y != target->y) {
        i = i->next;
    }
    i->next = target->next;
    target->next = NULL;
    free(target);
}

void checkFood(pfood fhead, point snake) {
    point snakeHead = findHead(snake);

    pfood i = fhead->next;
    while (i != NULL) {
        if (i->x == snakeHead->x && i->y == snakeHead->y) {
            grow(snake);
            deleteFood(fhead, i);
            break;
        }
        i = i->next;
    }
}