#ifndef EKSPERYMRNT_H
#define EKSPERYMENT_H

#define N 100

#include <string>
#include <cmath>
#include "graf.h"

void eksperyment(Graf & graf);
bool ile_wierzcholkow(int & n);
bool jakie_prawdopodobienstwo(double & p);
double odleglosci(Graf & graf, const int & i, const int & n, const double & p, const int & r);


#endif