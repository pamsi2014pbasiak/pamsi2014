#include "BubbleSort.h"

void BubbleSort(vector<int> & tab){
	int licznik = 0;
    int tmp;
	int dlugosc = tab.size();
    do{
        for(int i=0; i<dlugosc-1; i++){

            if(tab[i]>tab[i+1]){
                tmp=tab[i];
                tab[i]=tab[i+1];
                tab[i+1]=tmp;
            }
		}
		dlugosc--;
	}
	while(dlugosc>1);
}