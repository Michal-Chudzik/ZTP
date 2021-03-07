/** INFO:
* Program sprawdza poprawnosc zapisanych w pliku wyrazen arytmetycznych
* reprezentuj¹cych wielomiany i zakodowanych wg notacji MathML.
* Przyjete zostalo, ze ka¿dy element wyrazenia zamkniêty w odpowiednich
* tagach jest zapisany w oddzielnej linijce pliku.
*/
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>

using namespace std;


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

int command(string& line, string& tmp, int n) {
	int licznik = line.find(">");
	if (licznik == string::npos)throw string("Brak nawiasu zamykajacego.");
	tmp = line.substr(n + 1, licznik - (n+1));
	return licznik;
}

void commandN(string& line, string& tmp, int n) {
	tmp = line.substr(n);
	int licznik = tmp.find(">");
	if (licznik == string::npos)throw string("Brak nawiasu zamykajacego.");
	tmp = tmp.substr(1, licznik-1);
}

void fun(fstream& file) {
	file.open("file.txt", ios::in);
	try {
		if (!file.is_open()) throw string("Blad otwarcia pliku");
		string stos[50];
		int stosCounter = 0;
		while (!file.eof()) {
			string line;
			getline(file, line);
			string tmp;
			if (line == "")continue;
			int endBracket = command(line, tmp, checkFirstBracket(line));
			if (tmp == "math xmlns=\"http://www.w3.org/1998/Math/MathML\""){
				stos[stosCounter] = tmp;
				stosCounter++;
			}
			else if (tmp == "mi" || tmp == "mo" || tmp == "mn") {
				stos[stosCounter] = tmp;
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
				if (tmp == stos[stosCounter]) {
					stos[stosCounter] = ' ';
				}
				else throw string("Blad tagow na stosie.");
			}
			else if (tmp == "msup" || tmp == "mrow"||tmp == "mfenced") {
				stos[stosCounter] = tmp;
				stosCounter++;
			}
			else if (tmp == "/mrow" || tmp == "/msup" || tmp == "/mfenced") {
				tmp = tmp.substr(1);
				stosCounter--;
				if (tmp == stos[stosCounter]) {
					stos[stosCounter] = ' ';
				}
				else throw string("Blad tagow na stosie");
				
			}
			else if (tmp == "/math") {
				stosCounter--;
				if (stos[stosCounter] == "math xmlns=\"http://www.w3.org/1998/Math/MathML\"") {
					stos[stosCounter] = ' ';
				}
				else throw string("Blad tagow na stosie");
			}
			else {
				throw string("Brak podanego tagu lub Bledny tag");
			}
		}
	}
	catch (string& exc) {
		cout << exc << endl;
	}
}

int main() {
	fstream file;
	fun(file);
}

