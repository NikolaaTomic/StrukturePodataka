#include <stdio.h>
#include <conio.h>
#include "fileio.h"
#include "snake.h"
#include "console.h"

int gameTime = 0;

void printFile() {

    clearScreen();
    FILE* myfile = fopen("dat.txt", "r");

    Sleep(100);
    gotoxy(38, 1);
    printf("   ___ _____ _  _____ ___ ___ _____ ___ ___\n");
    Sleep(100);
    gotoxy(38, 2);
    printf("  / __|_   _/_\\|_   _|_ _/ __|_   _|_ _/ __|\n");
    Sleep(100);
    gotoxy(38, 3);
    printf("  \\__ \\ | |/ _ \\ | |  | |\\__ \\ | |  | | (__ \n");
    Sleep(100);
    gotoxy(38, 4);
    printf("  |___/ |_/_/ \\_\\|_| |___|___/ |_| |___\\___|\n");
    Sleep(100);
    gotoxy(53, 6);
    printf("Press B to go back");


    gotoxy(25, 9);
    int y = 9;
    int x = 25;
    char line[100];
    while (fgets(line, sizeof(line), myfile) != NULL) {
        printf("%s\n", line);
        Sleep(50);
        y++;
        gotoxy(x, y);
        if (y > 23) {
            x = x + 30;
            y = 8;
        }
    }

    fclose(myfile);

    char input = 0;
    while (input != 'b') {
        input = _getch();
    }

}

void addFile() {
    FILE* myfile = fopen("dat.txt", "a");

    fprintf(myfile, "Size: %d  Time: %d\n", size, gameTime);
    fclose(myfile);
}

void fileHandle(int mode) {

    switch (mode)
    {
    case 1:
        printFile();
        break;
    case 2:
        addFile();
        break;
    default:
        break;
    }
}