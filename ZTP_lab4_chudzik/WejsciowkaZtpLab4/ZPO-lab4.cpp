/** INFO:
* Program jest przykladem programowania
* z wykorzystaniem cech charakterystycznych
*/
#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<exception>
#include<iomanip>

using namespace std;

class Bazowe_Cechy {
public:
	static const bool _jest_liczba = false;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const int _dolna_granica_przedzialu = 0;
	static const int _gorna_granica_przedzialu = 0;
	static const int _precision = 0;
	static const bool _musi_miec_polowke = false;
};

template<typename T>
class Cechy : public Bazowe_Cechy {
public:
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 0; };
};

class temperatura_wody {
	double t;
public:
	temperatura_wody(double temp = 50) : t(temp) {};
	double operator()() { return t; };
	temperatura_wody& operator=(double temp) { t = temp; return *this; };
};

template<>
class Cechy<temperatura_wody> : public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _wymaga_specjalny_przedzial = false;
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 100; };
	static const int _precision = 1;
};

class kostka_do_gry {
	int n;
public:
	kostka_do_gry(int num = 1) : n(num) {};
	int operator()() { return n; };
	kostka_do_gry& operator=(int num) { n = num; return *this; };

	friend ostream& operator<<(ostream& os, const kostka_do_gry& d) {
		return os << "wypis kostki do gry: " << fixed <<setprecision(0) << d.n;
	}
};

template<>
class Cechy<kostka_do_gry> : public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const bool _jest_potega_dwojki = false;
	static const bool _wymaga_specjalny_przedzial = false;

	static const int _dolna_granica_przedzialu = 1;
	static const int _gorna_granica_przedzialu = 6;
};

class rozmiar_felgi {
	int n;
public:
	rozmiar_felgi(int num = 10) :n(num) {
		if (num < 10 || 24 < num) { n = 10; }
	}
	int operator()() { return n; }
	rozmiar_felgi& operator=(int num) { n = num; return *this; }
	friend ostream& operator<<(ostream& os, const rozmiar_felgi& d) {
		return os << "Wartosci stosu rozmiaru felgi: " << fixed <<setprecision(0)<< d.n;
	}
};

template<>
class Cechy<rozmiar_felgi> :public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const bool _jest_potega_dwojki = false;
	static const bool _wymaga_specjalny_przedzial = false;
	static const int _dolna_granica_przedzialu = 10;
	static const int _gorna_granica_przedzialu = 24;
};

class czestotliwosc_radiofonii {
	double n;
public:
	czestotliwosc_radiofonii(string num = "88.0"){
		int dotPos = num.find('.');
		int len = num.length();
		if ((len - 1) - dotPos > 2) {
			n = 90.0;
		}
		else {
			double number = stod(num);
			if (number < 87.5 || number > 108) { n = 90.0; }
			else n = number;
		}
	}
	double operator()() { return n; }
	czestotliwosc_radiofonii& operator=(double num) { n = num; return *this; }
	friend ostream& operator<<(ostream& os, const czestotliwosc_radiofonii& d);
};

template<>
class Cechy<czestotliwosc_radiofonii> :public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = false;
	static const bool _wymaga_specjalny_przedzial = false;
	static const double dolna_granica_przedzialu() { return 87.50; }
	static const double gorna_granica_przedzialu() { return 108; }
	static const int _precision = 2;
};

ostream& operator<<(ostream& os, const czestotliwosc_radiofonii& d) {
	return os << "Wartosc stosu czestotliwosci radiofonii: " << fixed << setprecision(2) << d.n;
}


class rozmiar_buta {
	double n;
public:
	rozmiar_buta(double num = 30) :n(num) {
		if (fmod(num, 0.5) != 0 || num < 14 || num > 49) { n = 24.5; }
	}
	double operator()() { return n; }
	rozmiar_buta& operator= (double num) { n = num; return *this; }
	friend ostream& operator<<(ostream& os, const rozmiar_buta& d) {
		return os << "Wartosc stosu rozmiaru buta: " << fixed << setprecision(1) << d.n;
	}
};

