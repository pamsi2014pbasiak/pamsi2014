#include <iostream>
#include <ctime>
#include <cstdlib>


#include "BubbleSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "tester.h"
#include "eksperyment.h"

using namespace std;

void show_vector(vector<int> tab);

int main(){

	eksperyment();

	system("pause");
	return 1;
}


void show_vector(vector<int> tab){
	for(unsigned i=0; i<tab.size(); i++)
		cout << tab[i] << "  ";
	cout << endl;
}