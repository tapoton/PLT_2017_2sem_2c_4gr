#include<iostream>
#include <string>
using namespace std;
const int ALPHABET_SIZE = 26;
const int CASE = 'a';
struct Node
{
	Node *parent = nullptr;
	Node *children[ALPHABET_SIZE] = {};
	char key = '\0';
	bool occurrences = 0; //значение узла
};
void InsertNode(Node *&trieTrie, char *word)
{
	if (trieTrie == nullptr)
	{
		trieTrie = new Node;
		trieTrie->key = '\0';
		trieTrie->parent = nullptr;
		trieTrie->occurrences = false;
		for (unsigned int i = 0; i<ALPHABET_SIZE; trieTrie->children[i] = nullptr, i++);
	}

	Node* currentNode = trieTrie;

	while (*word != '\0')
	{
		if (currentNode->children[*word - CASE] == nullptr)
		{
			currentNode->children[*word - CASE] = new Node();
			currentNode->children[*word - CASE]->key = *word;
			currentNode->children[*word - CASE]->parent = currentNode;
			for (unsigned int i = 0; trieTrie->children[i] != nullptr; currentNode->children[*word - CASE]->children[i] = nullptr, i++);
		}

		currentNode = currentNode->children[*word - CASE];

		++word;
	}
	currentNode->occurrences = true;
}

int count(string Buff)
{
	const int n = Buff.length();
	char *word = new char[n];
	for (int i = 0; i < n; i++)
		word[i] = Buff[i];
	int counter =-1;
	for (int i = 0; i < n; i++)
	{
		if (word[i] != 'a'&& word[i] != 'e'&& word[i] != 'i'&& word[i] != 'o'&& word[i] != 'u'&& word[i] != 'y')
			counter++;
	}
	return counter;
}
int count_of_childs(Node *trieTree)
{
	Node *New_tree = trieTree;
	int count = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (New_tree->children[i]) count++;
	return count;

}
void Search(Node *trieTree, int kol,int&count_word, string Buff = " ")
{
	Node *New_tree = trieTree;
	if (New_tree->key) Buff += New_tree->key;
	if (New_tree->occurrences)
	{
		int count_1 = count(Buff);
		if (count_1 == kol)
		{
			cout << Buff;
			count_word++;
		}
	}
	while (New_tree && count_of_childs(New_tree) == 1)
	{
		int i = 0;
		while (!New_tree->children[i])
			i++;
		Buff += New_tree->children[i]->key;
		if (New_tree->children[i]->occurrences)
		{
			int count_1 = count(Buff);
			if (count_1 == kol)
			{
				cout << Buff;
				count_word++;
			}
		}
		New_tree = New_tree->children[i];
	}
	if (New_tree && count_of_childs(New_tree) > 1)
	{
		int i = 0;
		string NewBuff = Buff;
		while (i < ALPHABET_SIZE)
		{
			if (New_tree->children[i])
				Search(New_tree->children[i], kol, count_word,NewBuff);
			i++;
		}
	}

}
void Print(Node* trieTree, string Buff = "")
{
	Node* New_trie = trieTree;
	if (New_trie->key) Buff += New_trie->key;
	if (New_trie->occurrences) cout << Buff << endl;
	while (New_trie && count_of_childs(New_trie) == 1)
		{
		int i = 0;
		while (!New_trie->children[i])
			 i++;
		Buff += New_trie->children[i]->key;
		if (New_trie->children[i]->occurrences) cout << Buff << endl;
		New_trie = New_trie->children[i];
		}
	if (New_trie && count_of_childs(New_trie)>1)
		 {
		int i = 0;
		string NewBuff = Buff;
		while (i<ALPHABET_SIZE)
			 {
			if (New_trie->children[i])
				Print(New_trie->children[i], NewBuff);
			i++;
			}
		}
	}
int main()
{
	int kol, kol_word=0;
	cout << "enter kol" << endl;
	cin >> kol;
	Node* basicTree=nullptr;
	InsertNode(basicTree, "be");
	InsertNode(basicTree, "bee");
	InsertNode(basicTree, "better");
	InsertNode(basicTree, "tea");
	InsertNode(basicTree, "ten");
	InsertNode(basicTree, "apple"); 
	InsertNode(basicTree, "apply");
	InsertNode(basicTree, "meal");
	InsertNode(basicTree, "me");
	InsertNode(basicTree, "mean");
	InsertNode(basicTree, "meat");
	Print(basicTree);
	Search(basicTree, kol,kol_word);
	cout << "\n the number of words" << kol_word;
	system("pause");
	return 0;
}