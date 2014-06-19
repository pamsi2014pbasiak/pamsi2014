#include "QuickSort.h"

void QuickSort(int left, int right, vector<int> & tab){
	int i = left;
	int j = right;
	int tmp = (left+right);
	int pivot = tab[tmp>>1];
	do{
		while(tab[i]<pivot)
			i++;
		while(tab[j]>pivot)
			j--;
		if(i<=j){
			tmp = tab[i];
			tab[i] = tab[j];
			tab[j] = tmp;
			i++;
			j--;
		}
	}while(i<=j);
	if(left<j)
		QuickSort(left, j, tab);
	if(right>i)
		QuickSort(i, right, tab);
}

//vector<int> QuickSort(int left, int right, vector<int> tab){
//	int pivot, i, j, tmp;
//
//	i = (left+right)/2;
//	pivot = tab[i];
//	tab[i] = tab[right];
//	for(i = j = left; i < right; i++)
//		if(tab[i] < pivot)
//		{
//			tmp = tab[i];
//			tab[i] = tab[j];
//			tab[j] = tmp;
//			j++;
//		}
//		tab[right] = tab[j];
//		tab[j] = pivot;
//		if(left < j-1)
//			tab = QuickSort(left, j-1, tab);
//		if(j+1 < right)
//			tab = QuickSort(j+1, right, tab);
//		return tab;
//}