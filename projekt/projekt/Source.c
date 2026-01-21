#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "console.h"
#include "game.h"
#include "snake.h"
#include "food.h"

int gameState = 1;

int main(){
	srand(time(NULL));
	hideCursor();

	fd fhead = { 0, 0, NULL };
	zm head = { 0, 0, NULL };

	while (gameState){
		game(head, fhead);
	}

	return 0;
}