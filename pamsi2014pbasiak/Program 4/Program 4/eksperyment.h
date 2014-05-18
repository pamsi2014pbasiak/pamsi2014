#ifndef EKSPERYMENT_H
#define EKSPERYMENT_H

#include <vector>
#include <random>
#include <climits>
#include <iostream>
#include <algorithm>

#include "tester.h"
#include <cmath>
#include <iostream>

#define N 100

using namespace std;


void eksperyment();
vector<int> generate(const unsigned long int size, const int sort_type, const int sorted_percent);
bool select_sort_type(int & sort_type);
bool specify_vector_size(unsigned long int & size);
bool select_sorted_percent(int & sorted_percent);

#endif