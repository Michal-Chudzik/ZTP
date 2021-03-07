#pragma once
#include <cassert>

using namespace std;

template<typename T>
class ListItem{
public:
	T value;
	ListItem(T el) : prev(nullptr), next(nullptr), value(el) {}
	ListItem<T>* prev;
	ListItem<T>* next;
};

template<typename T>
class List{
public:
	ListItem<T>* head = nullptr;
	ListItem<T>* tail = nullptr;
	int top = 0;
	void push(T el) {
		top++;
		ListItem<T>* newEl = new ListItem<T>(el);
		if (head == nullptr) {
			head = tail = newEl;
		}
		else {
			tail->next = newEl;
			newEl->prev = tail;
			tail = newEl;
		}
		newEl->next = nullptr;
	}
	T pop() {
		top--;
		if (tail != nullptr) {
			ListItem<T>* temp = tail;
			tail = tail->prev;
			delete temp;
		}
	}

};


template<typename T>
class Konten
{
	List<T> lista;

public:

	void push(T i) {
		lista.push(i);
	};
	T pop() {
		return lista.pop();
	};
	int rozmiar() { return lista.top; };

	class iterator {
		Konten& s;
		ListItem<T>* wsk;
		int licznik;
	public:
		iterator(Konten& is) : s(is), licznik(0) { wsk = s.lista.head; };
		iterator(Konten& is, bool) : s(is), licznik(s.lista.top) { wsk = s.lista.tail; }
		T operator++() { // Prefix
			if (licznik++ <= s.lista.top) {
				wsk = wsk->next;
				return wsk->value;
			}
		};
		T operator++(int) { // Postfix
			if (licznik++ <= s.lista.top) {
				T val = wsk->value;
				wsk = wsk->next;
				return val;
			}
		};
		T& operator*() const { return wsk->value; };
		iterator& operator=(const iterator& rv) {
			s = rv.s;
			licznik = rv.licznik;
			return *this;
		}
		bool operator!=(const iterator rv)const {
			return licznik != rv.licznik;
		}
		iterator set_front() {
			wsk = s.lista.head;
			licznik = 0;
			return *this;
		}
	};
	iterator begin() { return iterator(*this); };
	iterator end() { return iterator(*this, true); };

	friend class iterator;
};