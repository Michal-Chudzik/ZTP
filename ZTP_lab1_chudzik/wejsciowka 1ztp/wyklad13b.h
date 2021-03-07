
#include <cstdio>
#include "Dane.h"
using namespace std;

#ifndef wyklad13b_h
#define wyklad13b_h

template <typename T, int rozmiar>
class Tablica :public Dane{
	T A[rozmiar];
public:
	T& operator[](int index);
};

template <typename T, int rozmiar>
T& Tablica<T, rozmiar>::operator[](int index)
{
	if (index >= rozmiar || index < 0)
		return A[0];
	else
		return A[index];
}

#endif