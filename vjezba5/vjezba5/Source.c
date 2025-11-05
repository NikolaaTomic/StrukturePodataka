#include <stdio.h>
#include <stdlib.h>

typedef struct Broj* point;
typedef struct Broj {
	int br;
	point next;
} Broj;

int push(int, point);
int pop(point);
int read(point);

int main(){

	Broj head = { 0, NULL };

	read(&head);

	printf("rezultat je: %d", head.next->br);

	return 0;
}

int read(point head){
	int result = 0;
	FILE* file = fopen("dat.txt", "r");
	if (file == NULL){
		printf("file nije otvoren :(");
		return -1;
	}
	char buffer[100];
	while (fgets(buffer, sizeof(buffer), file) != NULL){
		printf(" %s \n", buffer);
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (buffer[i] >= 48 && buffer[i] <= 57){
				push(buffer[i] - '0', head);
			}
			else{
				switch (buffer[i]){
				case '+':
					result = pop(head) + pop(head);
					push(result, head);
					break;
				case '*':
					result = pop(head) * pop(head);
					push(result, head);
					break;
				case '-':
					result = pop(head) - pop(head);
					push(result, head);
					break;
				default:
					break;
				}
			}
		}
	}
	return 1;
}

int push(int x, point head) {
	point temp = malloc(sizeof(Broj));
	if (temp == NULL){
		printf("memorija problem");
		return -1;
	}
	temp->next = head->next;
	head->next = temp;
	temp->br = x;

	return 1;
}

int pop(point head){
	point temp = head->next;

	int x = temp->br;

	head->next = temp->next;
	temp->next = NULL;
	free(temp);

	return x;
}