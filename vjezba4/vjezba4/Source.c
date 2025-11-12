#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Cvor* point;
typedef struct Cvor {
    int koef;
    int exp;
    point next;
} Cvor;

point noviCvor(int koef, int exp) {
    point novi = malloc(sizeof(Cvor));
    novi->koef = koef;
    novi->exp = exp;
    novi->next = NULL;
    return novi;
}

// ubacuje clan u polinom po redu eksponenata
int dodajSortirano(point* polinom, int koef, int exp) {
    if (koef == 0) return 0;
    point novi = noviCvor(koef, exp);

    if (*polinom == NULL || (*polinom)->exp < exp) {
        novi->next = *polinom;
        *polinom = novi;
        return 0;
    }

    point trenutni = *polinom;
    point prethodni = NULL;
    while (trenutni && trenutni->exp > exp) {
        prethodni = trenutni;
        trenutni = trenutni->next;
    }

    if (trenutni && trenutni->exp == exp) {
        trenutni->koef += koef;

        if (trenutni->koef == 0) { // briši ako postane 0
            if (prethodni) prethodni->next = trenutni->next;
            else polinom = trenutni->next;
            free(trenutni);
        }
        return 0;
    }

    novi->next = trenutni;
    if (prethodni) prethodni->next = novi;
    else *polinom = novi;
    return 0;
}

point ucitajPolinom(FILE* f) {
    point polinom = NULL;
    int k, e;
    while (fscanf(f, "%d %d", &k, &e) == 2) {
        dodajSortirano(&polinom, k, e);
        if (fgetc(f) == '\n') break; // novi red = novi polinom
    }
    return polinom;
}

point zbrojiPolinome(point p1, point p2) {
    point rez = NULL;
    for (; p1; p1 = p1->next) dodajSortirano(&rez, p1->koef, p1->exp);
    for (; p2; p2 = p2->next) dodajSortirano(&rez, p2->koef, p2->exp);
    return rez;
}

point pomnoziPolinome(point p1, point p2) {
    point rez = NULL;
    for (point i = p1; i; i = i->next) {
        for (point j = p2; j; j = j->next) {
            dodajSortirano(&rez, i->koef * j->koef, i->exp + j->exp);
        }
    }
    return rez;
}

int ispisiPolinom(point p) {
    if (!p) {
        printf("0\n");
        return 0;
    }
    while (p) {
        printf("%dx^%d", p->koef, p->exp);
        p = p->next;
        if (p) printf(" + ");
    }
    printf("\n");
}

int obrisiPolinom(point p) {
    while (p) {
        point temp = p;
        p = p->next;
        temp->next = NULL;
        free(temp);
    }
    return 0;
}

int main() {
    FILE* f = fopen("dat.txt", "r");
    if (!f) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }



    point p1 = ucitajPolinom(f);
    point p2 = ucitajPolinom(f);
    fclose(f);

    printf("Prvi polinom: ");
    ispisiPolinom(p1);
    printf("Drugi polinom: ");
    ispisiPolinom(p2);

    point zbroj = zbrojiPolinome(p1, p2);
    point umnozak = pomnoziPolinome(p1, p2);

    printf("\nZbroj: ");
    ispisiPolinom(zbroj);
    printf("Umnozak: ");
    ispisiPolinom(umnozak);

    obrisiPolinom(p1);
    obrisiPolinom(p2);
    obrisiPolinom(zbroj);
    obrisiPolinom(umnozak);

    return 0;
}