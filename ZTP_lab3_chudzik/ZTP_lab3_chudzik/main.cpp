/** INFO:
* Program korzystajac z szablonu kontenera tworzy wlasny kontener przechowujacy
* dane w liscie dynamicznej, a nastepnie na podstawie tego szablonu tworzy dwa
* obiekty reprezentujace kontenery do przechowywania zmiennych. Dwa ciagi liczb
* rzeczywistych reprezentuja dwa punkty w przestrzeni wspo�rzednych
* rzeczywistych. Program majac dane p i q zapisane w dwoch kontenerach
* bedzie znajdowal dwa punkty p' i q', po czym obliczal objetosc hiperkostki.
*/
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Konten.h"

double randDouble() {
	double f = (double)rand() / RAND_MAX;
	return f * 10;
}

template<typename T>
void transformuj(T& i1, T& i2, T& i3) {
	while (i1 != i2) {
		if (*i1 < *i3) {
			double tmp;
			tmp = *i1;
			*i1 = *i3;
			*i3 = tmp;
		}
		i1++;
		i3++;
	}
	i1.set_front();
	i3.set_front();
}

template<typename T>
void roznicuj(T& i1, T& i2, T& i3) {
	while (i1 != i2) {
		*i1 = *i1 - *i3;
		i1++;
		i3++;
	}
	i1.set_front();
	i3.set_front();
}

template<typename T, typename N>
void objetosc(T& i1, T& i2, N& a) {
	while (i1 != i2) {
		a = a * (*i1);
		i1++;
	}
	i1.set_front();
}


int main() {
	srand((unsigned int)time(NULL));
	Konten<double> kontener1;
	Konten<double> kontener2;

	for (int i = 0; i < 100; i++) {
		kontener1.push(randDouble());
		kontener2.push(randDouble());
	}

	Konten<double>::iterator it1 = Konten<double>::iterator(kontener1);
	Konten<double>::iterator it2 = Konten<double>::iterator(kontener2);
	Konten<double>::iterator it3 = kontener1.end();

	cout << "\n\nkontener1:\tkontener2:\n";
	for (int i = 0; i < kontener1.rozmiar(); i++) {
		cout << setprecision(5) << it1++ << "\t\t" << it2++ << endl;
	}
	it1.set_front();
	it2.set_front();
	
	transformuj<Konten<double>::iterator>(it1, it3, it2);
	cout << "\n\nPo funkcji transformuj\n";
	cout << "\nkontener1:\tkontener2:\n";
	for (int i = 0; i < kontener1.rozmiar(); i++) {
		cout << setprecision(5) << it1++ << "\t\t" << it2++ << endl;
	}
	it1.set_front();
	it2.set_front();
	roznicuj<Konten<double>::iterator>(it1, it3, it2);
	
	long double obj = 1;
	objetosc<Konten<double>::iterator, long double>(it1, it3, obj);
	cout << "\nObjetosc: "<< obj <<endl;
	it1.set_front();

	cout << "\nKoniec programu.\n";
	return 0;
}