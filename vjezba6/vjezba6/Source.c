#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 300
#define DATE_SIZE 11


typedef struct  _artikl artikl;
typedef artikl* artikl_adresa;
struct _artikl {
    char naziv[BUFFER_SIZE];
    double cijena;
    int kolicina;
    artikl_adresa next;
};



typedef struct  _racun racun;
typedef racun* racun_adresa;
struct _racun {
    artikl artikl_head;
    char datum[DATE_SIZE];
    racun_adresa next;
};


void ReadFiles(racun_adresa);

void ReadRacun(racun_adresa, char*);

void InsertArtikl(artikl_adresa, char*, int, double);

racun_adresa CreateRacun();

artikl_adresa CreateArtikl(char*, int, double);

void PrintRacune(racun_adresa);

void FreeMemory(racun_adresa);


int main() {
    racun racun_head;
    racun_head.next = NULL;
    racun_head.artikl_head.next = NULL;

    ReadFiles(&racun_head);
    PrintRacune(racun_head.next);

    FreeMemory(&racun_head);
    if (racun_head.next == NULL)
    {
        printf("Lista je uspjesno izbrisana!\n");
    }


    return 0;
}



void ReadFiles(racun_adresa headRacun)
{
    FILE* file = fopen("racuni.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open racuni.txt!\n");
        return;
    }

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, file))
    {

        //Skida newline char s kraja buffera
        int size = strlen(buffer);
        if (size > 0 && buffer[size - 1] == '\n')
        {
            buffer[size - 1] = '\0';
        }

        //Stvara novi racun struct i dodaje ga u listi
        racun_adresa temp = CreateRacun();
        if (temp == NULL)
        {
            printf("Error pri alociranju artikla!");
            return;
        }


        //funkcija za citanje racunax
        ReadRacun(temp, buffer);

        //Sortiranje racuna po datumima od najstarijeg do najnovijeg
        racun_adresa previous = headRacun;
        racun_adresa current = headRacun->next;
        while (current != NULL && strcmp(current->datum, temp->datum) < 0)
        {
            previous = previous->next;
            current = current->next;
        }
        temp->next = previous->next;
        previous->next = temp;


    }
    fclose(file);
}

void ReadRacun(racun_adresa headArtikl, char* nazivRacuna)
{
    FILE* file = fopen(nazivRacuna, "r");
    if (file == NULL)
    {
        printf("Error opening file %s  !\n", nazivRacuna);
        return;
    }

    char buffer[BUFFER_SIZE];

    //Citamo prvo datum tj. 1. liniju
    fgets(buffer, BUFFER_SIZE, file);

    //skidamo newline s kraja datuma
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    //ubacujemo u head artikla datum
    strcpy(headArtikl->datum, buffer);

    artikl_adresa HEADARTIKL = &headArtikl->artikl_head;
    //Citamo ostatak datoteke
    while (fgets(buffer, BUFFER_SIZE, file))
    {
        char nazivArtikla[100];
        int kolicina;
        double cijena;
        sscanf(buffer, "%s %d %lf", nazivArtikla, &kolicina, &cijena);

        InsertArtikl(HEADARTIKL, nazivArtikla, kolicina, cijena);
    }

    fclose(file);
}

void InsertArtikl(artikl_adresa head, char* nazivArtikla, int kolicina, double cijena)
{
    artikl_adresa previous = head;
    artikl_adresa current = head->next;

    while (current != NULL && strcmp(current->naziv, nazivArtikla) < 0)
    {
        previous = current;
        current = current->next;
    }

    artikl_adresa temp = CreateArtikl(nazivArtikla, kolicina, cijena);
    if (temp == NULL)
    {
        printf("Error allocating memory for artikl!\n");
        return;
    }

    temp->next = current;
    previous->next = temp;
}

racun_adresa CreateRacun()
{
    racun_adresa temp = (racun_adresa)malloc(sizeof(racun));

    temp->artikl_head.next = NULL;
    temp->next = NULL;
    return temp;
}

artikl_adresa CreateArtikl(char* naziv, int kolicina, double cijena)
{
    artikl_adresa temp = (artikl_adresa)malloc(sizeof(artikl));

    strcpy(temp->naziv, naziv);
    temp->kolicina = kolicina;
    temp->cijena = cijena;
    temp->next = NULL;

    return temp;
}

void PrintRacune(racun_adresa head)
{
    while (head != NULL)
    {
        printf("Datum: %s\n", head->datum);

        artikl_adresa current_artikl = head->artikl_head.next;
        while (current_artikl != NULL)
        {
            printf("\tNaziv: %-20s | Kolicina: %3d | Cijena: %.2lf\n",
                current_artikl->naziv,
                current_artikl->kolicina,
                current_artikl->cijena);
            current_artikl = current_artikl->next;
        }

        printf("\n"); // Space between receipts
        head = head->next;
    }

    printf("\n");
}

void FreeMemory(racun_adresa head)
{
    racun_adresa temp_racun;

    while (head->next != NULL)
    {
        temp_racun = head->next;

        // Free all artikli in this racun
        artikl_adresa temp_artikl = temp_racun->artikl_head.next;
        artikl_adresa next_artikl;

        while (temp_artikl != NULL)
        {
            next_artikl = temp_artikl->next;
            free(temp_artikl);
            temp_artikl = next_artikl;
        }

        // Free the racun itself
        head->next = temp_racun->next;
        free(temp_racun);
    }
}