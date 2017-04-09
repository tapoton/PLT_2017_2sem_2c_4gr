#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
const int n = 13;

struct Node
{
	string name;
	Node* next;
};

class List
{
	
		Node* head;
	public:
		List() : head(NULL)
		{}
		void Add(string add_name)
		{
			Node* newnode = new Node;
			newnode->name = add_name;
			newnode->next = NULL;
			if (!head)
				head = newnode;
			else
			{
				Node* ptr = head;
				while (ptr->name != add_name && ptr->next)
					ptr = ptr->next;
				if (ptr->name == add_name)
				{
					cout << "\nќшибка, элемент с таим именем уже существует";
					delete newnode;
					return;
				}
				else
					ptr->next = newnode;
			}
		}
		void Delete(string del_name)
		{
			if (head && head->name == del_name)
			{
				Node* ptr = head;
				head = head->next;
				delete ptr;
			}
			else
			{
				Node* ptr = head, *oldptr = head;
				while (ptr && ptr->name != del_name)
				{
					oldptr = ptr;
					ptr = ptr->next;
				}
				if (!ptr) cout << "\nЁлемента с таким именем нет";
				else
				{
					oldptr->next = ptr->next;
					delete ptr;
				}
			}
		}
		Node* Find(string find_name)
		{
			Node* ptr = head;
			while (ptr && ptr->name != find_name)
				ptr = ptr->next;
			if (!ptr) cout << "\nЁлемента с таким именем не найдено";
			return ptr;
		}
		void Print()
		{
			if (!head) cout << "—писок пуст";
			else
			{
				Node* ptr = head;
				while (ptr)
				{
					cout << ptr->name;
					if (ptr->next) cout << " -> ";
					ptr = ptr->next;
				}
			}
		}
};

int FindHash(string name)
{
	int i = 0, sum = 0;
	while (name[i])
		sum += name[i++];
	return sum % 13;
}

class HashTable
{
	List Table[n];
	public:
		void Add(string add_name)
		{
			Table[FindHash(add_name)].Add(add_name);
		}
		void Delete(string del_name)
		{
			Table[FindHash(del_name)].Delete(del_name);
		}
		Node* Find(string find_name)
		{
			return Table[FindHash(find_name)].Find(find_name);
		}
		void Print()
		{
			for (int i = 0; i < n; i++)
			{
				cout<<endl<<'є'<<i+1<<": ";
				Table[i].Print();
			}
		}
};



void main()
{
	setlocale(LC_ALL, "rus");
	HashTable Table;
	Table.Add("0");
	Table.Add("1");
	Table.Add("2");
	Table.Add("3");
	Table.Add("4");
	Table.Add("5");
	Table.Add("6");
	Table.Add("7");
	Table.Add("8");
	Table.Add("9");
	Table.Add("10");
	Table.Add("11");
	Table.Add("12");
	Table.Add("13");
	Table.Add("14");
	Table.Add("15");
	cout << endl;
	Table.Delete("0"); Table.Delete("word");
	cout << endl << endl;
	Table.Print();
	cout << endl;
	cout << endl; system("pause");
}

