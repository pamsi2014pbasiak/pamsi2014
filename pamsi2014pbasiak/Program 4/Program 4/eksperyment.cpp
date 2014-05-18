#include "eksperyment.h"

void eksperyment(){
	vector<int> tab;
	vector<double> time;
	double cycle_time, total_time=0;
	int sort_type, sorted_percent;
	unsigned long int size;

	do{
		if(specify_vector_size(size))
			if(select_sort_type(sort_type))
				if(select_sorted_percent(sorted_percent)){
					for(int j=1; j<=3; j++){
						time.clear();
						for(int i=0; i<N+1; i++){
							tab.clear();
							tab = generate(size, sort_type, sorted_percent);
							tester(cycle_time, tab, j);
							time.push_back(cycle_time);
						}
						total_time=0;
						for(int i=1; i<=N; i++)
							total_time+=time[i];	
						cout << "Algorytm " << j << ": " << total_time/N << "s\n";
						cout << endl;
					}
				}
	}while(size>0);
}

bool select_sort_type(int & sort_type){
	cout << "1. Sortowanie z rozkladu Jednostajnego\n";
	cout << "2. Sortowanie z rozkladu Normalnego\n";
	cout << "3. Sortowanie z rozkladu Poissona\n";
	cout << "0. POWROT\n";
	cout << "?> ";
	cin >> sort_type;
	cout << endl;

	return sort_type?true:false;
}

bool specify_vector_size(unsigned long int & size){
	cout << "Ile elementow ma miec tablica? (0 aby zakonczyc)\n?> ";
	cin >> size;
	cout << endl;

	return size>0?true:false;
}

bool select_sorted_percent(int & sorted_percent){
	cout << "Ile elementow ma byc uporzadkowane?\n";
	cout << "(0 - ca³kowicie nieuporzadkowane, 10 - 10% uporzadkowane, 50 -50% uporzadkowane itd.)\n";
	cout << "?> ";
	cin >> sorted_percent;
	cout << endl;
	return sorted_percent<=100?true:false;
}

vector<int> generate(const unsigned long int size, const int sort_type, const int sorted_percent){
	vector<int> tab, tmp;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution1(0,INT_MAX-1);
	std::normal_distribution<> distribution2(5,2);
	std::poisson_distribution<int> distribution3(4);

	unsigned long int to_sort = (int)floor(size*sorted_percent/100.0);

	tmp.clear();

	switch(sort_type){
	case 1:
		for(unsigned i=0; i<size; i++)
			tab.push_back(distribution1(generator));
		sort(tab.begin(), tab.begin()+to_sort);
		break;
	case 2:
		for(unsigned i=0; i<size; i++)
			tab.push_back((int)distribution2(generator));
		sort(tab.begin(), tab.begin()+to_sort);
		break;
	case 3:
		for(unsigned i=0; i<size; i++)
			tab.push_back(distribution3(generator));
		sort(tab.begin(), tab.begin()+to_sort);
		break;
	}

	return tab;
}