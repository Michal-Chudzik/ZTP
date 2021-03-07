#define _CRT_SECURE_NO_WARNINGS
/** INFO:
* Program wykorzystuj¹c obiekt klasy Mikser przetwarza dane wczytane z pliku
* testowego mistrz.txt. Program tworzy obiekt klasy Mikser, a nastenie
* otwiera i wczytuje plik, tak aby kazdy wiersz kolejki priorytetowej
* zawiera³ s³owa z jednego wiersza posortowane pod wzglêdem ich dlugosci,
* od najdluzszych do najkrotszych. Program na koniec zapisuje dane do pliku
* w ktorym na poczatku kazdej linii jest zapisana liczba slow w danej kolejce
*/
#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include<list>

using namespace std;



// metoda pomijajaca spacje
string space(string slowo) {
	string tmp;
	for (int i = 0; i < slowo.length(); i++) {
		if (slowo.at(i) != ' ') {
			tmp += slowo.at(i);
		}
	}
	return tmp;
}

// szablon do sortowania w odpowiedniej kolejnosci
template<class T>
struct greaters {	
	bool operator()(const T& x, const T& y)const {
		return (x.length() < y.length());
	}
};

// szablon do sortowania w odpowiedniej kolejnosci
template<class T>
struct lessers { 
	bool operator() (const T& x, const T& y)const {
		return (x.size() < y.size());
	}
};


//Przeciazony operator wypisania do pliku
ostream& operator<< (ostream& os, priority_queue<string, vector<string>, greaters<string>>& pt) {	
	int siz = pt.size();
	os << siz << ": ";
	for (int i = 0; i < siz; i++) {
		os << pt.top() << " ";
		pt.pop();
	}
	os << endl;
	return os;
}


class Mikser : public list<priority_queue<string, vector<string>, greaters<string> > > {
public:
	Mikser() = delete;
	Mikser(const char* filename) { open(filename); };
	~Mikser();
	void open(const char* filename);
	void write(const char* filename);
	void execute();
};

Mikser::~Mikser() {
	while (!empty()) {
		pop_back();
	}
}
void Mikser::open(const char* filename) {
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			vector<string> slowa;
			string tmp = "";
			int i = 0;
			// petla na zakresie przechodzaca po kazdym znaku linii
			for (auto x : line) {
				i++;
				if (x == ' ' && i != line.length()) { // szukamy koniec slowa ktory nie jest koncem linii 
					tmp = space(tmp);
					slowa.push_back(tmp);
					tmp = "";
				}
				else {		// jesli nie jest koncem slowa wpisujemy nastepna litere w tmp
					tmp += x;
				}
			}
			tmp = space(tmp);	// usuniecie spacji na koncu linii
			slowa.push_back(tmp);	// wpisanie slowa do vectora
			Mikser::push_back(priority_queue<string, vector<string>, greaters<string> >());		// wpisanie priority queue do listy 
			list<priority_queue<string, vector<string>, greaters<string>>>::iterator it = end();	// iterator listy
			it--;
			// petla wpisujaca slowa do listy
			for (auto i = slowa.begin(); i != slowa.end(); i++){ 
				it->push(*i);
			}
		}
	}
	file.close();	// zamkniecie pliku
}

// Metoda zapisujaca dane do pliku
void Mikser::write(const char* filename) {
	ofstream file(filename);
	for (auto it = begin(); it != end(); it++) {
		file << *it;	// wypis korzystajacy z przeciazonego operatora wypisu do pliku
	}
	file.close();
}

// Metoda sortujaca
void Mikser::execute() {	
	sort(lessers<priority_queue<string, vector<string>, greaters<string>>>());
}


int main() {
	Mikser M("mistrz.txt");	// otworzenie pliku i wpisanie danych
	M.execute();			// sortowanie pobranych danych
	M.write("wyniki.txt");	// wypis danych do pliku
}
