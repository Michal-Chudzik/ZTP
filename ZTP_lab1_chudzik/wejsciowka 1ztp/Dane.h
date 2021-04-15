#include <cstdio>
#include <string>
using namespace std;

#ifndef Dane_h
#define Dane_h

class Dane{
private:
	int id;
	string nazwa;
	double pojemn;
	double temp;
public:
	// default constructor
	Dane() {
		id = 0;
		nazwa = ' ';
		pojemn = 0;
		temp = 0;
	}

	// constructor initializer list
	Dane(int sens, double nu, double tem, string nam)
		: id(sens), pojemn(nu), temp(tem), nazwa(nam) {	}

	// overloaded output operator to file
	friend ostream& operator<< (ostream& os, const Dane& d) {
		os << '|' << setw(6) << setfill('0') << d.id <<'|';
		os << left << setw(10) << setfill(' ') << d.nazwa<<'|';
		os << right << fixed << setprecision(1) << setw(7) << d.temp << '|';
		os << setw(6) << fixed << setprecision(0) << d.pojemn << "|\n";
		return os;
	}

	// overloaded operator +=
	Dane& operator+= (const Dane& d) {
		temp += d.temp;
		pojemn += d.pojemn;
		return *this;
	}
};

#endif