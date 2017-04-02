#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define Hash_size 52

struct Node
 {
	int count;
	string value;
	Node *next;
	}**hashtable;

unsigned int Index(string value)
 {
	int sum = 0;
	for (unsigned int i = 0; i < value.length(); i++)
		sum += value[i] ;
	return (sum % Hash_size);
	}
Node *Search(string value)
 {
	Node *p= hashtable[Index(value)];
	while (p && p->value != value)
		 p = p->next;
	return p;
	}
void Insert(string value)
 {
	if (value != "\0")
	{
		Node *search = Search(value);
		int index = Index(value);
		if (!search)
		{
			if (Node *current = new Node)
			{
				current->value = value;
				current->count = 1;
				current->next = hashtable[index];
				hashtable[index] = current;
			}
		}
		else
			search->count++;
	}
	}
void Print()
 {
	cout << "The resulting hash function:" << endl;
	int sum = 0;
	for (int i = 0; i < Hash_size; i++)
		 if (hashtable[i])
		 {
		Node *q;
		
			while (hashtable[i])
			 {
			q = hashtable[i];
			sum += q->count;
			cout << q->value << " = " << q->count << endl;
			hashtable[i] = hashtable[i]->next;
			}
		}
	cout << "The total amount: " << sum << endl;
	}
void Create()
{
	hashtable = new Node *[Hash_size];
	for (int i = 0; i < Hash_size; i++)
		hashtable[i] = NULL;
}
void Remove()
{
	for (int i = 0; i < Hash_size; i++)
		if (hashtable[i])
		{
			Node *q;
			while (hashtable[i])
			{
				q = hashtable[i];
				hashtable[i] = hashtable[i]->next;
				delete q;
				q = NULL;
			}
		}
	delete[] hashtable;
}

void main()
{
	char signs[] = "-=+/*,.;:'\"><(){}[]";
	int const n = 20; int  m = sizeof(signs) - 1;
	char c[n];
	Create();
	ifstream f("input.txt");
	if (!f)
		cerr << "Error opening file" << endl;
	while (f >> c)
	{
		if (c[0] >= '0'&&c[0] <= '9')
			c[0] = '\0';
		for (int i = 0; c[i]; i++)
			for (int j = 0; j < m; j++)
				if (c[i] == signs[j])
					c[i] = '\0';
		Insert(c);
	}

	Print();
	Remove();
	system("pause");
}
