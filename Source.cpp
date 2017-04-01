

/*Лаба 1: в нагруженном дереве найти слово максимальной длинны*/


#include<iostream>
#include<string>
using namespace std;
const char first = 'a';
const int apb = 26;
struct Node
{
	char key;
	Node*child[apb];
	bool eow;

};
void init(Node*head)
{
	head->key = '\0';
	for (int i = 0; i < apb; i++)
		head->child[i] = NULL;
	head->eow = 0;
}

void addletter(Node *tmp, int i, char letter, bool check)
{
	Node* nextletter = new Node;
	nextletter->eow = check;
	nextletter->key = letter;
	for (unsigned int i = 0; i < apb; i++)
	{
		nextletter->child[i] = NULL;
	}
	tmp->child[i] = nextletter;
}

void insertWord(string word,Node*temp) 
{
	for (unsigned int i = 0; i < word.length(); i++) {

		if (temp->child[word[i] - first] == NULL) {
			addletter(temp, word[i] - first, word[i], i + 1 == word.length() ? true : false);
		}
		else {
			if (i + 1 == word.length()) {
				temp->child[word[i] - first]->eow = true;
			}
		}

		temp = temp->child[word[i] - first];
	}
}


string longest(Node* temp, string current_word = "") 
{
	if (temp->eow) 
		return current_word;
	
	string longest_word;

	for (int i = 0; i < apb; i++) 
	{
		if (temp->child[i] != NULL) 
		{
			current_word += temp->child[i]->key;
			string word = longest(temp->child[i], current_word);
			if (longest_word.length() < word.length()) 
			{
				longest_word = word;
			}

			if (longest_word.length() > 0) {
				current_word.erase(current_word.length() - 1, 1);
			}
		}
	}
	return longest_word;
}

void show(Node *temp, unsigned int level = 0) {
	if (temp == NULL) {
		return;
	}
	for (unsigned int i = 1; i < level; i++) {
		cout << "\t";
	}
	cout << temp->key << endl;
	for (int i = 0; i < apb; i++) {
		show(temp->child[i], level + 1);
	}
}


void main()
{
	Node trie;
	init(&trie);
	insertWord("brown", &trie);
	insertWord("author", &trie);
	insertWord("austroneer",&trie);
	insertWord("bowling", &trie);
	insertWord("home", &trie);
	show(&trie);
	string s=longest(&trie);
	cout << s<<endl;
	system("pause");
}