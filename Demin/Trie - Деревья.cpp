
#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

const int  alphabet = 33;

struct Node
{
	char key = '\0';
	Node* parent;
	Node* child[alphabet] = {};
	bool end = 0;
};

void Insert(char word[], Node* trie )
{
	char* word_ptr = word;
	Node* trie_ptr = trie;
	while (*(word_ptr))
	{
		int i = 0;
		while (trie_ptr->child[i] && trie_ptr->child[i]->key != *word_ptr)
			i++;
		if (!trie_ptr->child[i])
		{
			trie_ptr->child[i] = new Node;
			trie_ptr->child[i]->key = *word_ptr;
			trie_ptr->child[i]->parent = trie_ptr;
		}
		trie_ptr = trie_ptr->child[i];
		word_ptr++;
	}
	trie_ptr->end = 1;
}

int Num_Of_Childs(Node* node)
{
	Node* ptr = node;
	int i, counter = 0;
	for (i = 0; i < alphabet; i++)
		if (ptr->child[i]) counter++;
	return counter;
}

void Print(Node* trie, string done = "")
{
	Node* ptr = trie;
	if (ptr->key) done += ptr->key;
	if (ptr->end) cout << done << endl;
	while (ptr && Num_Of_Childs(ptr)==1)
	{
		int i = 0;
		while (!ptr->child[i])
			i++;
		done += ptr->child[i]->key;
		if (ptr->child[i]->end) cout << done << endl;
		ptr = ptr->child[i];
	}
	if (ptr && Num_Of_Childs(ptr)>1)
	{
		int i = 0;
		string newdone = done;
		while (i<alphabet)
		{
			if(ptr->child[i])
				Print(ptr->child[i], newdone);
			i++;
		}
	}
}

void Even_Del(Node* trie)
{
	Node* ptr = trie;
	int childs = Num_Of_Childs(ptr), i = 0;
	while (childs)
	{
		childs--;
		while (!ptr->child[i])
			i++;
		int childs_of_child = Num_Of_Childs(ptr->child[i]), j = 0;
		while (childs_of_child)
		{
			childs_of_child--;
			while (!ptr->child[i]->child[j])
				j++;
			if (ptr->child[i]->child[j]->end)
				ptr->child[i]->child[j]->end = NULL;
			if (Num_Of_Childs(ptr->child[i]->child[j]))
				Even_Del(ptr->child[i]->child[j]);
			else
			{
				delete ptr->child[i]->child[j];
				ptr->child[i]->child[j] = NULL;
			}
			if (!Num_Of_Childs(ptr->child[i]) && !ptr->child[i]->end)
			{
				delete ptr->child[i];
				ptr->child[i] = NULL;
			}
			if (!Num_Of_Childs(ptr) && ptr->parent)
			{
				int k = 0;
				while (ptr->parent->child[k] != ptr)
					k++;
				ptr->parent->child[k] = NULL;
				delete ptr;
			}
			j++;
		}
		i++;
	}
}

void main()
{
	setlocale(LC_ALL, "rus");
	Node trie;
	Insert("sad", &trie);
	Insert("saint", &trie);
	Insert("safe", &trie);
	Insert("saturn", &trie);
	Insert("time", &trie);
	Insert("tired", &trie);
	Insert("ticket", &trie);
	Insert("apple", &trie);
	Insert("apply", &trie);
	Insert("appetite", &trie);
	Insert("deny", &trie);
	Insert("dental", &trie);
	Insert("dellusion", &trie);
	Insert("fury", &trie);
	Insert("funeral", &trie);
	Insert("fuel", &trie);
	Print(&trie);
	Even_Del(&trie);
	cout << "----------"<<endl;
	Print(&trie);
	cout << endl;
	system("pause");
}

=======
// comment

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

const int  alphabet = 33;

struct Node
{
	char key = '\0';
	Node* parent;
	Node* child[alphabet] = {};
	bool end = 0;
};

void Insert(char word[], Node* trie )
{
	char* word_ptr = word;
	Node* trie_ptr = trie;
	while (*(word_ptr))
	{
		int i = 0;
		while (trie_ptr->child[i] && trie_ptr->child[i]->key != *word_ptr)
			i++;
		if (!trie_ptr->child[i])
		{
			trie_ptr->child[i] = new Node;
			trie_ptr->child[i]->key = *word_ptr;
			trie_ptr->child[i]->parent = trie_ptr;
		}
		trie_ptr = trie_ptr->child[i];
		word_ptr++;
	}
	trie_ptr->end = 1;
}

int Num_Of_Childs(Node* node)
{
	Node* ptr = node;
	int i, counter = 0;
	for (i = 0; i < alphabet; i++)
		if (ptr->child[i]) counter++;
	return counter;
}

void Print(Node* trie, string done = "")
{
	Node* ptr = trie;
	if (ptr->key) done += ptr->key;
	if (ptr->end) cout << done << endl;
	while (ptr && Num_Of_Childs(ptr)==1)
	{
		int i = 0;
		while (!ptr->child[i])
			i++;
		done += ptr->child[i]->key;
		if (ptr->child[i]->end) cout << done << endl;
		ptr = ptr->child[i];
	}
	if (ptr && Num_Of_Childs(ptr)>1)
	{
		int i = 0;
		string newdone = done;
		while (i<alphabet)
		{
			if(ptr->child[i])
				Print(ptr->child[i], newdone);
			i++;
		}
	}
}

void Even_Del(Node* trie)
{
	Node* ptr = trie;
	int childs = Num_Of_Childs(ptr), i = 0;
	while (childs)
	{
		childs--;
		while (!ptr->child[i])
			i++;
		int childs_of_child = Num_Of_Childs(ptr->child[i]), j = 0;
		while (childs_of_child)
		{
			childs_of_child--;
			while (!ptr->child[i]->child[j])
				j++;
			if (ptr->child[i]->child[j]->end)
				ptr->child[i]->child[j]->end = NULL;
			if (Num_Of_Childs(ptr->child[i]->child[j]))
				Even_Del(ptr->child[i]->child[j]);
			else
			{
				delete ptr->child[i]->child[j];
				ptr->child[i]->child[j] = NULL;
			}
			if (!Num_Of_Childs(ptr->child[i]) && !ptr->child[i]->end)
			{
				delete ptr->child[i];
				ptr->child[i] = NULL;
			}
			if (!Num_Of_Childs(ptr) && ptr->parent)
			{
				int k = 0;
				while (ptr->parent->child[k] != ptr)
					k++;
				ptr->parent->child[k] = NULL;
				delete ptr;
			}
			j++;
		}
		i++;
	}
}

void main()
{
	setlocale(LC_ALL, "rus");
	Node trie;
	Insert("sad", &trie);
	Insert("saint", &trie);
	Insert("safe", &trie);
	Insert("saturn", &trie);
	Insert("time", &trie);
	Insert("tired", &trie);
	Insert("ticket", &trie);
	Insert("apple", &trie);
	Insert("apply", &trie);
	Insert("appetite", &trie);
	Insert("deny", &trie);
	Insert("dental", &trie);
	Insert("dellusion", &trie);
	Insert("fury", &trie);
	Insert("funeral", &trie);
	Insert("fuel", &trie);
	Print(&trie);
	Even_Del(&trie);
	cout << "----------"<<endl;
	Print(&trie);
	cout << endl;
	system("pause");
}

