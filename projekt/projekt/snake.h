#ifndef SNAKE_H
#define SNAKE_H

typedef struct zmija* point;
typedef struct zmija {
    int x;
    int y;
    point next;
} zm;

extern int size;

int find(int x, int y, point head);
void grow(point head);
point findHead(point snake);
void deleteSnake(point snake);
int checkDeath(point snake);
void move(char input, point head);

#endif // !SNAKE_H

