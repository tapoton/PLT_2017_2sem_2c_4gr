#include <iostream>
#include <string>
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
	Node * haveRoot()
	{
		return root;
	}
	void addWord(string s);
	void print(Node*p, string s = "")
	{
		if (p) {

			if (p->wordMarker() && s != ""&&p->content() != -35)
				cout << s + p->content() << endl;


			for (unsigned int i = 0; i < p->children().size(); i++)
			{
				print((p->children())[i], s + p->content());
			}
		}
	}
	void tdelete(Node*p)
	{

		if (p) {
			for (unsigned int i = 0; i < p->children().size(); i++)
			{
				tdelete(p->children()[i]);
			}

			delete p;
		}

	}
	Node *returnNode(string s)
	{
		Node *p = root;

		for (unsigned int i = 0; i < s.size() - 1; i++)
			p = p->findChild(s[i]);
		return p;

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

int main()
{
	Trie* trie = new Trie();
	trie->addWord("Car");
	trie->addWord("Cat");
	trie->addWord("Catty");
	trie->addWord("Cool");
	trie->print(trie->haveRoot());
	cout << endl;

	trie->tdelete(trie->returnNode("Cat"));//удаляет нод последней буквы и все последущие

	trie->print(trie->haveRoot());

	delete trie;
	system("pause");
}