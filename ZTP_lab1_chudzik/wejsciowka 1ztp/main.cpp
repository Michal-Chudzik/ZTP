#define _CRT_SECURE_NO_WARNINGS

/** INFO:
* Program sumuje podane temperatury i pojemnosci z podanych
* pojemnikow, pomiary i wyniki zapisuje do pliku za pomoca przeciazonego
* operatora wypisu.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

#include <windows.h>
#include <lmcons.h>
#include "wyklad13b.h"

using namespace std;

void raport(Tablica<Dane, 6> &arr, string fileN, string mode) {
	system("CLS");
	if (mode != "out") {
		cout << "Bledny tryb otwarcia.";
		exit(1);
	}
	fstream file;
	file.open(fileN, ios::out);	// otworzenie pliku

	// pobranie i wpisanie do pliku czasu lokalnego
	time_t t; 
	struct tm *tt;
	time(&t); 
	tt = localtime(&t);
	file << right << setw(34) << asctime(tt) <<"\n\n";

	// pobranie i wpisanie do pliku nazwy urzadzenia
	TCHAR computername[UNCLEN + 1];
	DWORD computername_len = UNCLEN + 1;
	GetComputerName((TCHAR*)computername, &computername_len);
	file << computername;
	
	//wypisanie danych do pliku
	file << "\n+------+----------+-------+------+\n";
	file << "|  ID  |  nazwa   | temp. |pojemn|\n";
	file << "+------+----------+-------+------+\n";
	for (int i = 0; i < 6; i++){
		file << arr[i];	// wypis do pliku za pomoca przeciazonego operatora
	}
	file << "+------+----------+-------+------+\n";
	// wypis do pliku sumy danych
	Dane Tmp(0,0,0," ");
	for (int i = 0; i < 6; i++){
		Tmp += arr[i];
	}
	file << Tmp;
	file << "+------+----------+-------+------+\n";
}


int main() {
	Tablica<Dane, 6> Darr;

	// inicjalizacja danych
	Dane D1(1, 100.0, 21.34, "nazwa 1");
	Dane D2(2, 300.0, 1.3, "nazwa 2");
	Dane D3(3, 250.0, 11.4, "nazwa 3");
	Dane D4(4, 800.0, 15.6, "nazwa 4");
	Dane D5(5, 10.0, 34.3, "nazwa 5");
	Dane D6(6, 23.0, 28.3, "nazwa 6");
	// uzupelnienie tablicy danymi
	Darr[0] = D1;
	Darr[1] = D2;
	Darr[2] = D3;
	Darr[3] = D4;
	Darr[4] = D5;
	Darr[5] = D6;
	string filename;
	cout << "podaj nazwe pliku: ";
	cin >> filename;
	filename += ".txt";
	raport(Darr, filename, "out");
	return 0;
}