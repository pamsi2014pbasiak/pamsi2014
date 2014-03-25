 #include <iostream>
#include <stack>
#include <queue>
#include <ctime>
#include <algorithm>

#define ROZMIAR 63
#define SZEROKOSC 78

using namespace std;

void stos(){
    stack<int> stos;
    stack<int> tmp;
    int dana, szukaj, ilosc=0;
    short unsigned int opcja;

    do{
        cout << "1. Dodaj element" << endl;
        cout << "2. Wyswietl zawartosc stosu" << endl;
        cout << "3. Wyszukaj element" << endl;
        cout << "4. Usun element" << endl;
        cout << "0. Powrot" << endl;
        cout << "?: ";
        cin >> opcja;
        cout << endl;

        switch(opcja){
            case 1:            // DODAJ ELEMENT
                cout << "?: ";
                cin >> dana;
                cout << endl;
                stos.push(dana);
                break;
            case 2:            // WYSWIETL ZAWARTOSC STOSU
                if(stos.empty()){
                    cout << "Stos jest pusty!" << endl << endl;
                    break;
                }
                tmp = stos;
                cout << "Elementy: ";
                while(!tmp.empty()){
                    cout << tmp.top() << "  ";
                    tmp.pop();
                }
                cout << endl << endl;
                break;
            case 3:            // WYSZUKAJ ELEMENT
				if(stos.empty()){
                    cout << "Stos jest pusty!" << endl << endl;
                    break;
                }
                cout << "?: ";
                cin >> szukaj;
                tmp = stos;
                while(!tmp.empty()){
                    if(tmp.top()==szukaj)
                        ilosc++;
                    tmp.pop();
                }
                if(ilosc)
                    cout << "Szukany element znajduje sie na stosie! (sztuk: " << ilosc << ")" << endl << endl;
                else
                    cout << "Szukanego elementu nie ma na stosie!" << endl << endl;
                ilosc = 0;
                break;
            case 4:            // USUN ELEMENT
                if(!stos.empty()){
                    stos.pop();
                    cout << "Usunieto 1 element ze stosu!" << endl << endl;
                }
                else
                    cout << "Stos jest pusty!" << endl << endl;
                break;
            case 0:            // POWROT
                break;
        }
    }while(opcja!=0);

    
}

void kopiec(){
    short unsigned int opcja;
    int kopiec[ROZMIAR];
    int ilosc=0, zakres_min, zakres_max, potega=1, wypisano=0, przesuniecie=0;
	int i=0, j=0;

    do{
        cout << "1. Wypelnij tablice wartosciami losowymi" << endl;
        cout << "2. Przywroc wlasnosci kopca" << endl;
        cout << "3. Wyswietl kopiec" << endl;
        cout << "4. Usun element ze szczytu" << endl;
        cout << "0. Powrot" << endl;
        cout << "?: ";
        cin >> opcja;
        cout << endl;

        switch(opcja){
            case 1:            // WYPELNIJ TABLICE WARTOSCIAMI LOSOWYMI
                srand((int)time(NULL));
				do{
					cout << "Ile liczb wygenerowac?: ";
					cin >> ilosc;
					if(ilosc<1 || ilosc>ROZMIAR)
						cout << "BLAD!: Podaj wartosc z zakresu 1-" << ROZMIAR << endl;
				}while(ilosc<1 || ilosc>ROZMIAR);
                cout << "Podaj wartosc minimalna: ";
                cin >> zakres_min;
                cout << "Podaj wartosc maksymalna: ";
                cin >> zakres_max;
                for(i=0; i<ilosc; i++){
                    kopiec[i]=(rand()%(zakres_max-zakres_min+1))+zakres_min;
                    cout << kopiec[i] << "  ";
                }
                cout << endl;
                break;
            case 2:				// PRZYWROC WLASNOSCI KOPCA
				if(ilosc<1){
					cout << "Kopiec jest pusty!" << endl << endl;
					break;
				}
				if(is_heap(kopiec,kopiec+ilosc)){
					cout << "Wlasciwosci kopca sa zachowane!" << endl << endl;
					break;
				}
                make_heap(kopiec,kopiec+ilosc);
				cout << "Wlasciwosci kopca zostaly przywrocone!" << endl << endl;
                break;
            case 3:            // WYSWIETL KOPPIEC
				potega=1; wypisano=0;
				if(ilosc<1){
					cout << "Kopiec jest pusty!" << endl << endl;
					break;
				}
				while(wypisano!=ilosc){
					for(i=0; i<potega; i++){
						cout << kopiec[wypisano] << "  ";
						++wypisano;
						if(wypisano==ilosc)
							break;
					}
					potega*=2;
					cout << "(" << potega << ")" <<endl;
				}
				cout << endl;
                break;
            case 4:            // USUN ELEMENT ZE SZCZYTU
				if(ilosc<1){
					cout << "Kopiec jest pusty!" << endl << endl;
					break;
				}
				for(i=0; i<ilosc-1; i++)
					kopiec[i]=kopiec[i+1];
				ilosc-=1;
                break;
            case 0:            // POWROT
                break;
        }
    }while(opcja!=0);
}

void kolejka(){
    queue<int> kolejka;
    int dana;
    short unsigned int opcja;

    do{
        cout << "1. Dodaj element na koniec kolejki" << endl;
        cout << "2. Pobierz element z poczatku kolejki" << endl;
        cout << "3. Wyswietl dlugosc kolejki" << endl;
        cout << "0. Powrot" << endl;
        cout << "?: ";
        cin >> opcja;
        cout << endl;

        switch(opcja){
            case 1:			// DODAJ ELEMENT NA KIONIEC KOLEJKI
                cout << "?: ";
                cin >> dana;
                kolejka.push(dana);
                cout << endl;
                break;
            case 2:			// POBIERZ ELEMENT Z POCZATKU KOLEJKI
                if(kolejka.empty()){
                    cout << "Kolejka jest pusta!" <<endl <<  endl;
                    break;
                }
                cout << kolejka.front() << endl << endl;
                kolejka.pop();
                break;
            case 3:			// WYSWIETL DLUGOSC KOLEJKI
                cout << "Rozmiar kolejki: " << kolejka.size() << endl << endl;
                break;
            case 0:			// POWROT
				break;
        }
    }while(opcja!=0);
}


int main(){
    short unsigned int opcja;

    do{
        cout << "1. Stos" << endl;
        cout << "2. Kopiec" << endl;
        cout << "3. Kolejka" << endl;
        cout << "0. Koniec" << endl;
        cout << "?: ";
        cin >> opcja;
        cout << endl;

        switch(opcja){
            case 1: stos(); break;
            case 2: kopiec(); break;
            case 3: kolejka(); break;
            case 0: exit(0); break;
        }
    }while(opcja!=0);

    return 1;
}
