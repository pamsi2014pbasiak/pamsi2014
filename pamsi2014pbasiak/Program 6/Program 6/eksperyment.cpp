#include "eksperyment.h"

void eksperyment(Graf & graf){
	int  n;
	double p, czas;
	string algorytm[] = {"Dijkstra (macierz):\t", "Dijkstra (lista):\t", "Bellman-Ford (macierz):\t", "Bellman_Ford (lista):\t"};
	
	if(!ile_wierzcholkow(n))
		return;
	if(!jakie_prawdopodobienstwo(p))
		return;
	cout << "G(" << n << ", "  << p << ")\n";
	cout << "Wyniki usrednione dla N = " << N << " pomiarow:\n";
	for(int i = 0; i<2; i++){
		czas = odleglosci(graf, i, n, p, 1);
		cout << algorytm[i] << czas << "[s]\n";
	}
	for(int i = 2; i<4; i++){
		czas = odleglosci(graf, i, n, p, 2);
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

bool jakie_prawdopodobienstwo(double & p){
	int opcja;
	do{
		cout << "Jakie prawdopodobienstwo:\n";
		cout << "1. 0.25\n";
		cout << "2. 0.5\n";
		cout << "3. 0.75\n";
		cout << "4. Graf pelny Kn\n";
		cout << "0. POWROT\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;

		switch(opcja){
		case 1:
			p = 0.25;
			return 1;
			break;
		case 2:
			p = 0.5;
			return 1;
			break;
		case 3:
			p = 0.75;
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

double odleglosci(Graf & graf, const int & i, const int & n, const double & p, const int & r){
	vector<double> czasy(N+1, 0.0);
	double czas=0;
	for(int j=0; j<N+1; j++){
		graf.generuj_ER(n,p,r);
		switch(i){
		case 0:
			czasy[j] = graf.Dijkstra_macierz();
			break;
		case 1:
			czasy[j] = graf.Dijkstra_lista();
			break;
		case 2:
			czasy[j] = graf.BF_macierz();
			break;
		case 3:
			czasy[j] = graf.BF_lista();
			break;
		}
	}
	for(int j=1; j<N+1; j++)
		czas+=czasy[j];
	return czas/N;
}