#include "graf.h"

bool Graf::czytaj_z_pliku(const string & nazwa){
	luk tmp;
    rozmiar=0;
    fstream plik(nazwa, ios::in);
	if(!plik.good())
		return 0;
	plik >> rozmiar >> rozmiar >> w_start;
    while(!plik.eof()){
        plik >> tmp.wierzcholek1 >> tmp.wierzcholek2 >> tmp.waga;
		g.push_back(tmp);
    }
	luki_na_macierz();
	luki_na_liste();
	return 1;
}

void Graf::zapisz_do_pliku(const string & nazwa){
	fstream plik(nazwa, ios::out);
	for(int i=0; i < (int)sciezka.size(); i++){
		plik << i << "\t";
		if(sciezka[i].waga < INF)
			plik << sciezka[i].waga;
		else
			plik << "INF";
		for(int j=0; j<(int)sciezka[i].wierzcholek.size(); j++)
			plik << "\t" << sciezka[i].wierzcholek[j];
		plik << endl;
	}
	plik.flush();
	plik.close();
}

void Graf::wypisz_luki(){
	for(int i=0; i < (int)g.size(); i++)
		cout << setw(3) << g[i].wierzcholek1 << "\t"
			 << setw(3) << g[i].wierzcholek2 << "\t"
			 << setw(3) << g[i].waga << "\n";
	cout << endl;
}

void Graf::wypisz_macierz(){
	for(int i=0; i<rozmiar; i++){
		for(int j=0; j<rozmiar; j++)
			if(g_macierz[i][j] < INF)
				cout << setw(3) << g_macierz[i][j] << "  ";
			else
				cout << "INF  ";
		cout << endl;
	}
	cout << endl;
}

void Graf::wypisz_liste(){
	for(int i=0; i < (int)g_lista.size(); i++){
		cout << setw(3) << i << ":  ";
		for(int j=0; j < (int)g_lista[i].wierzcholek.size(); j++)
			cout << setw(3) << g_lista[i].wierzcholek[j] << "("
				 << setw(3) << g_lista[i].waga[j] << ")  ";
		cout << endl;
	}
	cout << endl;
}

void Graf::wypisz_sciezki(){
	for(int i=0; i < (int)sciezka.size(); i++){
		cout << setw(3) << i << " (";
		if(sciezka[i].waga == INF)
			cout << "INF):  ";
		else
			cout << setw(3) << sciezka[i].waga << "):  ";
		for(int j=0; j < (int)sciezka[i].wierzcholek.size(); j++)
			cout << setw(3) << sciezka[i].wierzcholek[j] << "  ";
		cout << endl;
	}
	cout << endl;
}

void Graf::luki_na_macierz(){
	czysc_macierz();
	for(int i=0; i < (int)g.size(); i++){
		g_macierz[g[i].wierzcholek1][g[i].wierzcholek2] = g[i].waga;
		g_macierz[g[i].wierzcholek2][g[i].wierzcholek1] = g[i].waga;
	}
}

void Graf::luki_na_liste(){
	czysc_liste();
	for(int i=0; i < (int)g.size(); i++)
	{
		g_lista[g[i].wierzcholek1].wierzcholek.push_back(g[i].wierzcholek2);
		g_lista[g[i].wierzcholek2].wierzcholek.push_back(g[i].wierzcholek1);
		g_lista[g[i].wierzcholek1].waga.push_back(g[i].waga);
		g_lista[g[i].wierzcholek2].waga.push_back(g[i].waga);
	}
}

void Graf::czysc_macierz(){
	g_macierz.resize(rozmiar);
	for(int i=0; i<rozmiar; i++){
		g_macierz[i].resize(rozmiar);
		for(int j=0; j<rozmiar; j++)
			g_macierz[i][j] = INF;
	}
}

void Graf::czysc_liste(){
	for(int i=0; i < (int)g_lista.size(); i++){
		g_lista[i].wierzcholek.clear();
		g_lista[i].waga.clear();
	}
	g_lista.clear();
	g_lista.resize(rozmiar);
}

void Graf::czysc_sciezki(){
	for(int i=0; i < (int)sciezka.size(); i++){
		sciezka[i].wierzcholek.clear();
		sciezka[i].waga = INF;
	}
	sciezka.clear();
	sciezka.resize(rozmiar);
}