template<>
class Cechy<rozmiar_buta> :public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = 0;
	static const bool _wymaga_specjalny_przedzial = true;
	static const bool _musi_miec_polowke = true;
	static const double dolna_granica_przedzialu() { return 14; }
	static const double gorna_granica_przedzialu() { return 49; }
	static const int _precision = 1;
};

class pojemnosc_karty {
	int n;
public:
	pojemnosc_karty(int num = 2) :n(num) {
		double tmp = log2(num);
		if (tmp-(int)tmp!=0||num < 0 || num > 128) { n = 2; }
	}
	int operator()() { return n; }
	pojemnosc_karty& operator=(int num) { n = num; return *this; }
	friend ostream& operator<<(ostream& os,const pojemnosc_karty& d) {
		return os << "Wartosc stosu pojemnosci karty: " << fixed << setprecision(1) << d.n;
	}
};

template<>
class Cechy<pojemnosc_karty> :public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const bool _jest_potega_dwojki = true;			
	static const bool _wymaga_specjalny_przedzial = true;
	static const int _dolna_granica_przedzialu = 2;
	static const int _gorna_granica_przedzialu = 128;
	static const int _precision = 0;
};

class Przepelnienie : public exception {
	char opis[100];
public:
	Przepelnienie(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};

class BrakDanych : public exception {
	char opis[100];
public:
	BrakDanych(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};


template<typename T, int rozmiar, class _Cechy = Cechy<T>>
class SzablonStosu{
	T stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	SzablonStosu() : top(0) {}
	void push(const T& i) {	// metoda push dla obiektu T							
		if (top == rozmiar)	// warunek sprawdzajacy czy iterator jest rowny rozmiarowi kontera						
			throw Przepelnienie(typeid(i).name());	// throw zwracajacy typ danych kontenera z ktorego korzystamy
		stos[top++] = i;							
	}
	void push(int i) {		//metoda push dla wartosci int
		if (top == rozmiar)	// warunek sprawdzajacy czy iterator jest rowny rozmiarowi kontera
			throw Przepelnienie(typeid(i).name()); // throw zwracajacy typ danych kontenera z ktorego korzystamy

		// walidacja wartoœci przekazanej do zapisu  
		if (Cechy<T>::_jest_liczba && Cechy<T>::_jest_liczba_calkowita) {
			if (Cechy<T>::_nalezy_do_przedzialu) {
				if ((Cechy<T>::_dolna_granica_przedzialu <= i) && (i <= Cechy<T>::_gorna_granica_przedzialu)) {
					double tmp1 = log2(i);
					if (Cechy<T>::_jest_potega_dwojki && tmp1 - (int)tmp1 == 0 || !Cechy<T>::_wymaga_specjalny_przedzial) {
						stos[top++] = i;
					}
				}
			}
			else
				stos[top++] = i;
		}
	}
	void push(double i) {   // metoda push dla wartosci double
		if (top == rozmiar) // warunek sprawdzajacy czy iterator jest rowny rozmiarowi kontera
			throw Przepelnienie(typeid(i).name());			// konstruktor klasy Przepelnienie z argumentem zwracajacym typ danych dla i

		// walidacja wartoœci przekazanej do zapisu
		if (Cechy<T>::_jest_liczba && !Cechy<T>::_jest_liczba_calkowita) {
			if (Cechy<T>::_nalezy_do_przedzialu) {
				if ((Cechy<T>::dolna_granica_przedzialu() <= i) && (i <= Cechy<T>::gorna_granica_przedzialu())) {
					if (Cechy<T>::_musi_miec_polowke && fmod(i, 0.5) == 0 || !Cechy<T>::_wymaga_specjalny_przedzial) {
						stos[top++] = i;
					}
				}
			}
			else stos[top++] = i;
		}
	}
	T pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());
		return stos[--top];
	}
};


