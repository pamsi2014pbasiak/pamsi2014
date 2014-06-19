#include "test.h"

void test(Graf & graf){
	int opcja;
	do{
		cout << "1. Wczytaj graf z pliku\n";
		cout << "2. Wyznacz maksymalny przeplyw (Ford-Fulkerson)\n";
		cout << "3. Wyswietl graf\n";
		cout << "4. Wyswietl przeplyw\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;

		switch(opcja){
		case 1:
			czytaj(graf);
			break;
		case 2:
			cout << "Wykonano w: " << graf.mflow() << " [s]\n";
			cout << endl;
			break;
		case 3:
			wyswietl(graf);
			break;
		case 4:
			cout << "Przeplyw: " << graf.przeplyw() << endl;
			cout << endl;
			break;
		}
	}while(opcja);
}

void czytaj(Graf & graf){
	string nazwa;
	cout << "Podaj nazwe pliku do wczytania:\n";
	cout << "?> ";
	cin >> nazwa;
	cout << endl;
	if(graf.czytaj_z_pliku(nazwa)){
		cout << "Pomslnie wczytano graf!\n";
		cout << "v: " << graf.v() << "\te: " << graf.e() << endl;
		cout << "s: " << graf.s() << "\tu: " << graf.u() << endl;
	}
	else
		cout << "BLAD! Plik nie istnieje\n";
	cout << endl;
}

void wyswietl(Graf & graf){
	int opcja;

	do{
		cout << "1. Wyswietl krawedzie\n";
		cout << "2. Wyswietl macierz\n";
		cout << "3. Wyswietl przeplywy\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;
		switch(opcja){
		case 1:
			graf.wypisz_krawedzie();
			break;
		case 2:
			graf.wypisz_macierz();
			break;
		case 3:
			graf.wypisz_przeplywy();
			break;
		}
	}while(opcja);
}