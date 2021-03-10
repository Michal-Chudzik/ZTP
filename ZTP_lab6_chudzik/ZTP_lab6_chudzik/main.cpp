/** INFO:
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
/// Obiekt funkcyjny do obliczania ilosci elementow w multisecie
/// </summary>
class obiekt_fun{
public:
	const multiset<int>& obs;
	obiekt_fun(const multiset<int>& obs) : obs(obs) {}			// zainicjalizowanie multisetu wartosciami przekazanymi z funkcji
	void operator() (int& gat){									// operator modyfikuje wartosci z multisetu gat poniewaz jest przekazany przez referencje co oznacza prace na orginale
		auto p = equal_range(obs.begin(), obs.end(), gat);		// liczenie ilosci elementow gatunkow w multisecie i zwrocenie tej ilosci do pair
		gat = distance(p.first, p.second);						// obliczenie ilosci elementow na podstawie iteratorow pobranych z multisetu i wpisanie ich do gat
	}
};

/// <summary>
/// Wywolanie obiektu funkcyjnego
/// </summary>
/// <param name="gat">vector z iloscia gatunkow</param>
/// <param name="obs">multiset z obserwacjami</param>
void count(vector<int>& gat, const multiset<int>& obs) {
	obiekt_fun ob(obs);											// stworzenie obiektu funkcyjnego oraz wywolanie konstruktora
	for_each(gat.begin(), gat.end(), ob);						// petla for_each wywolujaca operator wywolania() dla wszystkich elementow multisetu
}

/// <summary>
/// funkcja pomocnicza do obliczania
/// </summary>
/// <param name="R">Zmienna z vectora R</param>
/// <param name="S">Zmienna z vectora S</param>
/// <returns>Wartosc sumy.</returns>
double tmpsum(int& R, int& S) {
	int tmp = R - S;
	double suma = (tmp * tmp) / ((double)R + (double)S);
	return suma;
}

/// <summary>
/// Wypis
/// </summary>
/// <param name="n">Zmienna do wypisu</param>
void printout(int& n) {
	cout << n << endl;
}

/// <summary>
/// Obiekt funkcyjny do uzupelnienia multisetow
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
/// Funkcja wywolujaca obiekt funkcyjny
/// </summary>
/// <param name="tmp">Referencyjnie przekazany multiset</param>
void randomize(multiset<int>& tmp) {
	obj_fun ob(tmp);
}

int main() {
	srand((unsigned int)time(NULL));
	multiset<int> r;
	multiset<int> s;
	randomize(r);	// uzupelnienie multisetu wartosciami
	randomize(s);
	vector<int> R({ 0,1,2,3,4,5,6,7,8,9 });
	vector<int>	S({ 0,1,2,3,4,5,6,7,8,9 });
	count(R, r);	//wywolanie metody liczacej
	count(S, s);	//wywolanie metody liczacej

	vector<double> tmp;	// vector pomocniczy do sumowania ilosci gatunkow
	// wpisanie statystyki gatunkow do vectora pomocniczego
	transform (R.begin(), R.end(), S.begin(), back_inserter(tmp), tmpsum);

	// wypis danych z R oraz S
	cout << "Dane z R:\n";
	for_each(R.begin(), R.end(), printout);
	cout << "\n\nDane z S:\n";
	for_each(S.begin(), S.end(), printout);

	// zsumowanie statystyki
	cout << "\n\nWartosc Statystyki:\n";
	cout << accumulate<vector<double>::iterator, double>(tmp.begin(), tmp.end(), 0);
}