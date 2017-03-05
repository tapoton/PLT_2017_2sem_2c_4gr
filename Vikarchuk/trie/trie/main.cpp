#include<iostream>
#include<string>

using namespace std;

const int ALPHABET_SIZE = 26;

class trie
{
	struct Node
	{
		bool is_end; // if the node is the end of the word
		int prefix_count; // count of words with prefix <head - current>
		Node *child[ALPHABET_SIZE];
	} *head;

public:

	trie()
	{
		head = new Node;
		head->prefix_count = 0;
		head->is_end = false;
		for (unsigned int i = 0; i < ALPHABET_SIZE; i++)
		{
			head->child[i] = NULL;
		}
	}

	void init(Node *node)
	{
		node->prefix_count = 0;
		node->is_end = false;
		for (unsigned int i = 0; i < ALPHABET_SIZE; i++)
		{
			node->child[i] = NULL;
		}
	}

	void insert(string word)
	{
		Node *current = head;
		current->prefix_count++;
		
		for (unsigned int i = 0; i < word.length(); i++)
		{
			int letter = (int)word[i] - (int)'a';
			if (current->child[letter] == NULL)
			{
				current->child[letter] = new Node;
				init(current->child[letter]);
			}
			current->child[letter]->prefix_count++;
			current = current->child[letter];
		}
		current->is_end = true;
	}

	bool search(string word)
	{
		Node *current = head;
		
		for (unsigned int i = 0; i < word.length(); i++)
		{
			int letter = (int)word[i] - (int)'a';
			if (current->child[letter] == NULL)
				return false;
			current = current->child[letter];
		}
		return current->is_end;
	}

	int words_with_prefix(string prefix)
	{
		Node *current = head;

		for (unsigned int i = 0; i < prefix.length(); i++)
		{
			int letter = (int)prefix[i] - (int)'a';
			if (current->child[letter] == NULL)
				return 0;
			else
				current = current->child[letter];
		}
		return current->prefix_count;
	}
};

int main()
{ 
	trie Words;
	
	string word;
	cout << "Enter words, then enter 0:\n";
	do
	{
		cin >> word;
		if(word != "0")
			Words.insert(word);
	} while (word != "0");

	cout << "Enter prefix: ";
	string prefix;
	cin >> prefix;
	cout << "\n" << Words.words_with_prefix(prefix) << " words with prefix " << prefix << " were found.\n";

	system("pause");

	return 0;
}