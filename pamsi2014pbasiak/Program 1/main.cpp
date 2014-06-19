#include <iostream>
#include <ctime>
#include <fstream>
#include <random>
#include <cstdio>

#define ROZMIAR 100

using namespace std;

class Tablica{

private:
	int tab[ROZMIAR];
	int dlugosc;

public:
	int czytaj_z_konsoli();
	int wypisz_na_konsole();
	int wypelnij_liczbami_losowymi();
	int zapisz_do_txt();
	int czytaj_z_txt();
	int zapisz_do_bin();
	int czytaj_z_bin();
	Tablica* kopia();
	Tablica & operator= (const Tablica &t){
		this->dlugosc = t.dlugosc;
		for(int i=0; i<t.dlugosc; i++)
			this->tab[i]=t.tab[i];
		return *this;
	};
};

int Tablica::czytaj_z_konsoli(){
	short unsigned int ile;
	cout << endl << "Ile liczb chcesz podac?: ";
	cin >> ile;
	for(int i=0; i<ile; i++)
		cin >> tab[i];
	dlugosc = ile;
	cout << endl;
	return 1;
}

int Tablica::wypisz_na_konsole(){
	for(int i=0; i<dlugosc; i++)
		cout << endl << tab[i];
	cout << endl << endl;
	return 1;
}

int Tablica::wypelnij_liczbami_losowymi(){
	int wmin, wmax, ile;
	srand((int)time(NULL));
	cout << endl << "Ile liczb chcesz wygenerowac?: ";
	cin >> ile;
	cout << "Podaj wartosc min. generowanych liczb: ";
	cin >> wmin;
	cout << "Podaj wartosc max. generowanych liczb: ";
	cin >> wmax;
	for(int i=0; i<ile; i++)
		tab[i] = (rand()%(wmax-wmin+1))+wmin;
	cout << endl;
	dlugosc = ile;
	return 1;
}

int Tablica::zapisz_do_txt(){
	fstream plik("plik.txt", ios::out);
	for(int i=0; i<dlugosc; i++){
		plik << tab[i] << endl;
		plik.flush();
	}
	plik.close();
	return 1;
}

int Tablica::czytaj_z_txt(){
	int i=0;
	fstream plik("plik.txt", ios::in);
	while(plik!=NULL){
		plik >> tab[i];
		i++;
	}
	dlugosc=i-1;
	return 1;
}

int Tablica::zapisz_do_bin(){
	ofstream plik("plik.bin", ios::out | ios::binary);
	Tablica* T = new Tablica;
	for(int i=0; i<dlugosc; i++)
		T->tab[i]=tab[i];
	T->dlugosc=dlugosc;
	plik.write((char*)(T),sizeof(Tablica));
	delete T;
	plik.close();
	return 1;
}

int Tablica::czytaj_z_bin(){
	ifstream plik("plik.bin", ios::in | ios::binary);
	Tablica* T = new Tablica;
	plik.read((char*)(T), sizeof(Tablica));
	dlugosc=T->dlugosc;
	for(int i=0; i<dlugosc; i++)
		tab[i]=T->tab[i];
	plik.close();
	delete T;
	return 1;
}

Tablica* Tablica::kopia(){
	Tablica* T = new Tablica;
	T->dlugosc = dlugosc;
	for(int i=0; i<dlugosc; i++)
		T->tab[i]=tab[i];
	return T;
}

int main(){

	Tablica tablica;
	Tablica *b;
	unsigned short int opcja;
	do{
		cout << "1. Wczytywanie tablicy z konsoli" << endl;
		cout << "2. Wyswietlanie tablicy" << endl;
		cout << "3. Wczytywanie z pliku tekstowego" << endl;
		cout << "4. Zapis do pliku tekstowego" << endl;
		cout << "5. Wczytywanie z pliku binarnego" << endl;
		cout << "6. Zapis do pliku binarnego" << endl;
		cout << "7. Wypelnianie tablicy liczbami losowymi" << endl;
		cout << "8. Tworzenie dynam. kopii + wyswietlanie" << endl;
		cout << "0. Koniec" << endl;
		cout << "Wybierz opcje: ";
		cin >> opcja;

		switch(opcja){
			case 0: exit(0); break;
			case 1: tablica.czytaj_z_konsoli(); break;
			case 2: tablica.wypisz_na_konsole(); break;
			case 3: tablica.czytaj_z_txt(); break;
			case 4: tablica.zapisz_do_txt(); break;
			case 5: tablica.czytaj_z_bin(); break;
			case 6: tablica.zapisz_do_bin(); break;
			case 7: tablica.wypelnij_liczbami_losowymi(); break;
			case 8: b=tablica.kopia(); b->wypisz_na_konsole(); delete [] b; break;
		}
	}while(opcja);

	return 0;
}