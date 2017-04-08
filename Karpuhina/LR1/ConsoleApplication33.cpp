// ConsoleApplication33.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
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
	for (int i = 0; i < str.length(); i++) //ïîêà íå áóäåò äîáàâëåíî âñå ñëîâî
	{
		if (ptr->next[str[i] - 'a'] != NULL) //ïðîâåðêà, åñëè ëè óæå â ñëîâàðå òåêóùàÿ áóêâà
		{
			if (i == str.length() - 1) //åñëè äîñòèãíóòà ïîñëåäíÿÿ áóêâà, îòìå÷àåì, ÷òî ýòî ñëîâî
			{
				ptr->next[str[i] - 'a']->isWord = true;
			}
			else ptr = ptr->next[str[i] - 'a']; 
		}
		else //áóêâà íå íàéäåíà, äîáàâëÿåì
		{
			Node* newNode = new Node;
			if (i == str.length() - 1)  //åñëè äîñòèãíóòà ïîñëåäíÿÿ áóêâà, îòìå÷àåì, ÷òî ýòî ñëîâî
			{
				newNode->isWord = true;
			}
			else newNode->isWord = false;
			ptr->next[str[i] - 'a'] = newNode;
			ptr = ptr->next[str[i] - 'a']; 
		}
	}
}

void getLexicon(Node* tree, string prefix) //âûâîä âñåõ ñëîâ íà ýêðàí
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
	for (int i = 0; i < abSize; i++) //èäåì ïî âñåì ïîòîìêàì
	{
		if (tree->next[i] != NULL) //åñëè ïîòîìîê ñóùåñòâóåò,
		{
			if (tree->next[i]->isWord) //ïðîâåðÿåì, ÷òî ýòî ñëîâî, à íå ïðîìåæóòî÷íàÿ áóêâà
			{
				if (cons.find(char('a' + i)) != -1) //ïðîâåðêà, ÿâëÿåòñÿ ëè áóêâà ñîãëàñíîé
					consEndNum++;
			}
			SearchConsEnd(tree->next[i]); //è èäåì äàëüøå ïî äåðåâó
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Node* tree = new Node;
	//äîáàâëåíèå ñëîâ
	add(tree, "hello");
	add(tree, "hi");
	add(tree, "ann");
	add(tree, "anna");
	//âûâîä âñåõ ñëîâ íà ýêðàí
	cout << "Ñëîâà, íàõîäÿùèåñÿ â ëåêñèêîíå: " << endl;
	getLexicon(tree, "");
	//ïîèñê ñëîâ, îêàí÷èâàþùèõñÿ íà ñîãëàñíóþ
	SearchConsEnd(tree);
	cout << "×èñëî ñëîâ, îêàí÷èâàþùèõñÿ íà ñîãëàñíóþ: " << consEndNum << endl;
	return 0;
}




