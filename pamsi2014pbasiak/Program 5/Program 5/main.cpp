#include "graf.h"
#include "eksperyment.h"
#include "test.h"

int main(){
	Graf d;
	int opcja;

	do{
		cout << "1. Przeprowadz eksperyment\n";
		cout << "2. Przetestuj program\n";
		cout << "0. ZAKONCZ\n";
		cout << "?> ";
		cin >> opcja;
		cout << endl;

		switch(opcja){
		case 1:
			eksperyment(d);
			break;
		case 2:
			test(d);
			break;
		};
	}while(opcja);

	return 1;
}