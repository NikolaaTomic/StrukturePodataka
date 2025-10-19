#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person* point;

typedef struct person {
    char name[20];
    char surn[20];
    int year;
    point next;
} person;

point memory(char[], char[], int);
int addStart(char[], char[], int, point);
int addEnd(char[], char[], int, point);
point find(char[], point);
int deleteItem(char[], point);
int print(point);

int main() {

    person head = { "", "", 0, NULL};   //postavljamo head element

    addStart("Niko", "Tomic", 20, &head);
    addStart("Mia", "Gruba", 21, &head);
    addStart("Baldi", "Bata", 10, &head);
    addEnd("Jerko", "Tripo", 21, &head);

    print(&head);

    deleteItem("Tripo", &head);

    print(&head);

    return 0;
}

point memory(char n[], char s[], int yr) {
    point temp = malloc(sizeof(person));
    
    if (temp == NULL) {   //provjera je li alokacija uspjela
        printf("memorija nije zauzeta, greska \n");
        return -1;
    }

    strcpy(temp->name, n);  //strcpy ce prenjeti string u element liste
    strcpy(temp->surn, s);
    temp->year = yr;
    return temp;
}

int addStart(char n[], char s[], int yr, point head) {

    point temp = memory(n, s, yr);   //alokacija memorije

    temp->next = head->next;
    head->next = temp;

    return 1;
}

int addEnd(char n[], char s[], int yr, point head){   
    point temp = memory(n, s, yr);   //alokacija memorije

    point q = head;
    while (q->next != NULL){         //trazimo zadnji element
        q = q->next;
    }

    q->next = temp;                  
    temp->next = NULL;

    return 1;
}

point find(char s[], point head){
    point temp = head->next;   //temp nam je adresa prvog elementa

    while (temp != NULL){

        if (strcmp(temp->surn, s) == 0){   //strcmp ce usporedit dva stringa i vratit 0 ako su isti

            return temp;      //vracamo element koji smo nasli
        }
        temp = temp->next;
    }
    printf("element %s ne postoji u listi", s);    //ako nema elementa onda cemo vratit null
    return NULL;
}

int deleteItem(char s[], point head){
    point temp = find(s, head);  //prvo cemo iskoristit find funkciju da nademo element koji zelimo brisat

    if (temp == NULL){   //ovo je provjera u slucaju da brisemo element koji ne postoji
        return -1;
    }
    
    point q = head;   //q nam je pokazivac na head koji cemo u petlji vrtit
    while (q->next != temp){  //vrtimo dok ne pronademo element prije elementa kojeg zelimo izbrisat
        q = q->next;
    }
    q->next = temp->next;   //dosl moramo "odspojit" taj element iz nase liste
    temp->next = NULL;      //moramo ga odspojit sa obje stranje, ne mozemo ostavit ovaj pointer
    free(temp);             //brisanje

    return 1;
}

int print(point head){
    printf("\n");
    point temp = head->next;            //temp nam je pokazivac na prvi element
    while (temp != NULL){               //vrtimo dok nam pokazivac na element ne bude null (znaci nema vise elemenata duuuh)

        printf("%s \t %s \t %d \n", temp->name, temp->surn, temp->year);

        temp = temp->next;              //ovo je obicni increment (basically nesto kao i++ u for petlji)
    }

    return 1;
}