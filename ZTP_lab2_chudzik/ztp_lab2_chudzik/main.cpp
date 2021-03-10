/** INFO:
* Program sprawdza poprawnosc zapisanych w pliku wyrazen arytmetycznych
* reprezentujacych wielomiany i zakodowanych wg notacji MathML.
* Przyjete zostalo, ze kazdy element wyrazenia zamkniety w odpowiednich
* tagach jest zapisany w oddzielnej linijce pliku.
*/
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>

using namespace std;

/// <summary>
/// Sprawdza nawias otwierajacy, jesli przed nim sa spacje to je pomija.
/// </summary>
/// <param name="line">Przekazanie calej linii.</param>
/// <returns>Indeks w ktorym znajduje sie nawias otwierajacy.</returns>
int checkFirstBracket(string& line) {
	int i = 0;
	while (line.at(i) == ' ') {							//pominiecie spacji w linii ktore znajduja sie przed nawiasem otwierajacym
		i++;
	}
	if (line.at(i) != '<') {
		throw string("Brak nawiasu otwierajacego.");		//throw do nawiasu otwierajacego
	}
	return i;
}

/// <summary>
/// Szuka nawiasu zamykajacego komende
/// </summary>
/// <param name="line">Cala linia z pliku.</param>
/// <param name="tmp">String pomocniczy.</param>
/// <param name="n">Indeks nawiasu otwierajacego.</param>
/// <returns>Indeks nawiasu zamykajacego.</returns>
int command(string& line, string& tmp, int n) {
	int licznik = line.find(">");
	if (licznik == string::npos)throw string("Brak nawiasu zamykajacego.");
	tmp = line.substr(n + 1, licznik - (n+1));
	return licznik;
}

/// <summary>
/// Szuka nawiasu zamykajacego komende konczaca blok
/// </summary>
/// <param name="line">Cala linia z pliku.</param>
/// <param name="tmp">String pomocniczy.</param>
/// <param name="n">Indeks '/'</param>
void commandN(string& line, string& tmp, int n) {
	tmp = line.substr(n);
	int licznik = tmp.find(">");
	if (licznik == string::npos)throw string("Brak nawiasu zamykajacego.");
	tmp = tmp.substr(1, licznik-1);
}

/// <summary>
/// Sprawdza poprawnosc tagow z pliku.
/// </summary>
/// <param name="file">Plik z tagami.</param>
void fun(fstream& file) {
	file.open("file.txt", ios::in);	// otworzenie pliku
	try {
		if (!file.is_open()) throw string("Blad otwarcia pliku");	// sprawdzenie czy plik zostal otwarty
		string stack[50];
		int stackCounter = 0;
		while (!file.eof()) {
			string line;
			getline(file, line);	// pobranie linii z pliku
			string tmp;
			if (line == "")continue;	// jesli w linii nic nie ma zostaje pominieta
			int endBracket = command(line, tmp, checkFirstBracket(line));	// wywolanie funkcji command
			if (tmp == "math xmlns=\"http://www.w3.org/1998/Math/MathML\""){	// sprawdzenie tagu otwierajacego plik
				stack[stackCounter] = tmp;	// wlozenie tagu na stos
				stackCounter++;	
			}
			else if (tmp == "mi" || tmp == "mo" || tmp == "mn") {	// sprawdzenie tagow mi, mo, mn
				stack[stackCounter] = tmp;	// wlozenie tagu na stos
				int check = line.find('/');														//sprawdzenie czy w linii jest tag negujacy
				if (check == string::npos)throw string("Brak elementu konczacego komende.");	//oraz jego pozycja
				if (tmp == "mn") {						
					bool containsNumber = false;
					while (endBracket-1 < check-2) {
						endBracket++;
						if (isdigit(line.at(endBracket))) containsNumber = true;
					}
					if (!containsNumber) throw string("Nie ma liczby, a powinna.");
				}
				else if (tmp == "mo") {
					endBracket++;
					if (line.at(endBracket) != '+' && line.at(endBracket) != '-' && line.at(endBracket) != '*' && line.at(endBracket) != '/')
						throw string("Nie ma operatora, a powinien byc"); 
				}
				commandN(line, tmp, check);								
				if (tmp == stack[stackCounter]) {
					stack[stackCounter] = ' ';	// zdjecie tagow ze stosu jesli spelnia warunek
				}
				else throw string("Blad tagow na stosie.");
			}
			else if (tmp == "msup" || tmp == "mrow"||tmp == "mfenced") {	// sprawdzenie tagow msup, mrow, mfenced
				stack[stackCounter] = tmp;	// wlozenie tagu na stos
				stackCounter++;
			}
			else if (tmp == "/msup" || tmp == "/mrow" || tmp == "/mfenced") {	// sprawdzenie tagow negujacych
				tmp = tmp.substr(1);	
				stackCounter--;	
				if (tmp == stack[stackCounter]) {
					stack[stackCounter] = ' ';	// zdjecie tagow ze stosu jesli spelnia warunek
				}
				else throw string("Blad tagow na stosie");
				
			}
			else if (tmp == "/math") {	// sprawdzenie tagu negujacego
				stackCounter--;
				if (stack[stackCounter] == "math xmlns=\"http://www.w3.org/1998/Math/MathML\"") {
					stack[stackCounter] = ' ';	// zdjecie tagow ze stosu jesli spelnia warunek
				}
				else throw string("Blad tagow na stosie");
			}
			else {
				throw string("Brak podanego tagu lub Bledny tag");
			}
		}
	}
	catch (string& exc) {
		cout << exc << endl;	// wypis wyrzuconego wyjatku
	}
}

int main() {
	fstream file;
	fun(file);
}

