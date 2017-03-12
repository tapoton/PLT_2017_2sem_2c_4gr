#include "stdafx.h"
#include "iostream"
#include "trie.h"
#include "string"

using namespace std;

//Вспомогательные ф-ции:

void Trie::init(node* Node) { //Нужна для уменьшения объёма кода
	Node->end = false;
	Node->parent = false;
	Node->length = 0;
	Node->vowQuant = 0;
	for (unsigned int i = 0; i < aLength; Node->child[i++] = nullptr);
}

Trie::Trie() { //Конструктор
	Head = new node;
	Head->key = ' ';
	Head->end = false;
	Head->parent = false;
	Head->length = 0;
	Head->vowQuant = 0;
	for (unsigned int i = 0; i < aLength; Head->child[i++] = nullptr);
}

bool isVowel(char c) { //Проверяет букву на гласность
	if ((c == 'a') || (c == 'A')) return true;
	if ((c == 'e') || (c == 'E')) return true;
	if ((c == 'i') || (c == 'I')) return true;
	if ((c == 'o') || (c == 'O')) return true;
	if ((c == 'u') || (c == 'U')) return true;
	if ((c == 'y') || (c == 'Y')) return true;
	else return false;
}

 int Trie::countCons(node* Node) { //Считает кол-во согласных, имеет смысл только для концевого эл-та
	return (Node->length) - (Node->vowQuant);
}

/////////////

//Основные ф-ции:

void Trie::push(char* word) { //Добавляет слово
	node* Current = Head;
	int letter;

	while (*word) { //Пока буквы не закончились распределяет их по дереву
		letter = (int)(*word) - (int)a; //Однозначная связь между буквой и её индексом в списке потомков
		if (Current->child[letter] == nullptr) { //если там ничего не лежало
			Current->child[letter] = new node;
			init(Current->child[letter]);
			Current->parent = true;
		}

		//Заполнение данных необходимых для missionX
		Current->child[letter]->key = *word;
		Current->child[letter]->length = Current->length + 1;
		Current->child[letter]->vowQuant = Current->vowQuant;
		if (isVowel(Current->child[letter]->key)) Current->child[letter]->vowQuant++;
		Current = Current->child[letter];
		word++;
	}

	Current->end = true;
}

int Trie::missionX(int cq, node* Node) { //Считает кол-во слов с опр. числом согласных, рекурсивная
	node* Current = Node;
	int X = 0;
	if ((Current->parent == false)) { //Если у текущего эл-та нет детей, или он хотя бы концевой,
		if (countCons(Current) == cq) X++;
	} //то проверяем удовлетворяет ли его слово условию.
	else {
		if ((Current->end) && (countCons(Current) == cq)) X++;
		for (unsigned int i = 0; i < aLength; i++)
			if (Current->child[i] != nullptr)
				X += missionX(cq, Current->child[i]); //Иначе идём по его потомкам
	}
	return X;
}

void Trie::print(char* indent, bool last, node* root) //Вывод дерева. Честно украдено, криво имплементировано.
{
	cout << indent;

	if (last)
	{
		cout << "+-";
		//*indent += " ";
	}
	else
	{
		std::cout << "|- ";
		//indent += "| ";
	}

	std::cout << root->key << std::endl;

	for (unsigned int i = 0; i< aLength; i++)
		if (root->child[i] != nullptr)
			print(indent, root->child[i]->end, root->child[i]);
};

/////////////