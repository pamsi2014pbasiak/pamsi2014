#include "graf.h"
#include "eksperyment.h"
#include "test.h"

int main(){
	Graf g;
	int opcja;

	do{
		cout << "1. Przetestuj program\n";
		cout << "2. Przeprowadz eksperyment\n";
		cout << "0. ZAKONCZ\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;

		switch(opcja){
		case 1:
			test(g);
			break;
		case 2:
			eksperyment(g);
			break;
		};
	}while(opcja);

	return 1;
}