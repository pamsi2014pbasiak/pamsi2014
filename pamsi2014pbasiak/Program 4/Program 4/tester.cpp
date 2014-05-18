#include "tester.h"


void tester(double & time, vector<int> & tab, const int alg){
	clock_t start, finish;

	switch(alg){
	case 1: 
		start = clock();
		QuickSort(0, tab.size()-1, tab);
		finish = clock();
		break;
	case 2:
		start = clock();
		InsertionSort(tab);
		finish = clock();
		break;
	case 3:
		start = clock();
		BubbleSort(tab);
		finish = clock();
		break;
	}

	time = (double)(finish - start) / CLOCKS_PER_SEC;
}