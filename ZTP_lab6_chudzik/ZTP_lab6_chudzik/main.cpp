/** INFO:
* Program generates two series of birds observations, it counts how many
* times they were observations of specific bird species and it 
* calculates statistics based on two series of measurements ten each
* 
* 
* Program generuje dwie serie obserwacji ptakow, liczy ile razy wystapily
* obserwacje poszczegolnych gatunkow oraz oblicza statystyke na
* podstawie dwoch serii pomiarow o dlugosci 10
*/
#include<set>
#include<ctime>
#include<vector>
#include<numeric>
#include<iostream>
#include<algorithm>

using namespace std;

/// <summary>
/// Function object to calculate quantity of elements in multiset
/// </summary>
class obiekt_fun{
public:
	const multiset<int>& obs;
	obiekt_fun(const multiset<int>& obs) : obs(obs) {}			// initialization of multiset 
	void operator() (int& gat){									// operator modyifies values from multiset gat
		auto p = equal_range(obs.begin(), obs.end(), gat);		// counting quantity of spicies in multiset and returning quantity of pairs 
		gat = distance(p.first, p.second);						// calculating quantity of elements base on iterators from multiset
	}
};

/// <summary>
/// Function object call
/// </summary>
/// <param name="gat">vector with quantity of spicies</param>
/// <param name="obs">multiset with observations</param>
void count(vector<int>& gat, const multiset<int>& obs) {
	obiekt_fun ob(obs);											// creating function object and constructor call
	for_each(gat.begin(), gat.end(), ob);						// for_each loop which calls operator() for every element in multiset
}

/// <summary>
/// Tmp function to calculate
/// </summary>
/// <param name="R">Variable from vector R</param>
/// <param name="S">Variable from vector S</param>
/// <returns>Sum value</returns>
double tmpsum(int& R, int& S) {
	int tmp = R - S;
	double suma = (tmp * tmp) / ((double)R + (double)S);
	return suma;
}

/// <summary>
/// Printout
/// </summary>
/// <param name="n">Variable to print</param>
void printout(int& n) {
	cout << n << endl;
}

/// <summary>
/// Function object to fill multiset
/// </summary>
class obj_fun {
public:
	multiset<int>& tmp;
	obj_fun(multiset<int>& tmp) : tmp(tmp) {
		for (int i = 0; i < 1000; i++){
			tmp.insert(rand() % 10);
		}
	}
};

/// <summary>
/// Fucntion which calls function object
/// </summary>
/// <param name="tmp">Multiset passed by reference</param>
void randomize(multiset<int>& tmp) {
	obj_fun ob(tmp);
}

int main() {
	srand((unsigned int)time(NULL));
	multiset<int> r;
	multiset<int> s;
	randomize(r);	// multiset fill
	randomize(s);
	vector<int> R({ 0,1,2,3,4,5,6,7,8,9 });
	vector<int>	S({ 0,1,2,3,4,5,6,7,8,9 });
	count(R, r);	//counting method call
	count(S, s);	

	vector<double> tmp;	// tmp vector to sum up spiecies quantity
	// putting spiecies statistics to tmp vector
	transform (R.begin(), R.end(), S.begin(), back_inserter(tmp), tmpsum);

	// data print from R and S
	cout << "Dane z R:\n";
	for_each(R.begin(), R.end(), printout);
	cout << "\n\nDane z S:\n";
	for_each(S.begin(), S.end(), printout);

	// summed up statistics
	cout << "\n\nWartosc Statystyki:\n";
	cout << accumulate<vector<double>::iterator, double>(tmp.begin(), tmp.end(), 0);
}