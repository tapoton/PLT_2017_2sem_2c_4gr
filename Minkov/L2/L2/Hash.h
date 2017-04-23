#ifndef __HASH__
#define __HASH__

#include "stdafx.h"
#include "iostream"
#include "stdafx.h"
#include "string"

using namespace std;

static int HASHTABLE_SIZE = 1;

struct Node {
char* key; // слово
int quantity; // кол-во повторений этого слова в тексте
Node* next; // слово с тем же хэшем
};

class HashEl { // Хэш-таблица методом цепочек (по сути эл-т класса это односвязный список)
protected:
	Node* Head = NULL;

public:
	//Основные:
	HashEl() {}

	void Add(char* str) {
		Node* Add = new Node;
		Add->next = nullptr;
		Add->key = str;
		Add->quantity = 1;
		if (Head) {
			Node* Current = Head;
			while (Current->next && strcmp(Current->key, Add->key)) Current = Current->next;
			if (!strcmp(Current->key, Add->key)) Current->quantity++;
			else Current->next = Add;
		}
		else Head = Add;
	}

	void Show() {
		Node *Current = Head;
		while (Current) {
			cout << Current->key << ' ' << Current->quantity << ' ';
			Current = Current->next;
		}
		cout << endl;
	}

	int TwoOrMore() { // Считает в списке кол-во слов встречающихся в тексте 2 и более раза
		int q = 0;
		Node* Current = Head;
		while (Current) {
			if (Current->quantity >= 2) q++;
			Current = Current->next;
		}
		return q;
	}

	void Pop() {
		Node* t = Head;
		while (t->next->next) t = t->next;
		t->next = NULL;
	}

	void Cut() {
		Node* t = Head;
		Head = Head->next;
		t = NULL;
	}

	//Вспомогательные:
	char* getKey(Node* t) { return t->key; }
	void setValue(Node* t, char* s) { t->key = s; }
	Node* getNext(Node* t) { return t->next; }
	Node* getHead() { return Head; }
	Node* getTail() {
		Node* t = Head;
		while (t->next) t = t->next;
		return t;
	}
	int length() {
		int q = 0;
		Node* t = Head;
		while (t) {
			q++;
			t = t->next;
		}
		return q;
	}
};

int Hash(char* key) {
	cout << key << endl;
	char* c = key;
	int s = 0;
	while (*c) s += *(c++);
	s %= HASHTABLE_SIZE;
	cout << "Хэш слова " << key << ':' << s << endl;
	return s;
}

void MissionX(char** arr, int lim) {
	unsigned int i, j;
	for (i = 0; i < lim - 1; i++) {
		for (j = i + 1; j < lim; j++) cout << arr[i] << ' ' << arr[j] << endl;
		if (i < lim - 2) {
			cout << arr[i] << ' ';
			for (j = i + 1; j < lim; j++)
				cout << arr[j] << ' ';
			cout << endl;
		}
	}
	cout << endl;
}

#endif // !__HASH__
