/** INFO:
* Program checks correctness of saved in file arithmetic expressions 
* representing polynomial and coded in MathML.
* It was accepted, that every tag closed in correct tags needs to 
* be in saperate line in file.
* 
* 
* 
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
/// Checks opening tag, if there are spaces before it, they are skipped
/// </summary>
/// <param name="line">Full line from file</param>
/// <returns>Index of a opening tag</returns>
int checkFirstBracket(string& line) {
	int i = 0;
	while (line.at(i) == ' ') {							//skipping spaces before opening tag
		i++;
	}
	if (line.at(i) != '<') {
		throw string("Brak nawiasu otwierajacego.");		//throw to opening tag
	}
	return i;
}

/// <summary>
/// Searching for closing tag in line
/// </summary>
/// <param name="line">Full line from file</param>
/// <param name="tmp">Tmp string</param>
/// <param name="n">Opening tag index</param>
/// <returns>Closing tag index</returns>
int command(string& line, string& tmp, int n) {
	int licznik = line.find(">");
	if (licznik == string::npos)throw string("Brak nawiasu zamykajacego.");
	tmp = line.substr(n + 1, licznik - (n+1));
	return licznik;
}

/// <summary>
/// Searching for closing tag of ending block command
/// </summary>
/// <param name="line">Full line from file</param>
/// <param name="tmp">Tmp string</param>
/// <param name="n">Index '/'</param>
void commandN(string& line, string& tmp, int n) {
	tmp = line.substr(n);
	int licznik = tmp.find(">");
	if (licznik == string::npos)throw string("Brak nawiasu zamykajacego.");
	tmp = tmp.substr(1, licznik-1);
}

/// <summary>
/// Checks corectness of tags in file
/// </summary>
/// <param name="file">File with tags</param>
void fun(fstream& file) {
	file.open("file.txt", ios::in);	// opening file
	try {
		if (!file.is_open()) throw string("Blad otwarcia pliku");	// checking if file was opened
		string stack[50];
		int stackCounter = 0;
		while (!file.eof()) {
			string line;
			getline(file, line);	// getting line from file
			string tmp;
			if (line == "")continue;	// If line is empty it is skipped
			int endBracket = command(line, tmp, checkFirstBracket(line));	// calling function command
			if (tmp == "math xmlns=\"http://www.w3.org/1998/Math/MathML\""){	// checking first tag in file
				stack[stackCounter] = tmp;	// putting tag on stack
				stackCounter++;	
			}
			else if (tmp == "mi" || tmp == "mo" || tmp == "mn") {	// checking mi, mo, mn tags
				stack[stackCounter] = tmp;	// putting tag on stack
				int check = line.find('/');														//	checking if in line is ending tag
				if (check == string::npos)throw string("Brak elementu konczacego komende.");	//	and it's possition
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
					stack[stackCounter] = ' ';	// taking off tag from stack if the condition is true
				}
				else throw string("Blad tagow na stosie.");
			}
			else if (tmp == "msup" || tmp == "mrow"||tmp == "mfenced") {	// checking msup, mrow, mfenced tags
				stack[stackCounter] = tmp;	// putting tag on stack
				stackCounter++;
			}
			else if (tmp == "/msup" || tmp == "/mrow" || tmp == "/mfenced") {	// checking ending tags
				tmp = tmp.substr(1);	
				stackCounter--;	
				if (tmp == stack[stackCounter]) {
					stack[stackCounter] = ' ';	// taking off tag from stack if the condition is true
				}
				else throw string("Blad tagow na stosie");
				
			}
			else if (tmp == "/math") {	// checking ending tag
				stackCounter--;
				if (stack[stackCounter] == "math xmlns=\"http://www.w3.org/1998/Math/MathML\"") {
					stack[stackCounter] = ' ';	// taking off tag from stack if the condition is true
				}
				else throw string("Blad tagow na stosie");
			}
			else {
				throw string("Brak podanego tagu lub Bledny tag");
			}
		}
	}
	catch (string& exc) {
		cout << exc << endl;	// print of a thrown exception
	}
}

int main() {
	fstream file;
	fun(file);
}

