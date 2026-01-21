#include <stdlib.h>
#include "snake.h"
#include "console.h"
#include "fileio.h"

int size = 1;

int find(int x, int y, point head) {
    point i = head->next;
    while (i != NULL) {
        if (i->x == x && i->y == y) {
            return 1;
        }
        i = i->next;
    }
    return 0;
}

void grow(point head) {
    point temp = malloc(sizeof(zm));
    temp->x = head->next->x;
    temp->y = head->next->y;

    temp->next = head->next;
    head->next = temp;
    size++;
}

point findHead(point snake) {
    point temp = snake->next;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    return temp;
}

void move(char input, point head) {


    point i = head->next;
    point temp;

    while (i->next != NULL) {
        temp = i->next;
        i->x = temp->x;
        i->y = temp->y;
        i = temp;
    }

    switch (input)
    {
    case 'w':
        i->y = i->y - 1;
        break;
    case 'a':
        i->x = i->x - 1;
        break;
    case 's':
        i->y = i->y + 1;
        break;
    case 'd':
        i->x = i->x + 1;
        break;
    default:
        break;
    }

}

void deleteSnake(point snake){
    point i = snake->next;
    point temp;
    while (i != NULL){
        temp = i;
        i = i->next;
        temp->next = NULL;
        free(temp);
    }
}

int checkDeath(point snake) {
    point snakeHead = findHead(snake);
    point i = snake->next;

    if (snakeHead->x > 9 || snakeHead->x < 0 || snakeHead->y > 9 || snakeHead->y < 0) {
        //deleteSnake(snake);
        gameOver();
        fileHandle(2);
        return 0;
    }

    while (i->next != NULL) {
        if (i->x == snakeHead->x && i->y == snakeHead->y) {
            //deleteSnake(snake);
            gameOver();
            fileHandle(2);
            return 0;
        }
        i = i->next;
    }

    return 1;
}