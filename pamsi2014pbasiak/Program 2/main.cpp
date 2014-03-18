#include <iostream>

using namespace std;

// KLASA STACK ORAZ JEJ METODY
class stack{
private:
    int liczba;
    stack* nastepny;

    stack(){
        liczba = NULL;
        nastepny = NULL;
    }

public:
	stack* push(int);
    stack* pop();
    bool is_empty();
    void show();
};

stack* stack::push(int l){
    stack *tmp = new stack;
    tmp->liczba=l;
    tmp->nastepny=this;
    cout << "Push " << l << endl;
    return tmp;
}

stack* stack::pop(){
    if(is_empty()){
        cout << "Stack is empty!" << endl;
        return NULL;
    }
    cout << liczba << endl;
    return nastepny;
}

bool stack::is_empty(){
    return (this==NULL);
}

void stack::show(){
    int i=0;
    stack* tmp = new stack;
    tmp = this;
    while(!tmp->is_empty()){
        i++;
        tmp=tmp->pop();
    }
    delete [] tmp;
    cout << "Rozmiar: " << i << endl << endl;
}

// KLASA LIST ORAZ JEJ METODY
class list{
private:
    int liczba;
    list *nastepny, *poprzedni;

	// konstruktor
    list(){
        liczba = NULL;
        nastepny = NULL;
        poprzedni = NULL;
    }

public:
    list* push_front(int);
    list* pop_front();
	list* push_back(int);
    list* pop_back();
    bool is_empty();
	void show();
};

list* list::push_front(int l){
    list *tmp = new list;
    tmp->liczba=l;
    tmp->nastepny=this;
    tmp->poprzedni=NULL;
	if(tmp->nastepny != NULL)
		(tmp->nastepny)->poprzedni = tmp;
    return tmp;
}

list* list::pop_front(){
	list *wsk;
	if(is_empty()){
		cout << "List is empty!" << endl;
		return NULL;
	}
    cout << liczba << endl;
	if(this->nastepny != NULL){
		wsk = this->nastepny;
		wsk->poprzedni = NULL;
	}
	return nastepny;
}

list* list::push_back(int l){
	list *wsk;
	list *nowa = new list;
	wsk = this;

	if(is_empty())
		return push_front(l);

	nowa->nastepny=NULL;
	nowa->liczba=l;

	while(wsk->nastepny != NULL){
		wsk = wsk->nastepny;
	}
	/*nowa->poprzedni = wsk;*/
	wsk->nastepny=nowa;
	return this;
}

list* list::pop_back(){
	list *wsk;
	wsk = this;

	if(is_empty()){
		cout << "List is empty!" << endl;
		return NULL;
	}
	if(this->nastepny == NULL)
		return this->pop_front();

	while(wsk->nastepny != NULL)
		wsk=wsk->nastepny;
	wsk=wsk->poprzedni;
	/*delete [] wsk->nastepny;*/
	wsk->nastepny = NULL;

	return this;
}

void list::show(){
	int i=0;
    list* tmp = new list;
    tmp = this;
    while(!tmp->is_empty()){
        i++;
        tmp=tmp->pop_front();
    }
    delete [] tmp;
    cout << "Rozmiar: " << i << endl << endl;
}

bool list::is_empty(){
    return (this==NULL);
}

// MAIN
int main(){
	short unsigned int opcja;
	stack *stos;
	list *lista;
	int dana;

	stos=NULL;
	lista=NULL;

	do{
		cout << endl;
		cout << "1. Dodaj element na poczatek stosu" <<endl;
		cout << "2. Zdejmij element ze stosu" << endl;
		cout << "3. Wyswietl stos oraz jego rozmiar" << endl;
		cout << "4. Dodaj element na poczatek listy" << endl;
		cout << "5. Zdejmij element z poczatku listy" << endl;
		cout << "6. Dodaj element na koncu listy" << endl;
		cout << "7. Zdejmij element z konca listy" << endl;
		cout << "8. Wyswietl liste" << endl;
		cout << "0. Koniec" << endl;
		cout << endl << "Wybor: ";
		cin >> opcja;
		cout << endl;

		switch(opcja){
			case 0: exit(0); break;
			case 1: cin >> dana; stos=stos->push(dana); break;
			case 2: stos = stos->pop(); break;
			case 3: stos->show(); break;
			case 4: cin >> dana; lista = lista->push_front(dana); break;
			case 5: lista = lista->pop_front(); break;
			case 6: cin >> dana; lista = lista->push_back(dana); break;
			case 7: /*lista = lista->pop_back();*/ break;
			case 8: lista->show(); break;
		}
	}while(opcja!=0);


	return 1;
}