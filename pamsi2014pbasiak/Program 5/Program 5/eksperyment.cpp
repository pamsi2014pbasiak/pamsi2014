#include "eksperyment.h"

void eksperyment(Graf & graf){
	int  n;
	double p, czas;
	string algorytm[] = {"Kruskal (macierz):\t", "Kruskal (lista):\t", "Prim (macierz):\t\t", "Prim (lista):\t\t"};
	
	if(!ile_wierzcholkow(n))
		return;
	if(!jakie_prawdopodobienstwo(n, p))
		return;
	cout << "G(" << n << ", "  << p << ")\n";
	cout << "Wyniki usrednione dla N = " << N << " pomiarow:\n";
	for(int i = 0; i<4; i++){
		czas = MST(graf, i, n, p);
		cout << algorytm[i] << czas << "[s]\n";
	}
	cout << endl;
}

bool ile_wierzcholkow(int & n){
	cout << "Ile wierzcholkow: \n";
	cout << "?> ";
	cin >> n;
	cout << endl;
	if(n>0)
		return 1;
	return 0;
}

bool jakie_prawdopodobienstwo(const int & n, double & p){
	int opcja;
	double x;
	do{
		cout << "Jakie prawdopodobienstwo:\n";
		cout << "1. 3log2(n)/n\n";
		cout << "2. n^(-1/3)\n";
		cout << "3. n^(-1/2)\n";
		cout << "4. Graf pelny Kn\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;

		switch(opcja){
		case 1:
			p = (3 * ( log((double)n) / log(2.0) )) / n;
			return 1;
			break;
		case 2:
			x = -1/3.0;
			p = pow(n,x);
			return 1;
			break;
		case 3:
			x = -1/2.0;
			p = pow(n,x);
			return 1;
			break;
		case 4:
			p = 1.0;
			return 1;
			break;
		case 0:
			return 0;
			break;
		}

	}while(opcja);
	return 0;
}

double MST(Graf & graf, const int & i, const int & n, const double & p){
	vector<double> czasy(N+1, 0.0);
	double czas=0;
	for(int j=0; j<N+1; j++){
		graf.generuj_ER(n,p);
		switch(i){
		case 0:
			czasy[j] = graf.kruskal_macierz();
			break;
		case 1:
			czasy[j] = graf.kruskal_lista();
			break;
		case 2:
			czasy[j] = graf.prim_macierz();
			break;
		case 3:
			czasy[j] = graf.prim_lista();
			break;
		}
	}
	for(int j=1; j<N+1; j++)
		czas+=czasy[j];
	return czas/N;
}