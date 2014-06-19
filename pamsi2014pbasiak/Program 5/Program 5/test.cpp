#include "test.h"

void test(Graf & graf){
	int opcja, n;
	double p, czas;
	do{
		cout << "1. Wczytaj graf z pliku\n";
		cout << "2. Generuj graf Erdosa-Renyiego\n";
		cout << "3. Znajdz MST\n";
		cout << "4. Wyswietl graf\n";
		cout << "5. Zapisz graf do pliku\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;

		switch(opcja){
		case 1:
			graf.czytaj_z_pliku();
			cout << "Wczytano plik (wierzcholki: " << graf.size() << ")\n\n";
			break;
		case 2:
			if(generuj(graf, n, p))
				cout << "\nWygenerowano G(" << n << ", " << p << ")\n";
			else
				cout << "\nBLAD!\n";
			cout << endl;
			break;
		case 3:
			if(MST(graf, czas))
				cout << "Czas wykonania: " << czas << "s\n\n";
			break;
		case 4:
			wyswietl(graf);
			break;
		case 5:
			graf.zapisz_do_pliku();
			break;
		}
	}while(opcja);
}

bool generuj(Graf & graf, int & n, double & p){
	n=0; p=0;

	cout << "Podaj liczbe wierzcholkow\n";
	cout << "?> ";
	cin >> n;
	if(n<1)
		return 0;
	cout << "Podaj prawdopodobienstwo (0.0 ; 1.0>\n";
	cout << "?> ";
	cin >> p;
	if(p<=0 || p>1)
		return 0;
	graf.generuj_ER(n,p);
	return 1;
}

void wyswietl(Graf & graf){
	int opcja;

	do{
		cout << "1. Wyswietl luki\n";
		cout << "2. Wyswietl macierz\n";
		cout << "3. Wyswietl liste\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;
		switch(opcja){
		case 1:
			graf.wypisz_luki();
			break;
		case 2:
			graf.luki_na_macierz();
			graf.wypisz_macierz();
			break;
		case 3:
			graf.luki_na_liste();
			graf.wypisz_liste();
			break;
		}
	}while(opcja);
}

bool MST(Graf & graf, double & czas){
	int opcja;
	do{
		cout << "1. Kruskal (macierz)\n";
		cout << "2. Kruskal (lista)\n";
		cout << "3. Prim (macierz)\n";
		cout << "4. Prim (lista)\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;

		switch(opcja){
		case 1:
			czas = graf.kruskal_macierz();
			return 1;
			break;
		case 2:
			czas = graf.kruskal_lista();
			return 1;
			break;
		case 3:
			czas = graf.prim_macierz();
			return 1;
			break;
		case 4:
			czas = graf.prim_lista();
			return 1;
			break;
		case 0:
			return 0;
			break;
		}
	}while(opcja);
		return 0;
}