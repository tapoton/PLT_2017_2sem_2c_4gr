#include <iostream>
#include <string>

using namespace std;

const int hash_size = 10;

class hashTable
{

	struct Node
	{
		int tabel;
		int money;
		string name;
		string surname;
		string otch;
		Node* next;
	};

	Node* worker[hash_size];

	void createNode(Node* current, int tabel, int money, string surname, string name, string otch)
	{
		current->tabel = tabel;
		current->name = name;
		current->surname = surname;
		current->otch = otch;
		current->money = money;
		current->next = NULL;
	}

	int hash(int key)
	{

		return key % hash_size;
	}

	Node* search1(int tabel)
	{
		int hash_num = hash(tabel);
		Node* result = new Node;
		result = worker[hash_num];
		if (result)
		{

			while ((result->tabel != tabel) && (result->next != NULL))
			{
				result = result->next;
			}
			if (result->next == NULL && result->tabel != tabel)
			{
				return NULL;
			}
			else
			{
				return result;

			}
		}
		else
		{
			return NULL;
		}


	}




public:

	hashTable()
	{
		for (int i = 0; i < hash_size; i++)
		{
			worker[i] = NULL;
		}
	}

	void insertNode(int tabel, int money, string surname, string name, string otch)
	{
		Node* pv;
		pv = search1(tabel);
		if (pv)
		{
			createNode(pv, tabel, money, surname, name, otch);
		}
		int hash_num = hash(tabel);
		if (worker[hash_num] != NULL)
		{
			Node* ptr = new Node;
			ptr = worker[hash_num];
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			Node* next_worker = new Node;
			createNode(next_worker, tabel, money, surname, name, otch);
			ptr->next = next_worker;
		}
		else
		{
			Node* next_worker = new Node;
			createNode(next_worker, tabel, money, surname, name, otch);
			worker[hash_num] = next_worker;
		}
	}

	void search(int tabel)
	{

		Node* result = new Node;
		result = search1(tabel);
		if (result)
		{
			cout << "\tNumber of tabel: " << result->tabel << endl;
			cout << result->surname << endl;
			cout << result->name << endl;
			cout << result->otch << endl;
			cout << result->money << endl;

		}
		else
		{
			cout << "error" << endl;
			return;
		}


	}

};

void main()
{
	hashTable table;
	int tabel_num;

	table.insertNode(12, 20000, "petrov", "petya", "petrovich");
	table.insertNode(13, 24000, "ivanov", "ivan", "petrovich");
	table.insertNode(23, 20000, "petrov", "ivan", "pavlovich");
	table.insertNode(12, 20000, "sergeev", "vladimir", "ivanovich");
	cout << "enter tabel: " << endl;
	cin >> tabel_num;
	table.search(tabel_num);
	system("pause");
}