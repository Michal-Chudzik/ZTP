/** INFO:
* Program using object of class Mikser processes data loaded from test file
* mistrz.txt. Program creates object of class Mikser, next opens and gets 
* data from file so that each line of priority queue contains words from
* one line sorted from longest to shortest. Program at the end saves data
* to file where at the beginning of every line is written number of words
* in this queue.
* 
* Program wykorzystuj¹c obiekt klasy Mikser przetwarza dane wczytane z pliku
* testowego mistrz.txt. Program tworzy obiekt klasy Mikser, a nastenie
* otwiera i wczytuje plik, tak aby kazdy wiersz kolejki priorytetowej
* zawiera³ s³owa z jednego wiersza posortowane pod wzglêdem ich dlugosci,
* od najdluzszych do najkrotszych. Program na koniec zapisuje dane do pliku
* w ktorym na poczatku kazdej linii jest zapisana liczba slow w danej kolejce
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include<list>

using namespace std;



/// <summary>
/// Method skipping spaces in line
/// </summary>
/// <param name="slowo">variable containing one word</param>
/// <returns>One word</returns>
string space(string slowo) {
	string tmp;
	for (int i = 0; i < slowo.length(); i++) {
		if (slowo.at(i) != ' ') {
			tmp += slowo.at(i);
		}
	}
	return tmp;
}

/// <summary>
/// Template to sort in good order
/// </summary>
/// <typeparam name="T">Variable type</typeparam>
template<class T>
struct greaters {	
	bool operator()(const T& x, const T& y)const {
		return (x.length() < y.length());
	}
};

/// <summary>
/// Template to sort in good order
/// </summary>
/// <typeparam name="T">Variable type</typeparam>
template<class T>
struct lessers { 
	bool operator() (const T& x, const T& y)const {
		return (x.size() < y.size());
	}
};


/// <summary>
/// Overloaded output operator to file
/// </summary>
/// <param name="os">Reference to stream</param>
/// <param name="pt">Object to output</param>
/// <returns>Stream</returns>
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


class Mikser : public list<priority_queue<string, vector<string>, greaters<string>>>{
public:
	Mikser() = delete;
	Mikser(const char* filename) { open(filename); };
	~Mikser();
	void open(const char* filename);
	void write(const char* filename);
	void execute();
};

/// <summary>
/// Destructor of Mikser class
/// </summary>
Mikser::~Mikser() {
	while (!empty()) {
		pop_back();
	}
}

/// <summary>
/// Method opens a file and sort it content
/// </summary>
/// <param name="filename">File name</param>
void Mikser::open(const char* filename) {
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			vector<string> slowa;
			string tmp = "";
			int i = 0;
			// loop on range of every character of a line
			for (auto x : line) {
				i++;
				if (x == ' ' && i != line.length()) { // searching for end of a word which is not line ending
					tmp = space(tmp);
					slowa.push_back(tmp);
					tmp = "";
				}
				else {		// if its not the end of the word it puts next character in tmp 
					tmp += x;
				}
			}
			tmp = space(tmp);	// deleting space at the end of the line
			slowa.push_back(tmp);	// pushing word from vector
			Mikser::push_back(priority_queue<string, vector<string>, greaters<string> >());		// putting priority queue to list
			list<priority_queue<string, vector<string>, greaters<string>>>::iterator it = end();	// list iterator
			it--;
			// loop pushing words to list
			for (auto i = slowa.begin(); i != slowa.end(); i++){ 
				it->push(*i);
			}
		}
	}
	file.close();	// closing file
}

/// <summary>
/// Method saving data to file
/// </summary>
/// <param name="filename">File name</param>
void Mikser::write(const char* filename) {
	ofstream file(filename);
	for (auto it = begin(); it != end(); it++) {
		file << *it;	// overload output operator
	}
	file.close();
}

/// <summary>
/// Sorting method
/// </summary>
void Mikser::execute() {	
	sort(lessers<priority_queue<string, vector<string>, greaters<string>>>());
}


int main() {
	Mikser M("mistrz.txt");	
	M.execute();			
	M.write("wyniki.txt");	
}
