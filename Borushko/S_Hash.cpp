//If there are problems with encoding, then reload file in windows 1251 encoding.
//Задан текстовый файл. Сформировать набор словосочетаний по два и более слова, встречающихся в тексте не менее двух раз.
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Размер хеш-таблицы по умолчанию
const int hashSize = 53;

//Структура узел описана глобально для удобства возвращения элемента в хеш-таблице
struct Node
{
	string val;
	int key;
	Node* Next;
	Node* Prev;
	Node()
	{
		Next = Prev = nullptr;
	}
	Node* getByValue(string val)
	{
		Node* temp = this;
		while (temp != nullptr && temp->val != val)
			temp = temp->Next;
		return temp;
	}
	~Node()
	{
		Next = Prev = nullptr;
	}
};

#ifdef _IOSTREAM_ //Если подключён iostream
//Переопределить оператор cout для связного списка в виде указателя на начальный узел. Const 2 раза - для безопасности, чтобы не менять объект.
ostream& operator<<(ostream& os, const Node* const temp)
{
	const Node* ptr = temp;
	while (ptr != nullptr)
	{
		os << ptr->val << endl;
		ptr = ptr->Next;
	}
	return os;
}
#endif

//В качестве ключа используется количество повторений элемента в таблице
class HashTable
{
private:
	unsigned int hSize;
	Node** Table;
	//Поиск во всей таблице узла со значением val. Если узел не найден, то возвращается nullptr
	Node* find(string val)
	{
		Node* temp = nullptr;
		for (unsigned int i = 0; i < hSize && temp == nullptr; i++)
			if (Table[i] != nullptr)
				temp = Table[i]->getByValue(val);
		return temp;
	}
public:
	HashTable(const int size = hashSize)
	{
		Table = new Node*[size];
		hSize = size;
		for (int i = 0; i < hSize; i++)
			Table[i] = nullptr;
	}
	void add(string val)
	{
		Node* temp = find(val);
		int key = 0;
		if (temp != nullptr)
		{
			key = temp->key;
			if (temp->Next != nullptr)
				(temp->Next)->Prev = temp->Prev;
			if (temp->Prev != nullptr)
				(temp->Prev)->Next = temp->Next;
			if (Table[key - 1] == temp)
				Table[key - 1] = temp->Next;
			temp->Next = temp->Prev = nullptr;
		}
		else
		{
			temp = new Node;
			temp->val = val;
		}
		if (Table[key] != nullptr)
		{
			temp->Next = Table[key];
			Table[key]->Prev = temp;
		}
		Table[key] = temp;
		temp->key = key + 1;
	}
	//Возвращается указатель на начало списка, который обязательно будет состоять из узлов с одним ключом, но с разными значениями. Если список пуст, возвращается nullptr
	Node* const operator[](int key)
	{
		if (key > hSize || key < 1)
			throw "Error:Out of range.\n";
		return Table[key - 1];
	}
};

//Класс связного списка, работающий с уже существующими узлами
class LinkedList
{
	Node* begin;
public:
	LinkedList()
	{
		begin = nullptr;
	}
	LinkedList(Node* init)
	{
		begin = init;
	}
	void add(Node* begin_ptr)
	{
		Node* tmp = begin_ptr;
		while (tmp != nullptr)
		{
			Node* temp = new Node;
			temp->val = tmp->val;
			temp->Next = begin;
			begin = temp;
			tmp = tmp->Next;
		}
	}
	//Обрабатываем все узлы и в том, и в другом порядке некоторой функцией func
	template <typename T>
	void work(T func)
	{
		Node* temp = begin, *temp1 = nullptr;
		if (temp != nullptr)
			while (temp->Next != nullptr)
			{
				temp1 = temp->Next;
				while (temp1 != nullptr)
				{
					func(temp, temp1);
					func(temp1, temp);
					temp1 = temp1->Next;
				}
				temp = temp->Next;
			}
	}
	~LinkedList()
	{
		while (begin != nullptr)
		{
			Node* garb = begin;
			begin = begin->Next;
			delete garb;
		}
	}
};

int main()
{
	int choice;
	HashTable T;
	do
	{
		try
		{
			cout << "1: add words to the table"
				 << "\n2: see table insides\n3: process\n0: end\n";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				string val;
				cout << "Enter string: ";
				cin >> val;
				T.add(val);
				break;
			}
			case 2:
			{
				for (int i = 1; i <= hashSize; i++)
				{
					if (T[i] != nullptr)
						cout << "Elements with key " << i << ":\n" << T[i];
					else
						cout << "No elements with key " << i << endl;
				}
				break;
			}
			case 3:
			{
				ifstream file;
				string directory;
				cout << "File directory:\n";
				cin >> directory;
				file.open(directory);
				if (!file.is_open())
					throw "ERROR. File not found.\n";
				while (!file.eof())
				{
					string word;
					getline(file, word, ' ');
					T.add(word);
				}
				file.close();
				LinkedList L;
				for (int i = 2; i <= hashSize; i++)
					L.add(T[i]);
				L.work([](Node* temp1, Node* temp)
				{
					cout << (temp1->val) << ' ' << (temp->val) << endl;
				});
				break;
			}
			case 0:return 0;
			default:cout << "ERROR. Try again\n"; break;
			}
		}
		catch (char* err)
		{
			cout << err << endl;
		}
	} 
	while (true);
	return 1;
}