void Graf::dodaj_do_kolejki(vector<luk> & kolejka, const int & i, const int & j, const int & waga){
	luk tmp;
	tmp.wierzcholek1 = i;
	tmp.wierzcholek2 = j;
	tmp.waga = waga;
	if(!kolejka.size()){
		kolejka.push_back(tmp);
		return;
	}
	if(waga < kolejka[kolejka.size()-1].waga){
		kolejka.push_back(tmp);
		return;
	}
	for(int i=0; i < (int)kolejka.size(); i++)
		if(waga > kolejka[i].waga){
			kolejka.insert(kolejka.begin()+i, tmp);
			return;
		}
}

int Graf::zdejmij_z_kolejki(vector<luk> & kolejka){
	int tmp = kolejka[kolejka.size()-1].wierzcholek2;
	kolejka.pop_back();
	return tmp;
}

double Graf::Dijkstra_macierz(){
	clock_t start, finish;
	vector<luk> kolejka;
	int poprzedni = w_start;
	bool t=false;
	czysc_sciezki();
	start = clock();
	for(int i=0; i<rozmiar; i++)		// Przeszukuje wierzcholek startowy...
		if(g_macierz[w_start][i]<INF){	// ... czy ma jakichs sasiadow.
			t=true;
			dodaj_do_kolejki(kolejka,w_start,i,g_macierz[w_start][i]);
			sciezka[i].wierzcholek.push_back(w_start);
			sciezka[i].wierzcholek.push_back(i);
			sciezka[i].waga = g_macierz[w_start][i];
		}
	sciezka[w_start].waga = 0;
	sciezka[w_start].wierzcholek.push_back(w_start);
	if(!t){
		finish = clock();
		return (double)(finish - start) / CLOCKS_PER_SEC;
	}
	while(kolejka.size()){
		poprzedni = zdejmij_z_kolejki(kolejka);
		for(int i=0; i < rozmiar; i++)
			if(g_macierz[poprzedni][i] < INF)
				if(g_macierz[poprzedni][i]+sciezka[poprzedni].waga < sciezka[i].waga){
					sciezka[i].waga = g_macierz[poprzedni][i]+sciezka[poprzedni].waga;
					sciezka[i].wierzcholek.clear();
					for(int j=0; j < (int)sciezka[poprzedni].wierzcholek.size(); j++)
						sciezka[i].wierzcholek.push_back(sciezka[poprzedni].wierzcholek[j]);
					sciezka[i].wierzcholek.push_back(i);
					dodaj_do_kolejki(kolejka,poprzedni,i,sciezka[i].waga);
				}
	} // WHILE
	finish = clock();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}

double Graf::Dijkstra_lista(){
	clock_t start, finish;
	vector<luk> kolejka;
	int poprzedni = w_start;
	czysc_sciezki();
	start = clock();
	
	if(!g_lista[w_start].wierzcholek.size()){
		sciezka[w_start].waga = 0;
		sciezka[w_start].wierzcholek.push_back(w_start);
		finish = clock();
		return (double)(finish - start) / CLOCKS_PER_SEC;
	}
	sciezka[w_start].waga = 0;
	sciezka[w_start].wierzcholek.push_back(w_start);
	for(int i=0; i < (int)g_lista[w_start].wierzcholek.size(); i++){
		dodaj_do_kolejki(kolejka,w_start,g_lista[w_start].wierzcholek[i],g_lista[w_start].waga[i]);
		sciezka[g_lista[w_start].wierzcholek[i]].wierzcholek.push_back(w_start);
		sciezka[g_lista[w_start].wierzcholek[i]].wierzcholek.push_back(g_lista[w_start].wierzcholek[i]);
		sciezka[g_lista[w_start].wierzcholek[i]].waga = g_lista[w_start].waga[i];
	}
	while(kolejka.size()){
		poprzedni = zdejmij_z_kolejki(kolejka);
		for(int i=0; i < (int)g_lista[poprzedni].wierzcholek.size(); i++)
			if(g_lista[poprzedni].waga[i]+sciezka[poprzedni].waga < sciezka[g_lista[poprzedni].wierzcholek[i]].waga){
				sciezka[g_lista[poprzedni].wierzcholek[i]].waga = g_lista[poprzedni].waga[i]+sciezka[poprzedni].waga;
				sciezka[g_lista[poprzedni].wierzcholek[i]].wierzcholek.clear();
				for(int j=0; j < (int)sciezka[poprzedni].wierzcholek.size(); j++)
					sciezka[g_lista[poprzedni].wierzcholek[i]].wierzcholek.push_back(sciezka[poprzedni].wierzcholek[j]);
				sciezka[g_lista[poprzedni].wierzcholek[i]].wierzcholek.push_back(g_lista[poprzedni].wierzcholek[i]);
				dodaj_do_kolejki(kolejka,poprzedni,g_lista[poprzedni].wierzcholek[i],sciezka[g_lista[poprzedni].wierzcholek[i]].waga);
			}
		}
	finish = clock();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}

