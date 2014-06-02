#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <iomanip>
#include <ctime>

using namespace std;

struct luk{			// Struktura definiujaca pojecie ³uku
	int wierzcholek1;
	int wierzcholek2;
	int waga;

	bool operator<(const luk &);
};

struct sasiedzi{	// Struktura definiujaca pojecie sasiedztwa
	vector<int> wierzcholek;
	vector<int> waga;
};

class Graf{
private:
	int rozmiar;						// Ilosc wierzcholkow
	vector<luk> g;						// Reprezentacja lukowa
	vector<sasiedzi> g_lista;			// Reprezentacja typu lista
	vector< vector<int> > g_macierz;	// Reprezentacja macierzowa
public:

	void czytaj_z_pliku();
	void zapisz_do_pliku();
	void sortuj();
	int size() {return rozmiar;};

	void wypisz_luki();
	void wypisz_macierz();
	void wypisz_liste();

	void luki_na_macierz();
	void luki_na_liste();
	void macierz_na_luki();
	void lista_na_luki();

	bool czy_spojny(vector< vector<int> > macierz);
	bool czy_spojny(vector<sasiedzi> lista);
	bool czy_cykl(vector< vector<int> > macierz, int poczatek);
	bool czy_cykl(vector<sasiedzi> lista, int poczatek);

	void czysc_macierz();
	void czysc_liste();
	void dodaj_sasiada_macierz(const int & nr);
	void dodaj_sasiada_lista(const int & nr);
	void usun_sasiada_macierz(const int & nr);
	void usun_sasiada_lista(const int & nr);

	double kruskal_macierz();
	double prim_macierz();
	double kruskal_lista();
	double prim_lista();

	void generuj_ER(int n, double p);

};





#endif