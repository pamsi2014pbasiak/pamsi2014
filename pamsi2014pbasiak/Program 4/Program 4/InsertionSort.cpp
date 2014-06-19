#include "InsertionSort.h"

void InsertionSort(vector<int> & tab){
	vector<int> v(1, tab[0]);
	vector<int>::iterator it = v.begin();

	for(unsigned i=1; i < tab.size(); i++){
		it = v.begin();
		while(it!=v.end() && tab[i] > *it){
			it++;
		}
		v.insert(it, tab[i]);
	}
}