//Find the frequency of each word in some text file.
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
	ui repeats;
	Node* Next;
	Node()
	{
		Next = nullptr;
		repeats = 0;
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

//default size of Hash_Table
const ui default_size = 53;

template <typename value>
class HashTable
{
	ui Table_size;
	Node<value>** Table;
	ui (*map)(value key);
public:
	HashTable(ui (*hash_func)(value ), const ui size = default_size)
	{
		map = hash_func;
		Table = new Node<value>*[size];
		Table_size = size;
		for (ui i = 0; i < size; i++)
			Table[i] = nullptr;
	}
	void add(value val)
	{
		ui index = (*map)(val) % Table_size;
		Node<value>* temp = Table[index]->get_by_val(val);
		if (temp == nullptr)
		{
			temp = new Node<value>;
			temp->val = val;
			temp->Next = Table[index];
			Table[index] = temp;
		}
		temp->repeats++;
	}
	Node<value>* const operator[](value word)
	{
		return Table[((*map)(key) % Table_size)]->get_by_val(key);
	}
	inline Node<value>* const operator[](ui index)
	{
		return Table[index];
	}
	inline ui get_size()
	{
		return Table_size;
	}
};

int main()
{
	int choice;
	HashTable<string> T([](string word)->ui
	{
		ui sum = 0;
		for (ui i = 0; i < word.length(); i++)
			sum += word[i];
		return sum;
	});
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
				for (ui i = 0; i < T.get_size(); i++)
				{
					Node<string>* temp = T[i];
					while (temp != nullptr)
					{
						cout <<"Word " << (temp->val) << " has " << temp->repeats << " repeats.\n";
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
					throw "Error:File could not be opened.\n";
				ui words = 0;
				while (!file.eof())
				{
					string word;
					getline(file, word, ' ');
					ui eow = (word.length() - 1);
					if (word[eow] == ',' || word[eow] == '.' || word[eow] == '!' || word[eow] == '?' || word[eow] == '\n' || word[eow] == ' ')
						word.erase(eow, 1);
					if (word[0] == ',' || word[0] == '.' || word[0] == '!' || word[0] == '?' || word[0] == '\n' || word[0] == ' ')
						word.erase(0, 1);
					T.add(word);
					++words;
				}
				file.close();
				for (ui i = 0; i < T.get_size(); i++)
				{
					Node<string>* temp = T[i];
					while (temp != nullptr)
					{
						cout << "Word " << (temp->val) << " has frequency " << (((double)(temp->repeats) / words) * 100) << " %.\n";
						temp = temp->Next;
					}
				}
				break;

			}
			case 0:return 0;
			default:cout << "Error:Try again\n"; break;
			}
		}
		catch (char* err)
		{
			cout << err << endl;
		}
	} while (true);
	return 1;
}