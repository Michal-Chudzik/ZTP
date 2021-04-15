/** INFO:
* Program generates cloud of 100 random coordinates in n-dimensions space.
* Coordinates are generated from normal distribution N(5,10)
* based on cloud A it calculates clouds centroid.
* From A Centroid calculates cloud A', that is each corresponding point 
* axial symmetry of cloud A.
* 
* Program generuje chmure 100 losowych punktow w przestrzeni n-wymiarowej.
* Wspolrzedne sa generowane z tego samego rozkladu normalnego N(5,10),
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

/// <summary>
/// Class generates normal distribution
/// </summary>
class generatorLiczbNorm {
	// static –because there is one genereator for whole program
	static default_random_engine rng;
	
	// generates numbers from normal distributin using generator rng
	normal_distribution<double> dist;
public:
	generatorLiczbNorm(double mi= 0, double sigma = 1) : dist(mi, sigma) {};
	double operator()() {
		return dist(rng);
	}
};
default_random_engine generatorLiczbNorm::rng ;



int main() {
	int vecSiz = 100;					// quantity of coordinates
	int wymiar = 10;					// dimensions
	vector<vector<double>> A(vecSiz);	// cloud A
	generatorLiczbNorm b(5, 10);		// calling object which calculates normal distribution

	//generating and pushing numbers to cloud A
	for_each(A.begin(), A.end(), 
		[&b, wymiar](auto& pom) {
		pom = vector<double>(wymiar);
		generate(pom.begin(), pom.end(), b);
	});

	//calculating centroid of cloud A
	vector<double> centroidA(wymiar);
	for_each(A.begin(), A.end(), [&](const auto& pom) {
		transform(pom.begin(), pom.end(), centroidA.begin(), centroidA.begin(),
			[](double n1, double n2) { return n1 + n2; });
	});
	for_each(centroidA.begin(), centroidA.end(),
		[](auto& pom) {pom /= 100.0;});

	// print of cloud A centroid
	copy(centroidA.begin(), centroidA.end(), ostream_iterator<double>(cout, " "));
	
	vector<vector<double>> B;	// second cloud
	// pushing value to cloud B with formula B` = 2C - B
	for_each(A.begin(), A.end(),
		[&](auto& pomA) {
		vector<double> pomB(wymiar);
		transform(pomA.begin(), pomA.end(), centroidA.begin(), pomB.begin(),
			[](double n1, double n2) {return (2 * n2) - n1;	});
		B.push_back(pomB);
	});

	// calculating centroid of cloud B
	vector<double> centroidB(wymiar);
	for_each(B.begin(), B.end(), [&](const auto& pom) {
		transform(pom.begin(), pom.end(), centroidB.begin(), centroidB.begin(),
			[](double n1, double n2) { return n1 + n2; });
	});
	for_each(centroidB.begin(), centroidB.end(), [](auto& pom) {
		pom /= 100.0;
	});

	// print of cloud B centroid
	cout << endl;
	copy(centroidB.begin(), centroidB.end(), ostream_iterator<double>(cout, " "));
}