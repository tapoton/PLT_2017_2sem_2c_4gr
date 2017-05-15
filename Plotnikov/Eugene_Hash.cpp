//If there is problems with coding, then reload file in windows 1251 coding.
//«адан список имен людей.ќпределить частоту использовани€ каждого имени в некотором тексте.
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//type of indexes in Hash-Table
typedef unsigned int ui;

//struct Node described globally so it could be easier to return the List of values with the same keys.
template <typename value>
struct Node
{
	value val;
	ui key;
	Node* Next;
	Node* Prev;
	Node()
	{
		Next = Prev = nullptr;
	}
	Node* get_by_val(value val)
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

#ifdef _IOSTREAM_ //if iostream included
//Overload cout for the list of Nodes where temp is the pointer on the begining of the list.
template <typename value>
ostream& operator<<(ostream& os, const Node<value>* const temp)
{
	const Node<value>* ptr = temp;
	while (ptr != nullptr)
	{
		os << ptr->val << endl;
		ptr = ptr->Next;
	}
	return os;
}
#endif


//default size of Hash_Table
const ui default_size = 53;

template <typename value>
class HashTable
{
private:
	ui Table_size;
	Node<value>** Table;
	//Search in the table element with value val, if not found, return nullptr.
	Node<value>* find(value val)
	{
		Node<value>* temp = nullptr;
		for (ui i = 0; i < Table_size && temp == nullptr; i++)
			if (Table[i] != nullptr)
				temp = Table[i]->get_by_val(val);
		return temp;
	}
public:
	HashTable(const ui size = default_size)
	{
		Table = new Node<value>*[size];
		Table_size = size;
		for (ui i = 0; i < Table_size; i++)
			Table[i] = nullptr;
	}
	void add(value val)
	{
		Node<value>* temp = find(val);
		ui key = 0;
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
			temp = new Node<value>;
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
	Node<value>* const operator[](ui key)
	{
		if (key > Table_size || key < 1)
			throw "Error:Out of range.\n";
		return Table[key - 1];
	}
};

int main()
{
	int choice;
	HashTable<string> T;
	do
	{
		try
		{
			cout << "Enter 1 to add words to the table,"
				<< "\n2 to see table,\n3 to see the frequency of each word in the text file,\n0 to end.\n";
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
				for (ui i = 1; i <= default_size; i++)
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
				ui words = 0;
				while (!file.eof())
				{
					string word;
					getline(file, word, ' ');
					T.add(word);
					++words;
				}
				file.close();
				for (ui i = 1; i <= default_size; i++)
				{
					if (T[i] != nullptr)
						cout << "Elements with frequency " << (((double)(i) / words) * 100) << ":\n" << T[i];
				}
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
	} while (true);
	return 1;
}