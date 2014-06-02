#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct luk{			// Struktura definiujaca pojecie ³uku
	int wierzcholek1;
	int wierzcholek2;
	int waga;

	bool operator<(const luk &);
};

bool luk::operator<(const luk & l2){
	return waga <= l2.waga;
}

void wypisz(luk & l1){
	cout << l1.wierzcholek1 << "/t" << l1.wierzcholek2 << "/t" << l1.waga << endl;
}

class graf{

private:
	vector<luk> g;

public:
	void nowy_luk(luk);
	void sortuj();
	void wypisz_luki();

};

void graf::nowy_luk(luk nowy){
	g.push_back(nowy);
}

void graf::sortuj(){
	sort(g.begin(), g.end());
}

void graf::wypisz_luki(){
	for_each(g.begin(), g.end(), wypisz);
}

int main(){

	return 1;
}