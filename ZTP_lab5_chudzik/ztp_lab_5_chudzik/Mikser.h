#pragma once
#include<string>
#include<iostream>

class Mikser {
private:

public:
	Mikser() {};
	Mikser(const char* filename) { open(filename); };
	~Mikser() {};
	void open(const char* filename);
};
//
//void open(const char* file) {
//
//}