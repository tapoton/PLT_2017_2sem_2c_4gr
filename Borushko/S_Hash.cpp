//If there are problems with encoding, then reload file in windows 1251 encoding.
//Задан текстовый файл. Сформировать набор словосочетаний по два и более слова, встречающихся в тексте не менее двух раз.
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

//Размер хеш-таблицы по умолчанию
const int hashSize = 53;

template<typename value>
//Структура узел описана глобально для удобства возвращения элемента в хеш-таблице
struct Node
{
	value val;
	int repeats;
	Node* Next;
	Node()
	{
		Next = nullptr;
		repeats = 0;
	}
	Node* getByValue(value val)
	{
		Node* temp = this;
		while (temp != nullptr && temp->val != val)
			temp = temp->Next;
		return temp;
	}
	~Node()
	{
		Next = nullptr;
	}
};

template<typename value>
//В качестве ключа используется количество повторений элемента в таблице
class HashTable
{
private:
	unsigned int hSize;
	Node<value>** Table;
	int hash(value key)
	{
		int s = 0;
		string ss = (string)key;
		for (int i = 0; i < ss.length(); i++)
			s += ss[i];
		return s % hSize;
	}
	//Поиск во всей таблице узла со значением val. Если узел не найден, то возвращается nullptr
	Node<value>* find(string key)
	{
		Node<value>* temp = Table[hash(key)]->getByValue(key);
		return Table[hash(key)]->getByValue(key);
	}
public:
	HashTable(const int size = hashSize)
	{
		Table = new Node<value>*[size];
		hSize = size;
		for (int i = 0; i < hSize; i++)
			Table[i] = nullptr;
	}
	void add(value val)
	{
		Node<value>* temp = find(val);
		if (temp == nullptr)
		{
			temp = new Node<value>;
			temp->val = val;
			int index = hash(val);
			temp->Next = Table[index];
			Table[index] = temp;
		}
		temp->repeats++;
	}
	//Возвращается указатель на начало списка, который обязательно будет состоять из узлов с одним ключом, но с разными значениями. Если список пуст, возвращается nullptr
	Node<value>* const operator[](value word)
	{
		return Table[hash(word)]->getByValue(word);
	}
	Node<value>* const operator[](int index)
	{
		return Table[index];
	}
};

template<typename value>
//Класс связного списка, работающий с уже существующими узлами
class LinkedList
{
	Node<value>* begin;
public:
	LinkedList()
	{
		begin = nullptr;
	}
	LinkedList(Node<value>* init)
	{
		begin = init;
	}
	void add(Node<value>* begin_ptr)
	{
		Node<value>* tmp = begin_ptr;
		while (tmp != nullptr)
		{
			Node<value>* temp = new Node<value>;
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
		Node<value>* temp = begin, *temp1 = nullptr;
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
			Node<value>* garb = begin;
			begin = begin->Next;
			delete garb;
		}
	}
};

typedef string val_type;

int main()
{
	int choice;
	HashTable<val_type> T;
	do
	{
		try
		{
			cout  << "\n2: see table insides\n3: process\n0: end\n";
			cin >> choice;
			switch (choice)
			{
			case 2:
			{
				for (int i = 0; i < hashSize; i++)
				{
					Node<val_type>* temp = T[i];
					while (temp != nullptr)
					{
						cout << (temp->val) << ": " << temp->repeats << " repeat(s).\n";
						temp = temp->Next;
					}
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
					val_type word;
					getline(file, word, ' ');
					if (ispunct(word[word.length() - 1]))
						word.erase(word.length() - 1, 1);
					if (ispunct(word[0]))
						word.erase(0, 1);
					T.add(word);
				}
				file.close();
				LinkedList<val_type> L;
				for (int i = 0; i < hashSize; i++)
				{
					Node<val_type>* temp = T[i];
					while (temp != nullptr)
					{
						if (temp->repeats > 1)
							L.add(T[i]);
						temp = temp->Next;
					}
				}
				L.work([](Node<val_type>* temp1, Node<val_type>* temp)
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