int main() {
	SzablonStosu<string, 5> K1;
	SzablonStosu<temperatura_wody, 10> K2;
	SzablonStosu<kostka_do_gry, 10> K3;
	SzablonStosu<rozmiar_felgi, 5> K4;
	SzablonStosu<czestotliwosc_radiofonii, 6> K5;
	SzablonStosu<rozmiar_buta, 5> K6;
	SzablonStosu<pojemnosc_karty, 5> K7;

	// zape³nianie stosu
	ifstream fi("qv-lab4.txt");
	string s;
	try{
		K1.push("Henryk");
		K1.push("Sienkiewicz");

		// petla konczy sie w momencie wyrzucenia wyjatku przepelnienia stosu ktory znajduje sie w metodzie push
		while (fi) {
			fi >> s;					//wpisanie pliku do string s
			K1.push(s);					//wpisanie zawartosci s do kontera K1(szablon dla string)
			fi.seekg(ios::beg);			//przestawienie wskaznika na poczatek pliku
			fi.clear();					//wyczysczenie flag pliku
			cout << '*';				//gwiazdka ladowania
		};
	}
	catch (Przepelnienie& e){
		cout << "K1 gotowy: " << e.what() << endl;		//wypis typu danych
	};
	cout << "Danych na stosie K1: " << K1.zajetosc() << endl;	//wypis zmiennej TOP czyli ilosci danych znajdujacych sie na stosie
	
	/**
	*	przypisanie wartosci do kontenera temperatura wody
	*	wartosci sa sprawdzane w metodzie push czy
	*	sa poprawne dla danego typu danych, jesli
	*	nie sa wartosci zostaja pominiete
	*	wypis zmiennej TOP czyli ilosci danych znajdujacych sie na stosie
	*/
	K2.push(temperatura_wody());								
	K2.push(temperatura_wody(36.6));							
	K2.push(40.0);												
	K2.push(71.2);												
	cout << "Danych na stosie K2: " << K2.zajetosc() << endl;	

	K3.push(kostka_do_gry(3));									
	K3.push(kostka_do_gry());									
	K3.push(4);														
	K3.push(6);													
	K3.push(10);												
	cout << "Danych na stosie K3: " << K3.zajetosc() << endl;	

	K4.push(rozmiar_felgi());
	K4.push(rozmiar_felgi(26));
	K4.push(12);
	K4.push(21);
	K4.push(18);
	cout << "Danych na stosie K4: " << K4.zajetosc() << endl;

	K5.push(czestotliwosc_radiofonii("109.0"));
	K5.push(czestotliwosc_radiofonii("88.21"));
	K5.push(czestotliwosc_radiofonii("89.255"));
	K5.push(88.21);
	K5.push(102.56);
	K5.push(89.5);
	cout << "Danych na stosie K5: " << K5.zajetosc() << endl;

	K6.push(rozmiar_buta(4));
	K6.push(rozmiar_buta());
	K6.push(29.0);
	K6.push(60.0);
	K6.push(28.0);
	cout << "Danych na stosie K6: " << K6.zajetosc() << endl;

	K7.push(pojemnosc_karty(128));
	K7.push(pojemnosc_karty());
	K7.push(21);
	K7.push(64);
	K7.push(32);
	cout << "Danych na stosie K7: " << K7.zajetosc() << endl;


	// opró¿nianie stosu
	try{
		while (true)
			K1.pop();
	}
	catch (BrakDanych& e) {
		cout << endl << "K1 pusty: " << e.what() << endl<<endl;
	}
	try{
		while (true)
			 K2.pop();
	}
	catch (BrakDanych& e) {
		cout << "K2 pusty: " << e.what() << endl;
	}
	try{
		while (true) 
			cout << K3.pop() << endl;
	}
	catch (BrakDanych& e) {
		cout << "K3 pusty: " << e.what() << endl << endl;
	}
	try {
		while (true)
			cout << K4.pop() <<endl;
	}
	catch (BrakDanych& e) {
		cout << "K4 pusty: " << e.what() << endl << endl;
	}
	try {
		while (true) 
			cout << K5.pop() << endl;
	}
	catch (BrakDanych& e) {
		cout << "K5 pusty: " << e.what() << endl << endl;
	}
	try {
		while (true) 
			cout<<K6.pop()<<endl;
	}
	catch (BrakDanych& e) {
		cout << "K6 pusty: " << e.what() << endl << endl;
	}
	try {
		while (true)
			cout << K7.pop()<<endl;
	}
	catch (BrakDanych& e) {
		cout << "K7 pusty: " << e.what() << endl << endl;
	}

	system("pause");
	return 0;
}