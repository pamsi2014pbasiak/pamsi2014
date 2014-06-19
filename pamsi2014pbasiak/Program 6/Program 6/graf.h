#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <iomanip>
#include <ctime>
#include <climits>
#include <string>

#define INF INT_MAX

using namespace std;

struct luk{			// Struktura definiujaca pojecie ³uku
	int wierzcholek1;
	int wierzcholek2;
	int waga;
};

struct sasiedzi{	// Struktura definiujaca pojecie sasiedztwa
	vector<int> wierzcholek;
	vector<int> waga;

};

struct trasa{	
	vector<int> wierzcholek;
	int waga;

	trasa(): waga(INF){};
};

class Graf{
private:
	int rozmiar;						// Ilosc wierzcholkow
	int w_start;						// Wierzcholek poczatkowy
	vector<luk> g;						// Reprezentacja lukowa
	vector<sasiedzi> g_lista;			// Reprezentacja typu lista
	vector< vector<int> > g_macierz;	// Reprezentacja macierzowa
	vector<trasa> sciezka;
public:

	bool czytaj_z_pliku(const string & nazwa);
	void zapisz_do_pliku(const string & nazwa);
	void sortuj();
	int size() {return rozmiar;};

	void wypisz_luki();
	void wypisz_macierz();
	void wypisz_liste();
	void wypisz_sciezki();

	void luki_na_macierz();
	void luki_na_liste();

	void czysc_macierz();
	void czysc_liste();
	void czysc_sciezki();
	void dodaj_do_kolejki(vector<luk> & kolejka, const int & i, const int & j, const int & waga);
	int zdejmij_z_kolejki(vector<luk> & kolejka);

	double Dijkstra_macierz();
	double Dijkstra_lista();
	double BF_macierz();
	double BF_lista();

	void generuj_ER(const int & n, const double & p, const int & r);

};





#endif