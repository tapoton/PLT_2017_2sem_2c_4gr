// Задан текстовый файл. Сформировать набор словосочетаний по два и более слова, встречающихся в тексте не менее двух раз.

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "Hash.h"

using namespace std;

static const char* filename = "Input.txt";

void main()
{
	setlocale(0, "");
	ifstream fin;
	fin.open(filename);
	cout << "Считываем текст из Input.txt..\n";
	string strfin;
	int q = 0;

// Вычисление размера хэш-таблицы, для макс. коэф. заполненности = 90%
	while (getline(fin, strfin)) { 
		q++;
		HASHTABLE_SIZE = round(q / 0.90);
	}
	cout << "В тексте " << q << " слов(а). Оптимальный размер хэш-таблицы - " << HASHTABLE_SIZE << endl;
	fin.close();

// Заполнение Хэш-таблицы (реализована как массив односвязных списков)
	fin.open(filename);
	HashEl* HashTable = new HashEl[HASHTABLE_SIZE];
	unsigned int i = 0;

	while (getline(fin, strfin)) {
		char* word = new char[strfin.size() + 1];
		copy(strfin.begin(), strfin.end(), word);
		word[strfin.size()] = '\0';
		unsigned int index = Hash(word);
		cout << endl;
		HashTable[index].Add(word);
	}

	fin.close();

// Определение кол-ва повторяющихся слов (переменная twoormore) и вывод Хэш-таблицы
	int twoormore = 0;
	cout << "В памяти таблица располагается след. образом:\n";
	for (i = 0; i < HASHTABLE_SIZE; i++) {
		cout << "Индекс: " << i << ", содержимое: ";
		HashTable[i].Show(); 
		cout << endl; 
		twoormore += HashTable[i].TwoOrMore();
	}

// Формирование массива[twoormore] слов 
	char** SentenceX = new char*[twoormore];
	unsigned int j = 0;
	for (i = 0; i < HASHTABLE_SIZE; i++) {
		Node* tmp = HashTable[i].getHead();
		while (tmp) {
			if (tmp->quantity >= 2) {
				*(SentenceX + j) = tmp->key;
				j++;
			}
			tmp = tmp->next;
		}
	}

// Вывод словосочетаний
	cout << "Словосочетания повторяющихся слов:\n";
	MissionX(SentenceX, twoormore);
	system("pause");
}

