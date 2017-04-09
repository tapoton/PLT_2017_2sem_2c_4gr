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
};
class List
{
	Node **head;
public:
	unsigned int Index(string value)
	{
		int sum = 0;
		for (unsigned int i = 0; i < value.length(); i++)
			sum += value[i];
		return (sum % Hash_size);
	}
	Node *Search(string value)
	{
		Node *p = head[Index(value)];
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
					current->next = head[index];
					head[index] = current;
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
			if (head[i])
			{
				Node *q;

				while (head[i])
				{
					q = head[i];
					sum += q->count;
					cout << q->value << " = " << q->count << endl;
					head[i] = head[i]->next;
				}
			}
		cout << "The total amount: " << sum << endl;
	}
	List()
	{
		head = new Node *[Hash_size];
		for (int i = 0; i < Hash_size; i++)
			head[i] = NULL;
	}
	~List()
	{
		for (int i = 0; i < Hash_size; i++)
			if (head[i])
			{
				Node *q;
				while (head[i])
				{
					q = head[i];
					head[i] = head[i]->next;
					delete q;
					q = NULL;
				}
			}
		delete[] head;
	}
};

void main()
{
	List list;
	char signs[] = "-=+/*,.;:'\"><(){}[]";
	int const n = 20; int  m = sizeof(signs) - 1;
	char c[n];
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
		list.Insert(c);
	}

	list.Print();
	system("pause");
}
