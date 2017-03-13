#include <iostream>
#include <string>
using namespace std;

const int alphabet = 26;
const int alphpabetSogl = 21;
const int first = 'a';
const char sogl[alphpabetSogl] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

class TrieTree
{
	struct Node 
	{
		char key;
		bool isEnd;
		Node* child[alphabet];
	};
	Node* head = NULL;
	void show(Node *temp, unsigned int level = 0) 
{
		if (temp == NULL)
		{
			return;
		}
		for (unsigned int i = 1; i < level; i++) 
		{
			cout << "\t";
		}
		cout << temp->key << endl;
		for (int i = 0; i < alphabet; i++)
		{
			show(temp->child[i], level + 1);
		}
	}
	int kol_sogl(Node* temp, int &S)
	{
		for (unsigned int i = 0; i < alphabet; i++)	
		{
			if (temp->child[i] != NULL)		
			{
				if (temp->child[i]->isEnd)
				{
					for (int j = 0; j < alphpabetSogl; j++)
					{
						if (temp->child[i]->key == sogl[j]) 
						{
							S++;
						}
					}
			
				}
				kol_sogl(temp->child[i], S);
			}
		}		
		return S;
	}
public:
	void create(Node *lead, int index, char c, bool check)
	{
		Node* follower = new Node;
		follower->isEnd = check;
		follower->key = c;
		for (unsigned int i = 0; i < alphabet; i++)
		{
			follower->child[i] = NULL;
		}
		lead->child[index] = follower;
	}
	void insert(string word)
	{
		if (head == NULL)
		{
			head = new Node;
			head->key = ' ';
			head->isEnd = false;
			for (unsigned int i = 0; i < alphabet; i++)
			{
				head->child[i] = NULL;
			}
		}
		Node* temp = head;
		for (unsigned int i = 0; i < word.length(); i++)
		{
			if (temp->child[word[i] - first] == NULL)
			{
				create(temp, word[i] - first, word[i], i + 1 == word.length() ? true : false);
			}
			else
			{
				if (i + 1 == word.length())
				{
					temp->child[word[i] - first]->isEnd = true;
				}	
			}
			temp = temp->child[word[i] - first];
		}
	}
	void show()
	{
		show(head);
	}

	int kol_sogl()
	{
		int S = 0;
		return kol_sogl(head, S);
	}
};

void main()
{
	setlocale(LC_ALL, "rus");
	TrieTree objTree;

	string str;
	cout << "Ввести слова: ";
	while (cin.peek() != '\n')
	{
		cin >> str;
		objTree.insert(str);
	}
	objTree.show();

	cout << "Колличество слов, оканчивающихся на согласную букву = " << objTree.kol_sogl() << endl;

	system("pause");
}
