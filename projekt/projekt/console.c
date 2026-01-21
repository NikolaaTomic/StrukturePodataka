#include <stdio.h>
#include <windows.h>
#include "console.h"
#include "snake.h"
#include "food.h"

extern int gameState;

void hideCursor() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy(int x, int y) {
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Dobij informacije o konzoli
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Ispuni ekran praznim znakovima
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);

    // Ispuni atribut boje
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

    // Premjesti kursor na pocetak
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void printMap(point head, pfood fhead) {
    for (int i = 0; i < 30; i = i + 3) {
        for (int j = 0; j < 10; j++) {

            if (find(i / 3, j, head)) {
                gotoxy(i + 15, j + 9);
                printf("[%c]", 254);
            }
            else if (findFood(i / 3, j, fhead)) {
                gotoxy(i + 15, j + 9);
                printf("[%c]", 237);
            }
            else {
                gotoxy(i + 15, j + 9);
                printf("[ ]");

            }
        }

    }
}

void printAll() {
    gotoxy(45, 1);
    printf(" ___   _  _    _    _  __ ___ \n");
    Sleep(100);
    gotoxy(45, 2);
    printf("/ __| | \\| |  /_\\  | |/ /| __|\n");
    Sleep(100);
    gotoxy(45, 3);
    printf("\\__ \\ | .` | / _ \\ | ' < | _| \n");
    Sleep(100);
    gotoxy(45, 4);
    printf("|___/ |_|\\_|/_/ \\_\\|_|\\_\\|___|\n");
    Sleep(150);


    for (int i = 0; i < 30; i = i + 3) {
        for (int j = 0; j < 10; j++) {

            gotoxy(i + 15, j + 9);
            printf("[ ]");
        }
        Sleep(100);
    }



    gotoxy(87, 10);
    printf("CONTROLS:");
    Sleep(100);
    gotoxy(80, 11);
    printf("---------------------");
    Sleep(100);
    gotoxy(83, 12);
    printf("up:\t\t w");
    Sleep(100);
    gotoxy(83, 13);
    printf("down:\t s");
    Sleep(100);
    gotoxy(83, 14);
    printf("left:\t a");
    Sleep(100);
    gotoxy(83, 15);
    printf("right:\t d");
    Sleep(100);
    gotoxy(78, 17);
    printf("Press space to start game");
    gotoxy(80, 18);
    printf("Press H to show stats");
    gotoxy(81, 19);
    printf("Press Q to quit game");
}

void gameOver() {
    Sleep(1500);

    clearScreen();

    gotoxy(35, 10);
    printf("  ___   _   __  __ ___    ___  __   _____ ___ \n");
    Sleep(100);
    gotoxy(35, 11);
    printf(" / __| /_\\ |  \\/  | __|  / _ \\ \\ \\ / / __| _ \\\n");
    Sleep(100);
    gotoxy(35, 12);
    printf("| (_ |/ _ \\| |\\/| | _|  | (_) | \\ V /| _||   /\n");
    Sleep(100);
    gotoxy(35, 13);
    printf(" \\___/_/ \\_\\_|  |_|___|  \\___/   \\_/ |___|_|_\\\n");

    Sleep(150);
    gotoxy(40, 16);
    printf("Press: R to restart or Press Q to quit");

    char input;

    while (1) {
        input = _getch();

        if (input == 'r') {
            return;
        }
        else if (input == 'q') {
            gameState = 0;
            return;
        }
    }

}
