#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
int num_of_lists = 13;
const int m = 5;

struct Node
{
	string name;
	Node* next;
};

class List
{
	int num_of_nods;
	Node* head;
public:
	List() : head(NULL), num_of_nods(0)
	{}
	void Add(string add_name)
	{
		Node* newnode = new Node;
		newnode->name = add_name;
		newnode->next = NULL;
		if (!head)
		{
			head = newnode;
			num_of_nods++;
		}
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
			{
				ptr->next = newnode;
				num_of_nods++;
			}
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
	int& GetNum()
	{return num_of_nods;}
	Node* GetHead()
	{return head;}
};

int FindHash(string name, int n)
{
	int i = 0, sum = 0;
	while (name[i])
		sum += name[i++];
	return sum % n;
}

class HashTable
{
	const int num_of_nods=5;
	int num_of_lists;
	List *Table;
public:
	HashTable(int n)
	{
		num_of_lists = n;
		Table = new List[num_of_lists];
	}
	void Add(string add_name)
	{
		if (Table[FindHash(add_name, num_of_lists)].GetNum() < num_of_nods)
		{
			Table[FindHash(add_name, num_of_lists)].GetNum()++;
			Table[FindHash(add_name, num_of_lists)].Add(add_name);
		}
		else
		{
			int new_num_of_lists = num_of_lists+1;
			HashTable NewTable(new_num_of_lists);
			for (int i = 0; i < num_of_lists;i++)
			{
				Node* ptr = Table[i].GetHead();
				while (ptr)
				{
					NewTable.Add(ptr->name);
					ptr=ptr->next;
				}
			}

			Table = NewTable.Table;
			num_of_lists = new_num_of_lists;
			Add(add_name);
		}
	}	
	void Print()
	{
		for (int i = 0; i < num_of_lists; i++)
		{
			cout << endl << 'є' << i + 1 << ": ";
			Table[i].Print();
		}
	}
	void Delete(string del_name)
	{
		Table[FindHash(del_name, num_of_lists)].Delete(del_name);
	}
	Node* Find(string find_name)
	{
		return Table[FindHash(find_name, num_of_lists)].Find(find_name);
	}
};



void main()
{
	setlocale(LC_ALL, "rus");
	HashTable Table(3);
	Table.Add("l");
	Table.Add("o");
	Table.Add("r");
	Table.Print();
	Table.Add("u");
	Table.Add("x");
	cout<<endl;
	Table.Print();
	cout<<endl;
	Table.Delete("x");
	Table.Print();
	cout<<endl; system("pause");
}

