// ConsoleApplication33.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include "stdafx.h"
using namespace std;

const int abSize = 25; 
const string cons = "bcdfghjklmnpqrstvwxz"; 
int consEndNum = 0;

struct Node 
{
	bool isWord = false;
	Node* next[abSize] ;
};

void add(Node* tree, string str) 
{
	Node* ptr = tree;
	for (int i = 0; i < str.length(); i++) //пока не будет добавлено все слово
	{
		if (ptr->next[str[i] - 'a'] != NULL) //проверка, если ли уже в словаре текущая буква
		{
			if (i == str.length() - 1) //если достигнута последняя буква, отмечаем, что это слово
			{
				ptr->next[str[i] - 'a']->isWord = true;
			}
			else ptr = ptr->next[str[i] - 'a']; 
		}
		else //буква не найдена, добавляем
		{
			Node* newNode = new Node;
			if (i == str.length() - 1)  //если достигнута последняя буква, отмечаем, что это слово
			{
				newNode->isWord = true;
			}
			else newNode->isWord = false;
			ptr->next[str[i] - 'a'] = newNode;
			ptr = ptr->next[str[i] - 'a']; 
		}
	}
}

void getLexicon(Node* tree, string prefix) //вывод всех слов на экран
{
	for (int i = 0; i < abSize; i++)
	{
		if (tree->next[i] != NULL)
		{
			if (tree->next[i]->isWord)
			{
				cout << prefix << char('a' + i) << endl;
			}
			string str = prefix;
			str.append(1, char('a' + i));
			getLexicon(tree->next[i], str);
		}
	}
}

void SearchConsEnd(Node* tree) 
{
	for (int i = 0; i < abSize; i++) //идем по всем потомкам
	{
		if (tree->next[i] != NULL) //если потомок существует,
		{
			if (tree->next[i]->isWord) //проверяем, что это слово, а не промежуточная буква
			{
				if (cons.find(char('a' + i)) != -1) //проверка, является ли буква согласной
					consEndNum++;
			}
			SearchConsEnd(tree->next[i]); //и идем дальше по дереву
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Node* tree = new Node;
	//добавление слов
	add(tree, "hello");
	add(tree, "hi");
	add(tree, "ann");
	add(tree, "anna");
	//вывод всех слов на экран
	cout << "Слова, находящиеся в лексиконе: " << endl;
	getLexicon(tree, "");
	//поиск слов, оканчивающихся на согласную
	SearchConsEnd(tree);
	cout << "Число слов, оканчивающихся на согласную: " << consEndNum << endl;
	return 0;
}




