#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Student{
	char ime[20];
	char prez[20];
	int bodovi;
}st;

int BrojStudenta(){   //jednostavno broji koliko redaka ima datoteka
	int br = 0;
	char temp[400];
	FILE* file = fopen("dat.txt", "r");
	if (file == NULL){
		printf("greska");
		return 0;
	}

	while (fgets(temp, sizeof(temp), file) != NULL){
		br++;
	}

	fclose(file);

	return br;
}

st* Ucitaj(int broj){   //ucitaje podatke u niz koji je dinamicki alociran
	st* niz = (st*)malloc(sizeof(st) * broj);
	
	FILE* file = fopen("dat.txt", "r");
	if (file == NULL) {
		printf("greska");
		return 0;
	}

	for (int i = 0; i < broj; i++){
		fscanf(file, "%s %s %d", niz[i].ime, niz[i].prez, &niz[i].bodovi);
	}
	fclose(file);

	return niz;  //vraca pointer na strukturu jer cemo ga kasnije koristiti kasnije za ispis
}

int Ispis(st* niz, int br){  //uzima niz i broj zato jer drugacije nisamo mogao dobit velicinu niza koji je dinamicki alociran :(
	
	for (int i = 0; i < br; i++) {   //lagani ispis, tu trebamo koristiti velicinu niza koji neznam bez da imam br
		printf("Ime: %s  %s \t Bodovi: %d \t Apsolutni bodovi: %f \n", niz[i].ime, niz[i].prez, niz[i].bodovi, (float)niz[i].bodovi / 100);
	}
	
	free(niz);
	return 0;
}

int main(){

	int brojStudenta = BrojStudenta();   //ova linija mi treba samo za taj br, inace nebi imao nista drugo u main nego funkcije
										 //moglo se ovo obaviti i bez te linije: Ispis(Ucitaj(BrojStudenta()), BrojStudenta())
										 //onda bih ljepo u main imao samo jednu liniju ali eto nema veze
	Ispis(Ucitaj(brojStudenta), brojStudenta);

	//ovaj code bi izgledao puno ljepse da nema pravila da sve treba bit u odvojenim funkcijama 

	return 0;
}