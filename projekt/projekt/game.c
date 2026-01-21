#include <conio.h>
#include <windows.h>

#include "game.h"
#include "console.h"
#include "snake.h"
#include "food.h"
#include "fileio.h"

extern int gameState;

int game(zm head, fd fhead) {

    size = 1;

    clearScreen();
    printAll();

    point temp = malloc(sizeof(zm));
    temp->x = 4;
    temp->y = 4;
    temp->next = NULL;
    head.next = temp;

    printMap(&head, &fhead);

    char i = 0;
    char test = 0;
    char lastInput = 0;
    int gameRunning;

    char start = 0;

    while (start != 32) {
        start = _getch();
        if (start == 32) {
            gameRunning = 1;
        }
        else if (start == 'q') {
            gameState = 0;
            gameRunning = 0;
            return;
        }
        else if (start == 'h') {
            fileHandle(1);
            clearScreen();
            printAll();
        }
    }

    i = 'd';
    DWORD time = GetTickCount();
    DWORD lastMove = GetTickCount() - time;
    DWORD lastFood = GetTickCount() - time;

    while (gameRunning) {

        DWORD now = GetTickCount() - time;
        gameTime = now / 1000;

        printMap(&head, &fhead);

        gotoxy(20, 20);
        printf("Size: %d    Time: %d", size, now / 1000);

        if (_kbhit()) {
            while (_kbhit()) {
                test = _getch();
                if (test == 'w' || test == 'a' || test == 's' || test == 'd')
                    i = test;

            }
        }

        

        if (now - lastFood >= 3000) {
            addFood(&fhead, &head);
            lastFood = now;
        }

        checkFood(&fhead, &head);

        if (now - lastMove >= 250) {
            if (size == 1 || (lastInput == 'w' && i != 's') || (lastInput == 's' && i != 'w') || (lastInput == 'd' && i != 'a') || (lastInput == 'a' && i != 'd') || lastInput == 0) {
                move(i, &head);
                lastMove = now;
                gameRunning = checkDeath(&head);
                lastInput = i;
            }
            else {
                move(lastInput, &head);
                lastMove = now;
                gameRunning = checkDeath(&head);

            }
        }
  

    }

    return 0;
}