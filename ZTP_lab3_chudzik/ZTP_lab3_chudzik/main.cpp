/** INFO:
* Program using template of container creates own container which storage data
* in dynamic list, next based on template it creates two objects representing
* containers to storage variables. Two series of real numbers representing 
* coordinates in the space of real numbers. Program calculates coordinates 
* p` and q` from p and q, after that it calculates the volume of the hypercube.
* 
* 
* Program korzystajac z szablonu kontenera tworzy wlasny kontener przechowujacy
* dane w liscie dynamicznej, a nastepnie na podstawie tego szablonu tworzy dwa
* obiekty reprezentujace kontenery do przechowywania zmiennych. Dwa ciagi liczb
* rzeczywistych reprezentuja dwa punkty w przestrzeni wspo³rzednych
* rzeczywistych. Program majac dane p i q zapisane w dwoch kontenerach
* bedzie znajdowal dwa punkty p' i q', po czym obliczal objetosc hiperkostki.
*/
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Konten.h"

/// <summary>
/// Getting pseudo-random numbers
/// </summary>
/// <returns>Pseudo-random number</returns>
double randDouble() {
	double f = (double)rand() / RAND_MAX;
	return f * 10;
}

/// <summary>
/// Transform with containers iterators
/// </summary>
/// <typeparam name="T">Type passed to template</typeparam>
/// <param name="i1">Iterator of first container</param>
/// <param name="i2">Iterator pointing to end of the container</param>
/// <param name="i3">Iterator of second container</param>
template<typename T>
void Transform(T& i1, T& i2, T& i3) {
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

/// <summary>
/// Differentiate with containers iterators
/// </summary>
/// <typeparam name="T">Type passed to template</typeparam>
/// <param name="i1">Iterator of first container</param>
/// <param name="i2">Iterator pointing to end of the container</param>
/// <param name="i3">Iterator of second container</param>
template<typename T>
void Differentiate(T& i1, T& i2, T& i3) {
	while (i1 != i2) {
		*i1 = *i1 - *i3;
		i1++;
		i3++;
	}
	i1.set_front();
	i3.set_front();
}

/// <summary>
/// Calculates volume with containers iterators
/// </summary>
/// <typeparam name="T">Type passed to template</typeparam>
/// <typeparam name="N">Type of veriable passed to store result</typeparam>
/// <param name="i1">Iterator of first container</param>
/// <param name="i2">Iterator pointing to end of the container</param>
/// <param name="a">Variable to save result</param>
template<typename T, typename N>
void Volume(T& i1, T& i2, N& a) {
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

	// filling containers
	for (int i = 0; i < 100; i++) {
		kontener1.push(randDouble());
		kontener2.push(randDouble());
	}

	Konten<double>::iterator it1 = Konten<double>::iterator(kontener1);
	Konten<double>::iterator it2 = Konten<double>::iterator(kontener2);
	Konten<double>::iterator it3 = kontener1.end();

	// printing values from containers
	cout << "\n\nkontener1:\tkontener2:\n";
	for (int i = 0; i < kontener1.rozmiar(); i++) {
		cout << setprecision(5) << it1++ << "\t\t" << it2++ << endl;
	}
	it1.set_front();
	it2.set_front();
	
	// transforming and print out of the containers
	Transform<Konten<double>::iterator>(it1, it3, it2);
	cout << "\n\nPo funkcji transformuj\n";
	cout << "\nkontener1:\tkontener2:\n";
	for (int i = 0; i < kontener1.rozmiar(); i++) {
		cout << setprecision(5) << it1++ << "\t\t" << it2++ << endl;
	}
	it1.set_front();
	it2.set_front();
	
	Differentiate<Konten<double>::iterator>(it1, it3, it2);
	
	// calculating and printing result 
	long double obj = 1;
	Volume<Konten<double>::iterator, long double>(it1, it3, obj);
	cout << "\nObjetosc: "<< obj <<endl;
	it1.set_front();

	cout << "\nKoniec programu.\n";
	return 0;
}