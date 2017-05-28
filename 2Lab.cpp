#include <iostream>
#include <set>
#include <string>

using namespace std;

const int p = 127; // только простое
const int Table_Size = 99991; //модуль хеша (от 0 до 99991 (только простое)) // 1e9+7 размер таблици

class HashTable {

	struct hash_Node // узел хеш-таблици
	{
		hash_Node *Next; // следующий узел с тем же ключем
		int count_name; // кличество повторения имени
		string name; // имя
	};

	hash_Node *Table[Table_Size];

	~HashTable() // очистка памяти
	{
		for (int i = 0; i < Table_Size; i++)
		{
			if (Table[i] != NULL)
				dell(Table[i]);
		}
	}

	void dell(hash_Node *T) // удаление всех вершин с одинаковым хешом
	{
		if (T->Next == NULL)
		{
			delete T;
		}
		else
		{
			hash_Node *p;
			p = T->Next;
			T->Next = NULL;
			dell(p);
			delete T;
		}
	}

public:
	void print() // печать всех имен
	{
		for (int i = 0; i < Table_Size; i++) 
		{
			Print_Node_line(Table[i]);
		}
	}

	void Add_name(string name) // добавление имени в таблицу
	{
		int hash_s = bild_hash(name); // получение хеша
		if (Table[hash_s] == NULL) // если нет такого узла то создать его
		{
			Table[hash_s] = bild_Node(name);
		}
		else // если есть то проверить есть ли такое имя
		{
			hash_Node *TNode = Table[hash_s];
			while ((TNode->Next != NULL) && (TNode->name != name))
				TNode = TNode->Next;
			if (TNode->name != name) // если нет то создать еще 1 узел с тем же хешем
			{
				TNode->Next = bild_Node(name);
			}
			else
				TNode->count_name++; // иначе (если есть) увеличить количество повторений
		}
	}

private:

	long long bild_hash(string s) //получение хеша
	{
		long long hash = 0;
		for (int i = s.length() - 1; i >= 0; i--)
		{
			hash *= p;
			hash += s[i];
			hash %= Table_Size;
		}
		return (hash);
	}

	hash_Node *bild_Node(string name) // создание нового узла
	{
		hash_Node *NewNode = new hash_Node;
		NewNode->name = name;
		NewNode->count_name = 1;
		NewNode->Next = NULL;
		return (NewNode);
	}

	void Print_Node_line(hash_Node *TNode) // печать всех имен с одинаковым хешом
	{
		if (TNode != NULL)
		{
			cout << TNode->name << " " << TNode->count_name << endl;
			Print_Node_line(TNode->Next);
		}
	}

};

HashTable Table;

int main()
{
	int n;
	cin >> n; // общее количество имен

	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s; // ввод имени
		Table.Add_name(s); // добавить очередное имя в таблицу
	}

	Table.print(); // вывод всей таблицы

	

	system("pause");

	return (0);
}