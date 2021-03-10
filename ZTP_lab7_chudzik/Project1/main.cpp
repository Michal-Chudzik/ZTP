/** INFO:
* Program generuje chmurê 100 losowych punktow w przestrzeni n-wymiarowej.
* Wspolrzêdne sa generowane z tego samego rozkladu normalnego N(5,10),
* nastepnie na podstawie chmury A obliczany jest jej centroid.
* Z centroidu chmury A oblicza chmurê A' czyli kazdy odpowiadaj¹cy punkt
* symetrii osiowej chmury A.
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<random>
#include<numeric>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


using namespace std;


class generatorLiczbNorm {
	// static –poniewa¿ ma byæ jeden generator dla ca³ego programu:
	static default_random_engine rng;
	
	// produkuje liczby o rozk³. normalnym korzystaj¹c z generatora rng:
	normal_distribution<double> dist;
public:
	generatorLiczbNorm(double mi= 0, double sigma = 1) : dist(mi, sigma) {};
	double operator()() {
		return dist(rng);
	}
};
default_random_engine generatorLiczbNorm::rng ;



int main() {
	int vecSiz = 100;					// ilosc losowych punktow
	int wymiar = 10;					// wymiar przestrzeni
	vector<vector<double>> A(vecSiz);	// chmura A
	generatorLiczbNorm b(5, 10);		// wywolanie obiektu liczacego rozklad normalny

	//losowanie i wpisanie liczb do chmury A
	for_each(A.begin(), A.end(), 
		[&b, wymiar](auto& pom) {
		pom = vector<double>(wymiar);
		generate(pom.begin(), pom.end(), b);
	});

	//liczenie centroidu chmury A
	vector<double> centroidA(wymiar);
	for_each(A.begin(), A.end(), [&](const auto& pom) {
		transform(pom.begin(), pom.end(), centroidA.begin(), centroidA.begin(),
			[](double n1, double n2) { return n1 + n2; });
	});
	for_each(centroidA.begin(), centroidA.end(),
		[](auto& pom) {pom /= 100.0;});

	// wypis centroidu chmury A
	copy(centroidA.begin(), centroidA.end(), ostream_iterator<double>(cout, " "));
	
	vector<vector<double>> B;	// druga chmura
	// wpisanie wartosci do chmury B ze wzoru B` = 2C - B
	for_each(A.begin(), A.end(),
		[&](auto& pomA) {
		vector<double> pomB(wymiar);
		transform(pomA.begin(), pomA.end(), centroidA.begin(), pomB.begin(),
			[](double n1, double n2) {return (2 * n2) - n1;	});
		B.push_back(pomB);
	});

	//obliczenie centroidu chmury B
	vector<double> centroidB(wymiar);
	for_each(B.begin(), B.end(), [&](const auto& pom) {
		transform(pom.begin(), pom.end(), centroidB.begin(), centroidB.begin(),
			[](double n1, double n2) { return n1 + n2; });
	});
	for_each(centroidB.begin(), centroidB.end(), [](auto& pom) {
		pom /= 100.0;
	});

	// wypis centroidu chmury B
	cout << endl;
	copy(centroidB.begin(), centroidB.end(), ostream_iterator<double>(cout, " "));
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
}