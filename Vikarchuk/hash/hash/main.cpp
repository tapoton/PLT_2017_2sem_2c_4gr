#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Hash
{
	struct item
	{
		string word;
		int linkedItemsCount;
		item *next;
	};

	static const int tableSize = 20;

	item *hashTable[tableSize];
	item *head = new item; // для списка из слов
public:
	
	Hash()
	{
		for (int i = 0; i < tableSize; i++)
		{
			hashTable[i] = new item;
			hashTable[i]->linkedItemsCount = 0;
			hashTable[i]->word = "";
			hashTable[i]->next = NULL;
		}
		head->word = "";
		head->linkedItemsCount = -1;
		head->next = NULL;
	}

	int hashIndex(string word)
	{
		int index = 0;
		
		for (int i = 0; i < word.length(); i++)
		{
			index += (int)word[i];
		}
		index %= tableSize;
		
		return index;
	}
	
	void addElement(string word)
	{
		int index = hashIndex(word);

		if (hashTable[index]->word == "")
			hashTable[index]->word = word;
		else
		{
			hashTable[index]->linkedItemsCount += 1;
			item *ptr = hashTable[index];
			while (ptr->next != NULL)
				ptr = ptr->next;
			
			item *addedElement = new item;
			addedElement->word = word;
			addedElement->next = NULL;
			addedElement->linkedItemsCount = -1;

			ptr->next = addedElement;
		}
	}

	void newList() // проверка повторяющихся более 1 раза слов
	{
		for (int i = 0; i < tableSize; i++)
		{
			if (hashTable[i]->linkedItemsCount > 0)
			{
				item *el = new item;
				el->word = hashTable[i]->word;
				el->linkedItemsCount = -1;
				el->next = NULL;

				if (head->word == "")
				{
					head = el;
				}
				else
				{
					item *ptr = head;
					while (ptr->next != NULL)
						ptr = ptr->next;
					ptr->next = el;
				}
			}
		}
	}

	void listOutput()
	{
		item *ptr = head;
		while (ptr->next != NULL)
		{
			cout << ptr->word << " ";
			ptr = ptr->next;
		}
	}

	void hashOutput()
	{
		for (int i = 0; i < tableSize; i++)
		{
			item *ptr = hashTable[i];
			cout << ptr->word << " ";
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
				cout << ptr->word << " ";
			}
			cout << endl;
		}
	}

};

int main()
{
	static const int charCount = 2048;
	
	char text[charCount];
	
	ifstream fin;
	fin.open("inputText.txt");
	
	Hash hashObj;
	
	
	//fin >> text;
	cin.getline(text, charCount);
	char c = text[0]; string word = "";
	int i = 0;

	while (c != '\0')
	{
		c = text[i];
		while ((text[i] != ' ') && ((int)text[i] != -52) && (text[i] != '\0') && (text[i] != '\n')) // часто концом строки почему-то является символ М с кодом -52
		{
			word += text[i];
			i++;
		}
		i++;
		hashObj.addElement(word);
		word = "";
	}
	hashObj.hashOutput();
	hashObj.newList();
	hashObj.listOutput();

	fin.close();

	system("pause");

	return 0;
}