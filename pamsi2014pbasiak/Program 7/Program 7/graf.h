#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <climits>
#include <ctime>
#include <iomanip>

#define INF INT_MAX

using namespace std;


struct krawedz{			// Struktura definiujaca pojecie krawÍdzi
	int v1;
	int v2;
	int przeplyw;
};


class Graf{

private:

	unsigned _v;		// IloúÊ wierzcho≥kÛw
	unsigned _e;		// IloúÊ krawÍdzi
	int _s;			// èrÛd≥o
	int _u;			// Ujúcie
	int f_max;		// Maksymalny przep≥yw sieci
	vector<krawedz> k;			// Wektor krawÍdzi
	vector< vector<int> > C;	// Macierz przepustowoúci
	vector< vector<int> > F;	// Macierz przep≥ywÛw

	void krawedzie_na_macierz();
	void czysc_macierz(vector< vector<int> > & m);

public:

	Graf(): _v(0), _e(0), _s(0), _u(0), f_max(0){};

	int v() const{return _v;};
	int e() const{return _e;};
	int s() const{return _s;};
	int u() const{return _u;};
	int przeplyw() const{return f_max;};

	bool czytaj_z_pliku(const string & nazwa);
	void wypisz_macierz();
	void wypisz_krawedzie();
	void wypisz_przeplywy();
	double mflow();

};


#endif