#include <iostream>
#include <string>
#include<vector>
using namespace std;
bool f(string s)// функция для определения палиндрома
{
	if(s.size()==2) return 0;
	for(int i=1, j=s.size()-1;i<=j;i++,j--)
		if(s[i]!=s[j]) return false;

	return 1;
}
class Node {
public:
	Node() { mContent = ' '; mMarker = false; }
	~Node() {}
	Node* findChild(char c)
	{
		for (unsigned int i = 0; i < mChildren.size(); i++)
	{
		Node* tmp = mChildren.at(i);
		if (tmp->mContent == c)
		{
			return tmp;
		}
	}

	return NULL;
	}
	
	

	char mContent;
	bool mMarker;
	vector<Node*> mChildren;
};
class Trie:public Node {
public:
	Trie()
	{
		root=new Node();
	}
	~Trie(){}
	Node * getRoot()
	{
		return root;
	}
	void addWord(string s)
	{
		Node* current = root;

	if (s.length() == 0)
	{
		current->mMarker=true;
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
			tmp->mContent=s[i];
			current->mChildren.push_back(tmp);
			current = tmp;
		}
		if (i == s.length() - 1)
			current->mMarker=true;
	}
	}
	void palindrom(Node* p,string s)
	{
		
		
		if(f(s+p->mContent))cout<<s+p->mContent;
		if(p==NULL) return ;
		
		for (unsigned int i = 0; i < p->mChildren.size();i++)
		{ palindrom(p->mChildren[i], s+p->mContent);}
			
	}
private:
	Node* root;
};
int main()
{
	Trie* trie = new Trie();
	trie->addWord("plo");
	trie->addWord("villiv");
	trie->addWord("lil");
	trie->addWord("liooil");
	
	trie->palindrom(trie->getRoot(),"");
	delete trie;
	system("pause");
}
