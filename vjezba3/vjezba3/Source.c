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

//vjezbe2
point memory(char[], char[], int);
int addStart(char[], char[], int, point);
int addEnd(char[], char[], int, point);
point find(char[], point);
int deleteItem(char[], point);
int print(point);
//vjezbe3
int addBehind(char[], char[], int, point, char[]);
int addAhead(char[], char[], int, point, char[]);
int sort(point);
int addToFile(point);
int getFromFile(point);
point getPrev(char[], point);

int main() {

    person head = { "", "", 0, NULL };   //postavljamo head element

    addStart("Niko", "Tomic", 20, &head);
    addStart("Baldi", "Bata", 10, &head);
    addStart("Mia", "Gruba", 21, &head);
    addEnd("Jerko", "Tripo", 21, &head);

    //print(&head);

    deleteItem("Tripo", &head);

    //print(&head);

    addBehind("Tin", "Soli", 15, &head, "Gruba");
    //print(&head);

    addAhead("Tom", "Skugi", 17, &head, "Soli");
    print(&head);


    sort(&head);
    print(&head);

    addToFile(&head);

    getFromFile(&head);

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

int addEnd(char n[], char s[], int yr, point head) {
    point temp = memory(n, s, yr);   //alokacija memorije

    point q = head;
    while (q->next != NULL) {         //trazimo zadnji element
        q = q->next;
    }

    q->next = temp;
    temp->next = NULL;

    return 1;
}

point find(char s[], point head) {
    point temp = head->next;   //temp nam je adresa prvog elementa

    while (temp != NULL) {

        if (strcmp(temp->surn, s) == 0) {   //strcmp ce usporedit dva stringa i vratit 0 ako su isti

            return temp;      //vracamo element koji smo nasli
        }
        temp = temp->next;
    }
    printf("element %s ne postoji u listi", s);    //ako nema elementa onda cemo vratit null
    return NULL;
}

int deleteItem(char s[], point head) {
    point temp = find(s, head);  //prvo cemo iskoristit find funkciju da nademo element koji zelimo brisat

    if (temp == NULL) {   //ovo je provjera u slucaju da brisemo element koji ne postoji
        return -1;
    }

    point q = head;   //q nam je pokazivac na head koji cemo u petlji vrtit
    while (q->next != temp) {  //vrtimo dok ne pronademo element prije elementa kojeg zelimo izbrisat
        q = q->next;
    }
    q->next = temp->next;   //dosl moramo "odspojit" taj element iz nase liste
    temp->next = NULL;      //moramo ga odspojit sa obje stranje, ne mozemo ostavit ovaj pointer
    free(temp);             //brisanje

    return 1;
}

int print(point head) {
    printf("\n");
    point temp = head->next;            //temp nam je pokazivac na prvi element
    while (temp != NULL) {               //vrtimo dok nam pokazivac na element ne bude null (znaci nema vise elemenata duuuh)

        printf("%s \t %s \t %d \n", temp->name, temp->surn, temp->year);

        temp = temp->next;              //ovo je obicni increment (basically nesto kao i++ u for petlji)
    }

    return 1;
}

int addBehind(char n[], char s[], int yr, point head, char ref[]) {
    point temp = memory(n, s, yr);

    point i = getPrev(ref, head); //trazimo element iza kako bismo mogli promijeniti pointere

    temp->next = i->next;         //mjenjanje pointera
    i->next = temp;
    
    return 1;
}

int addAhead(char n[], char s[], int yr, point head, char ref[]){
    point temp = memory(n, s, yr);

    point i = find(ref, head);      //trazimo element

    temp->next = i->next;           //opet pointeri
    i->next = temp;

    return 1;
}

int sort(point head){           

    point temp;    //temp mi je ubiti onaj prijasnji element
    point n;       //n mi je ubiti onaj element nakon

    for (point i = head; i != NULL; i = i->next){   //vrti se od prvog do zadnjeg.... cak mislim da to nije skroz potrebno ali neka ga

        for (point j = head; j->next != NULL; j = j->next){  //vrti se od prvog pa do predzadnjeg, da se nebi zeznila varijabla n
            if (strcmp(j->surn, j->next->surn) > 0){
                temp = getPrev(j->surn, head);          //ovdje dobijemo prijasnjeg
                n = j->next;                            //obicna zamijena
                j->next = n->next;
                n->next = j;
                temp->next = n;

                j = n;                  //moramo vratiti j jedan korak unazad da se ne zezne petlja
                
            }
        }

    }

    return 1;
}

point getPrev(char ref[], point head) {   //nis spec samo tratzi prijasnjeg
    point i = head;
    while (strcmp(i->next->surn, ref) != 0 && i->next != NULL) {
        i = i->next;
    }
    return i;
}

int addToFile(point head){
    FILE* file = fopen("dat.txt", "w");
    if (file == NULL){
        printf("Nemoze otvorit file");
        return -1;
    }

    point i = head->next;
    while (i != NULL){
        fprintf(file, "%s \t %s \t %d\n", i->name, i->surn, i->year);
        i = i->next;
    }

    fclose(file);
    return 1;
}

int getFromFile(point head){
    char temp1[20], temp2[20];
    int temp3;

    printf("\nU fileu pise: \n");

    FILE* file = fopen("dat.txt", "r");
    if (file == NULL) {
        printf("Nemoze otvorit file");
        return -1;
    }


    while (fscanf(file, "%s \t %s \t %d", temp1, temp2, &temp3) != EOF){
        printf("%s \t %s \t %d \n", temp1, temp2, temp3);
    }

    fclose(file);
    return 1;
}