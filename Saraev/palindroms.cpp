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
	void appendChild(Node* child) { mChildren.push_back(child); }
	unsigned int size() { return  mChildren.size(); }
	Node* findChild(char c)
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
private:
	char mContent;
	bool mMarker;
	vector<Node*> mChildren;
};
bool palindrom(string str) {
	int left_index = 1;
	int right_index = str.size() - 1;
	while (left_index < right_index)
		if (str[left_index++] != str[right_index--])
			return false;

	return true;
}

class Trie {
public:
	Trie() { root = new Node(); }
	~Trie() {};
	Node * haveRoot() { return root; }
	void addWord(string s)
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
	void wherePalindrom(Node*p, string s = "")
	{

		if (!p)return;
		if (p->wordMarker() && palindrom(s + p->content()))cout << s + p->content() << endl;
		for (unsigned int i = 0; i < p->children().size(); i++)
		{
			wherePalindrom(p->children()[i], s + p->content());
		}
	}
private:
	Node* root;
};

int main()
{
	Trie* trie = new Trie();
	trie->addWord("reer");
	trie->addWord("yyyyy");
	trie->addWord("lol");
	trie->addWord("tyrpryt");
	trie->addWord("keks");
	trie->addWord("palindrom");
	trie->addWord("level");
	cout << "Palindroms : " << endl;
	trie->wherePalindrom(trie->haveRoot());

	delete trie;
	system("pause");
}