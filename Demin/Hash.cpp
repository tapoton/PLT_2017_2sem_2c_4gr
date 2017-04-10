#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

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
	{
		return num_of_nods;
	}
	Node* GetHead()
	{
		return head;
	}
	void DeleteList()
	{
		if(head)
		{
			Node* ptr = head, *oldptr = ptr;
			while (ptr->next)
			{
				oldptr = ptr;
				ptr = ptr->next;
			}
			if (ptr != head)
			{
				delete ptr;
				oldptr->next = NULL;
				num_of_nods--;
				DeleteList();			
			}
			else
			{
				num_of_nods--;
				delete head;
				head = NULL;
			}
		}
	}
};

class HashTable
{
	const int num_of_nods = 3;
	int num_of_lists;
	List *Table;
	int FindHash(string name)
	{
		int i = 0, sum = 0;
		while (name[i])
			sum += name[i++];
		return sum % num_of_lists;
	}
public:
	HashTable(int n)
	{
		num_of_lists = n;
		Table = new List[num_of_lists];
	}
	void operator=(HashTable SomeTable)
	{
		num_of_lists = SomeTable.num_of_lists;
		Table = SomeTable.Table;
	}
	void DeleteTable()
	{
		for (int i = 0; i < num_of_lists; i++)
			Table[i].DeleteList();
		num_of_lists = 0;
	}
	void Add(string add_name)
	{
		if (Table[FindHash(add_name)].GetNum() < num_of_nods)
			Table[FindHash(add_name)].Add(add_name);
		else
		{
			int new_num_of_lists = num_of_lists + 1;
			HashTable NewTable(new_num_of_lists);
			for (int i = 0; i < num_of_lists; i++)
			{
				Node* ptr = Table[i].GetHead();
				while (ptr)
				{
					NewTable.Add(ptr->name);
					ptr = ptr->next;
				}
			}
			DeleteTable();
			*this = NewTable;
			Add(add_name);
		}
	}
	void Print()
	{
		for (int i = 0; i < num_of_lists; i++)
		{
			cout << endl << '#' << i + 1 << ": ";
			Table[i].Print();
		}
	}
	void Delete(string del_name)
	{
		Table[FindHash(del_name)].Delete(del_name);
	}
	Node* Find(string find_name)
	{
		return Table[FindHash(find_name)].Find(find_name);
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
	cout << endl;
	Table.Print();
	cout << endl;
	Table.Delete("x");
	Table.Print();
	cout << endl; system("pause");
}