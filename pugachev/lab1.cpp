#include<iostream>
#include<string>

using namespace std;

const int n = 26;

class trie
{
public:
	struct Node
	{
		bool wordend;
		int number;
		char value; 
		Node *child[n];
	} *head;



	trie()
	{
		head = new Node;
		head->wordend = 0;
		head->value = 0;
		head->number = 0;
		for ( int i = 0; i < n; i++)
		{
			head->child[i] = NULL;
		}
	}

	void init(Node *node, char a, int i)
	{
		node->wordend = 0;
		i++;
		node->number = i;
		node->value = a;
		for (int i = 0; i < n; i++)
		{
			node->child[i] = NULL;
		}
	}

	void insert(string word)
	{
		Node *current = head;

		for (int i = 0; i < word.length(); i++)
		{
			int letter = (int)word[i] - (int)'a';
			if (current->child[letter] == NULL)
			{
				current->wordend = 0;
				current->child[letter] = new Node;
				init(current->child[letter], word[i],i);
			}
			
			current = current->child[letter];
		}
		current->wordend = 1;
	};

	bool noChild(Node* newn)
	{
		for (int i = 0; i < n; i++)
		{
			if (newn->child[i]!=NULL)
				return 0;
		}
		return 1;
	};
	/*void deleteEven(Node *newr, int i) // функция удаления веток чётной длины
	{
		int k;
		for ( k = 0; k < n; k++)
		{
			if (newr->child[k] != NULL)
			{
				deleteEven(newr->child[k], ++i); // вызываем функцию от потомка и удавиваем номер буквы i чтобы потом при удалении всего слова очередная буква была чётной 
				i *= 2;
			}
		}
			if ((i % 2 == 0)&&(noChild(newr)))
			{
				delete newr;
			}
		
	};*/
	bool deleteEven(Node *newr) // функция удаления веток чётной длины
	{
		bool deletecheck = 0;
		int k;
		for (k = 0; k < n; k++)
		{
			if (newr->child[k] != NULL)
			{
				if (deleteEven(newr->child[k]))
				 newr->child[k] = NULL; 
			}
		}
		if (((newr->wordend==0) && (noChild(newr)))||((newr->number%2==0)&& (noChild(newr))))
		{
			 newr = NULL;
			deletecheck = 1;
		}
		return deletecheck;
	};

	void newdelete()
	{
		Node* newr = head;
		deleteEven(newr);
	};
	bool search(string word)
	{
			Node *current = head;
			bool k = 0;
			for (int i = 0; i < word.length(); i++)
			{
				int letter = (int)word[i] - (int)'a';
				if (current->child[letter]==NULL)
					return 0;
				current = current->child[letter];
			}
			return 1;
	};
};
int main()
{
	trie Words;

	string word;
	cout << "Enter words, then enter 0:\n";
	do
	{
		cin >> word;
		if (word != "0")
			Words.insert(word);
	} while (word != "0");
	Words.newdelete();
	cout << "enter the word to check" << endl;
	do
	{
		cin >> word;
		(Words.search(word)) ? cout << "yes" : cout << "no";
		cout << endl;
	} while (word != "0");
	system("pause");
	return 0;
}