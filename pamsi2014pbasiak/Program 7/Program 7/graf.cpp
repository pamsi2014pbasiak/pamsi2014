#include "graf.h"

bool Graf::czytaj_z_pliku(const string & nazwa){
	krawedz tmp;
	fstream plik(nazwa, ios::in);
	k.clear();
	if(!plik.good())
		return 0;
	plik >> _v >> _e >> _s >> _u;
	while(!plik.eof()){
		plik >> tmp.v1 >> tmp.v2 >> tmp.przeplyw;
		k.push_back(tmp);
	}
	krawedzie_na_macierz();
	return 1;
}

void Graf::krawedzie_na_macierz(){
	czysc_macierz(C);
	czysc_macierz(F);
	for(int i=0; i<(int)k.size(); i++)
		C[k[i].v1][k[i].v2] = k[i].przeplyw;
}

void Graf::czysc_macierz(vector< vector<int> > & m){
	m.resize(_v);
	for(unsigned i=0; i<_v; i++){
		m[i].resize(_v);
		for(unsigned j=0; j<_v; j++)
			m[i][j] = 0;
	}
}

double Graf::mflow(){
	vector<int> Cfp(_v, 0);
	queue<int> kolejka;
	int x, cp;
	double start, finish;
	czysc_macierz(F);
	start = clock();
	bool t = false;
	f_max = 0;
	do{
		vector<int> p(_v,0);
		p[_s] = -1;
		Cfp[_s] = INF;
		while(!kolejka.empty())		// CZYSCI KOLEJKÊ
			kolejka.pop();
		kolejka.push(_s);
		t = 0;
		while (!kolejka.empty() && !t){
			x = kolejka.front(); 
			kolejka.pop();
			for (unsigned y = 1; y < _v; y++){
				cp = C[x][y] - F[x][y];
				if (cp && !p[y]){
					p[y] = x;
					if(Cfp[x] > cp)
						Cfp[y] = cp;
					else
						Cfp[y] = Cfp[x];
					if (y == _u){
						f_max += Cfp[_u];
						while (y != _s){
							x = p[y];
							F[x][y] += Cfp[_u];
							F[y][x] -= Cfp[_u];
							y = x;
						} // WHILE (y != _s)
						t = 1; 
						break;
					} // IF (y == _u)
					kolejka.push(y);
				} // IF (cp && !p[y])
			} // FOR
		} // WHILE (!kolejka.empty() && !t)
	} while(t); // DO
	finish = clock();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}

void Graf::wypisz_krawedzie(){
	for(int i=0; i < (int)k.size(); i++)
		cout << setw(3) << k[i].v1 << "\t"
			 << setw(3) << k[i].v2 << "\t"
			 << setw(3) << k[i].przeplyw << "\n";
	cout << endl;
}

void Graf::wypisz_macierz(){
	for(unsigned i=0; i<_v; i++){
		for(unsigned j=0; j<_v; j++)
			cout << setw(3) << C[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
}

void Graf::wypisz_przeplywy(){
	for(unsigned i=0; i<_v; i++)
		for(unsigned j=0; j<_v; j++)
			if(C[i][j])
				cout << i << " >> " << j << " = " << F[i][j] << "/" << C[i][j] << endl;
	cout << endl;
}