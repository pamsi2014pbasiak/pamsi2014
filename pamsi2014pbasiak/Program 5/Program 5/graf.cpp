#include "graf.h"

bool luk::operator<(const luk & l2){
	return waga < l2.waga;
}

void Graf::czytaj_z_pliku(){
	luk tmp;
    rozmiar=0;
    fstream plik("graf.out", ios::in);
    while(!plik.eof()){
        plik >> tmp.wierzcholek1 >> tmp.wierzcholek2 >> tmp.waga;
        if(tmp.wierzcholek1 > rozmiar)
			rozmiar = tmp.wierzcholek1;
		if(tmp.wierzcholek2 > rozmiar)
			rozmiar = tmp.wierzcholek2;
		g.push_back(tmp);
    }
	rozmiar++;
}

void Graf::zapisz_do_pliku(){
	fstream plik("graf.out", ios::out);
	plik << g[0].wierzcholek1 << "\t" 
		 << g[0].wierzcholek2 << "\t"
		 << g[0].waga;
	for(int i=1; i < (int)g.size(); i++)
		plik << endl
			 << g[i].wierzcholek1 << "\t"
			 << g[i].wierzcholek2 << "\t"
			 << g[i].waga;
	plik.flush();
	plik.close();
}

void Graf::sortuj(){
	sort(g.begin(), g.end());
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
			cout << setw(3) << g_macierz[i][j] << "  ";
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

void Graf::macierz_na_luki(){
	luk tmp;
	g.clear();
	g_lista.clear();
	for(int i=0; i<rozmiar-1; i++)
		for(int j=i+1; j<rozmiar; j++)
			if(g_macierz[i][j] != -1){
				tmp.wierzcholek1 = i;
				tmp.wierzcholek2 = j;
				tmp.waga = g_macierz[i][j];
				g.push_back(tmp);
			}
}

void Graf::lista_na_luki(){
	g.clear();
	g_macierz.clear();
	luk tmp;
	for(int i=0; i<rozmiar; i++)
		for(int j=0; j < (int)g_lista[i].wierzcholek.size(); j++)
			if(i < g_lista[i].wierzcholek[j]){
				tmp.wierzcholek1 = i;
				tmp.wierzcholek2 = g_lista[i].wierzcholek[j];
				tmp.waga = g_lista[i].waga[j];
				g.push_back(tmp);
			}
}

bool Graf::czy_spojny(vector< vector<int> > macierz){
	queue<int> tmp;
	vector<bool> visited(rozmiar,false);
	int z = 0;
	for(int i=1; i<rozmiar; i++)
		if(macierz[0][i]>=0)
			tmp.push(i);
		visited[0]=1;
	if(!tmp.size())
		return 0;
	while(tmp.size()){
		z = tmp.front(); 
		tmp.pop();
		if(!visited[z]){
			visited[z] = 1;
			for(int i=1; i<rozmiar; i++)
				if(macierz[z][i] >= 0)
					tmp.push(i);
		}
	}
	for(int i=0; i<rozmiar; i++)
			if(!visited[i])
				return 0;
	return 1;
}

bool Graf::czy_spojny(vector<sasiedzi> lista){
	vector<bool> visited(rozmiar,false);
	queue<int> tmp;
	int z = 0;
	if(lista[0].wierzcholek.size())
		tmp.push(lista[0].wierzcholek[0]);
	else
		return 0;
	do{
		z=tmp.front();
		tmp.pop();
		if(!visited[z]){
			for(int i=0; i < (int)lista[z].wierzcholek.size(); i++)
				tmp.push(lista[z].wierzcholek[i]);
			visited[z] = 1;
		}
	}while(tmp.size());
	for(int i=0; i < rozmiar; i++)
		if(!visited[i])
			return 0;
	return 1;
}

bool Graf::czy_cykl(vector< vector<int> > macierz, int poczatek){
	stack<int> tmp;
	int teraz;
	vector<bool> visited(rozmiar,false);
	tmp.push(poczatek);
	tmp.push(-1);
	visited[poczatek]=1;
	while(!tmp.empty()){
		poczatek = tmp.top(); tmp.pop();
		teraz = tmp.top(); tmp.pop();
		for(int i=0; i < rozmiar; i++){
			if(macierz[teraz][i]>=0)
				if(!visited[i]){
					tmp.push(i);
					tmp.push(teraz);
					visited[i]=1;
				}
				else if(poczatek != i)
					return true;
		}
	}
	return 0;
}

bool Graf::czy_cykl(vector<sasiedzi> lista, int poczatek){
	vector<bool> visited(rozmiar,false);
	stack<int> tmp;
	int teraz;
	tmp.push(poczatek);
	tmp.push(-1);
	visited[poczatek] = 1;
	while(!tmp.empty()){
		poczatek = tmp.top(); tmp.pop();
		teraz = tmp.top(); tmp.pop();
		for(int i=0; i < (int)lista[teraz].wierzcholek.size(); i++){
			if(!visited[lista[teraz].wierzcholek[i]]){
				tmp.push(lista[teraz].wierzcholek[i]);
				tmp.push(teraz);
				visited[lista[teraz].wierzcholek[i]] = 1;
			}
			else if(poczatek != lista[teraz].wierzcholek[i])
				return true;
		}
	}
	return 0;
}

void Graf::czysc_macierz(){
	g_macierz.resize(rozmiar);
	for(int i=0; i<rozmiar; i++){
		g_macierz[i].resize(rozmiar);
		for(int j=0; j<rozmiar; j++)
			g_macierz[i][j] = -1;
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

void Graf::dodaj_sasiada_macierz(const int & nr){
	g_macierz[g[nr].wierzcholek1][g[nr].wierzcholek2] = g[nr].waga;
	g_macierz[g[nr].wierzcholek2][g[nr].wierzcholek1] = g[nr].waga;
}

void Graf::dodaj_sasiada_lista(const int & nr){
	g_lista[g[nr].wierzcholek1].wierzcholek.push_back(g[nr].wierzcholek2);
	g_lista[g[nr].wierzcholek2].wierzcholek.push_back(g[nr].wierzcholek1);
	g_lista[g[nr].wierzcholek1].waga.push_back(g[nr].waga);
	g_lista[g[nr].wierzcholek2].waga.push_back(g[nr].waga);
}

void Graf::usun_sasiada_macierz(const int & nr){
	g_macierz[g[nr].wierzcholek1][g[nr].wierzcholek2] = -1;
	g_macierz[g[nr].wierzcholek2][g[nr].wierzcholek1] = -1;
}

void Graf::usun_sasiada_lista(const int & nr){
	g_lista[g[nr].wierzcholek1].wierzcholek.pop_back();
	g_lista[g[nr].wierzcholek2].wierzcholek.pop_back();
	g_lista[g[nr].wierzcholek1].waga.pop_back();
	g_lista[g[nr].wierzcholek2].waga.pop_back();
}

double Graf::kruskal_macierz(){
	clock_t start, finish;
	czysc_macierz();
	sortuj();
	start = clock();
	dodaj_sasiada_macierz(0);
	while(!czy_spojny(g_macierz))
		for(int it=1; it < (int)g.size(); it++){
			dodaj_sasiada_macierz(it);
			if(czy_cykl(g_macierz, g[it].wierzcholek1)){
				usun_sasiada_macierz(it);
				g.erase(g.begin()+it);
			}
			else{
				g.erase(g.begin()+it);
				break;
			}
		}
	finish = clock();
	macierz_na_luki();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}

double Graf::prim_macierz(){
	clock_t start, finish;
	vector<bool> visited(rozmiar,false);
	czysc_macierz();
	sortuj();
	start = clock();
	dodaj_sasiada_macierz(0);
	visited[g[0].wierzcholek1] = 1;
	visited[g[0].wierzcholek2] = 1;
	while(!czy_spojny(g_macierz))
		for(int it=1; it < (int)g.size(); it++)
			if( (!visited[g[it].wierzcholek1] && visited[g[it].wierzcholek2]) ||
				(visited[g[it].wierzcholek1] && !visited[g[it].wierzcholek2]) ){
					dodaj_sasiada_macierz(it);
					if(czy_cykl(g_macierz, g[it].wierzcholek1)){
						usun_sasiada_macierz(it);
						g.erase(g.begin()+it);
					}
					else{
						visited[g[it].wierzcholek1] = 1;
						visited[g[it].wierzcholek2] = 1;
						g.erase(g.begin()+it);
						break;
					}
			}
	finish = clock();
	macierz_na_luki();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}

double Graf::kruskal_lista(){
	clock_t start, finish;
	czysc_liste();
	sortuj();
	start = clock();
	dodaj_sasiada_lista(0);
	while(!czy_spojny(g_lista))
		for(int it=1; it < (int)g.size(); it++){
			dodaj_sasiada_lista(it);
			if(czy_cykl(g_lista, g[it].wierzcholek1)){
				usun_sasiada_lista(it);
				g.erase(g.begin()+it);
			}
			else{
				g.erase(g.begin()+it);
				break;
			}
		}
	finish = clock();
	lista_na_luki();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}

double Graf::prim_lista(){
	clock_t start, finish;
	vector<bool> visited(rozmiar,false);
	czysc_liste();
	sortuj();
	start = clock();
	dodaj_sasiada_lista(0);
	visited[g[0].wierzcholek1] = 1;
	visited[g[0].wierzcholek2] = 1;
	while(!czy_spojny(g_lista))
		for(int it=1; it < (int)g.size(); it++)
			if(	(!visited[g[it].wierzcholek1] && visited[g[it].wierzcholek2]) ||
				(visited[g[it].wierzcholek1] && !visited[g[it].wierzcholek2]) ){
					dodaj_sasiada_lista(it);
					if(czy_cykl(g_lista, g[it].wierzcholek1)){
						usun_sasiada_lista(it);
						g.erase(g.begin()+it);
					}
					else{
						visited[g[it].wierzcholek1] = 1;
						visited[g[it].wierzcholek2] = 1;
						g.erase(g.begin()+it);
						break;
					} // ELSE
			} // IF	
	finish = clock();
	lista_na_luki();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}

void Graf::generuj_ER(int n, double p){
	luk tmp;
	srand((int)time(NULL));
	do{
		g.clear();
		rozmiar = n+1;
		czysc_macierz();
		czysc_liste();
		for(int i=0; i<n; i++)
			for(int j=i+1; j<=n; j++)
				if(rand()%10000 < (int)(p*10000)){
					tmp.wierzcholek1 = i;
					tmp.wierzcholek2 = j;
					tmp.waga = rand()%1000;
					g.push_back(tmp);
				}
		luki_na_liste();
	}while(!czy_spojny(g_lista));
	czysc_liste();
}