#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	Node() { mContent = ' '; mMarker = false; }
	~Node() {}
	vector<Node*> children() { return mChildren; }

	char content() { return mContent; }
	void setContent(char c) { mContent = c; }
	bool wordMarker() { return mMarker; }
	void setWordMarker() { mMarker = true; }
	Node* findChild(char c);
	void appendChild(Node* child) { mChildren.push_back(child); }
	unsigned int size()
	{
		return  mChildren.size();
	}
private:
	char mContent;
	bool mMarker;
	vector<Node*> mChildren;
};

class Trie {
public:
	Trie();
	~Trie();
	Node * haveRoot()
	{
		return root;
	}
	void addWord(string s);
	bool searchWord(string s);
	string maxWord(Node* p)
	{
		if (p == NULL)return "";
		string s = "";
		for (unsigned int i = 0; i < p->children().size(); i++)
		{
			if (s.size() < maxWord((p->children())[i]).size())
				s = maxWord((p->children())[i]);
		}
		return p->content() + s;

	}
private:
	Node* root;
};

Node* Node::findChild(char c)
{
	for (unsigned int i = 0; i < mChildren.size(); i++)
	{
		Node* tmp = mChildren.at(i);
		if (tmp->content() == c)
		{
			return tmp;
		}
	}

	return NULL;
}

Trie::Trie()
{
	root = new Node();
}

Trie::~Trie()
{

}

void Trie::addWord(string s)
{
	Node* current = root;

	if (s.length() == 0)
	{
		current->setWordMarker();
		return;
	}

	for (unsigned int i = 0; i < s.length(); i++)
	{
		Node* child = current->findChild(s[i]);
		if (child != NULL)
		{
			current = child;
		}
		else
		{
			Node* tmp = new Node();
			tmp->setContent(s[i]);
			current->appendChild(tmp);
			current = tmp;
		}
		if (i == s.length() - 1)
			current->setWordMarker();
	}
}
bool Trie::searchWord(string s)
{
	Node* current = root;

	while (current != NULL)
	{
		for (unsigned int i = 0; i < s.length(); i++)
		{
			Node* tmp = current->findChild(s[i]);
			if (tmp == NULL)
				return 0;
			current = tmp;
		}

		return current->wordMarker();
		
	}
	return 0;
}

int main()
{
	Trie* trie = new Trie();
	trie->addWord("Hello");
	trie->addWord("Balloon");
	trie->addWord("Ball");
	trie->addWord("Bahlokn");
	cout << endl;
	string s = trie->maxWord(trie->haveRoot());
	cout << "Max word = ";
	for (unsigned int i = 1; i < s.size(); i++)
	{
		cout << s[i];
	}
	cout << endl;
	delete trie;
	system("pause");
}