double Graf::BF_macierz(){
	clock_t start, finish;
	bool t=false;
	czysc_sciezki();
	start = clock();
	for(int i=0; i<rozmiar; i++)
		if(g_macierz[w_start][i]<INF){
			t=true;
			sciezka[i].wierzcholek.push_back(w_start);
			sciezka[i].wierzcholek.push_back(i);
			sciezka[i].waga = g_macierz[w_start][i];
		}
	sciezka[w_start].waga = 0;
	sciezka[w_start].wierzcholek.push_back(w_start);
	if(!t){
		finish = clock();
		return (double)(finish - start) / CLOCKS_PER_SEC;
	}
	for(int i=1; i<rozmiar; i++){		// PETLA G£ÓWNA n-1 razy
		t = false;
		for(int x=0; x<rozmiar; x++)		// PRZESZUKUJEMY MACIERZ PO x
			for(int y=0; y<rozmiar; y++)	// DLA JAKIEGOS x PRZESZUKUJEMY MACIERZ PO y
				if(g_macierz[x][y] < INF)	// JEZELI ZNALEZIONO S¥SIADA...
					if(sciezka[x].waga+g_macierz[x][y] >= sciezka[x].waga)
						if(sciezka[y].waga > sciezka[x].waga+g_macierz[x][y]){
							t=true;
							sciezka[y].waga = sciezka[x].waga+g_macierz[x][y];
							sciezka[y].wierzcholek.clear();
							for(int j=0; j < (int)sciezka[x].wierzcholek.size(); j++)
								sciezka[y].wierzcholek.push_back(sciezka[x].wierzcholek[j]);
							sciezka[y].wierzcholek.push_back(y);
						} //IF
		if(!t)
			break;
	} //FOR (pêtla g³ówna)
	finish = clock();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}

double Graf::BF_lista(){
	clock_t start, finish;
	bool t=false;
	czysc_sciezki();
	start = clock();
	for(int i=0; i < (int)g_lista[w_start].wierzcholek.size(); i++){
		t=true;
		sciezka[g_lista[w_start].wierzcholek[i]].wierzcholek.push_back(w_start);
		sciezka[g_lista[w_start].wierzcholek[i]].wierzcholek.push_back(g_lista[w_start].wierzcholek[i]);
		sciezka[g_lista[w_start].wierzcholek[i]].waga = g_lista[w_start].waga[i];
	}
	sciezka[w_start].waga = 0;
	sciezka[w_start].wierzcholek.push_back(w_start);
	if(!t){
		finish = clock();
		return (double)(finish - start) / CLOCKS_PER_SEC;
	}
	for(int i=1; i<rozmiar; i++){		// PETLA G£ÓWNA n-1 razy
		t = false;
		for(int x=0; x < (int)g_lista.size(); x++)
			for(int y=0; y < (int)g_lista[x].wierzcholek.size(); y++)
				if(sciezka[x].waga+g_lista[x].waga[y] >= sciezka[x].waga)
					if(sciezka[g_lista[x].wierzcholek[y]].waga > sciezka[x].waga+g_lista[x].waga[y]){
						t=true;
						sciezka[g_lista[x].wierzcholek[y]].waga = sciezka[x].waga+g_lista[x].waga[y];
						sciezka[g_lista[x].wierzcholek[y]].wierzcholek.clear();
						for(int j=0; j < (int)sciezka[x].wierzcholek.size(); j++)
							sciezka[g_lista[x].wierzcholek[y]].wierzcholek.push_back(sciezka[x].wierzcholek[j]);
						sciezka[g_lista[x].wierzcholek[y]].wierzcholek.push_back(g_lista[x].wierzcholek[y]);
					}
		if(!t)
			break;
	} // FOR (pêtla g³ówna)
	finish = clock();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}

void Graf::generuj_ER(const int & n, const double & p, const int & r){
	luk tmp;
	srand((int)time(NULL));
		g.clear();
		rozmiar = n+1;
		czysc_macierz();
		czysc_liste();
		for(int i=0; i<n; i++)
			for(int j=i+1; j<=n; j++)
				if(rand()%10000 < (int)(p*10000)){
					tmp.wierzcholek1 = i;
					tmp.wierzcholek2 = j;
					if(r==1)
						tmp.waga = (rand()%500)+1;
					else if(r==2)
						tmp.waga = (rand()%1011)-100;
					else 
						return;
					g.push_back(tmp);
				}
		w_start = rand()%n;
		luki_na_liste();
		luki_na_macierz();
}