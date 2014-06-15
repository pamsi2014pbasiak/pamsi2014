#include "eksperyment.h"

void eksperyment(Graf & graf){
	double czas;
	string plik[] = {"2k100-35", "2k200-89", "2k300-53", "2k400-37", "2k500-92",
					 "4k100-23", "4k200-93", "4k300-72", "4k400-64", "4k500-16",
					 "16k100-67", "16k200-48", "16k300-19"};
	
	cout << "Wyniki usrednione dla N = " << N << " pomiarow:\n";
	for(int i = 0; i<13; i++){
		if(!graf.czytaj_z_pliku("grafy/"+plik[i]+".txt"))
			cout << "BLAD!\n";
		czas = max_flow(graf);
		cout << plik[i] << ":\t" << czas << " [s]\tPrzeplyw: " << graf.przeplyw() << endl;
	}
	cout << endl;
}

double max_flow(Graf & graf){
	vector<double> czasy(N+1, 0.0);
	double czas=0;
	for(int i=0; i<N+1; i++)
		czasy[i] = graf.mflow();
	for(int i=1; i<N+1; i++)
		czas+=czasy[i];
	return czas/N;
}