#include "test.h"

void test(Graf & graf){
	int opcja, n;
	double p, czas;
	do{
		cout << "1. Wczytaj graf z pliku\n";
		cout << "2. Generuj graf Erdosa-Renyiego\n";
		cout << "3. Znajdz odleglosci\n";
		cout << "4. Wyswietl graf\n";
		cout << "5. Zapisz graf do pliku\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;

		switch(opcja){
		case 1:
			if(czytaj(graf))
				cout << "WCZYTANO\n";
			else
				cout << "BLAD!\n";
			cout << endl;
			break;
		case 2:
			if(generuj(graf, n, p))
				cout << "\nWygenerowano G(" << n << ", " << p << ")\n";
			else
				cout << "\nBLAD!\n";
			cout << endl;
			break;
		case 3:
			if(odleglosci(graf, czas))
				cout << "Czas wykonania: " << czas << "s\n\n";
			break;
		case 4:
			wyswietl(graf);
			break;
		case 5:
			if(zapisz(graf))
				cout << "ZAPISANO\n";
			else
				cout << "BLAD!\n";
			cout << endl;
			break;
		}
	}while(opcja);
}

bool generuj(Graf & graf, int & n, double & p){
	int opcja;
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
	cout << endl;
	do{
		cout << "Zakres wag:\n";
		cout << "1. <1; 500>\n";
		cout << "2. <-10; 1000>\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;
		switch(opcja){
		case 1:
			graf.generuj_ER(n,p,1);
			return 1;
			break;
		case 2:
			graf.generuj_ER(n,p,2);
			return 1;
			break;
		case 0:
			return 0;
			break;
		}
	}while(opcja);
	return 1;
}

void wyswietl(Graf & graf){
	int opcja;

	do{
		cout << "1. Wyswietl luki\n";
		cout << "2. Wyswietl macierz\n";
		cout << "3. Wyswietl liste\n";
		cout << "4. Wyswietl sciezki\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;
		switch(opcja){
		case 1:
			graf.wypisz_luki();
			break;
		case 2:
			graf.wypisz_macierz();
			break;
		case 3:
			graf.wypisz_liste();
			break;
		case 4:
			graf.wypisz_sciezki();
			break;
		}
	}while(opcja);
}

bool odleglosci(Graf & graf, double & czas){
	int opcja;
	do{
		cout << "1. Dijkstra (macierz)\n";
		cout << "2. Dijkstra (lista)\n";
		cout << "3. B-F (macierz)\n";
		cout << "4. B-F (lista)\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;

		switch(opcja){
		case 1:
			czas = graf.Dijkstra_macierz();
			return 1;
			break;
		case 2:
			czas = graf.Dijkstra_lista();
			return 1;
			break;
		case 3:
			czas = graf.BF_macierz();
			return 1;
			break;
		case 4:
			czas = graf.BF_lista();
			return 1;
			break;
		case 0:
			return 0;
			break;
		}
	}while(opcja);
		return 0;
}

bool zapisz(Graf & graf){
	string nazwa;
	cout << "Podaj nazwe pod jaka zapisac (0 aby powrocic):\n";
	cout << "?>: ";
	cin >> nazwa;
	cout << endl;
	if(nazwa == "0")
		return 0;
	graf.zapisz_do_pliku(nazwa);
	return 1;
}

bool czytaj(Graf & graf){
	string nazwa;
	cout << "Podaj nazwe pliku (0 aby powrocic):\n";
	cout << "?>: ";
	cin >> nazwa;
	cout << endl;
	if(nazwa == "0")
		return 0;
	if(!graf.czytaj_z_pliku(nazwa))
		return 0;
	return 1;
}