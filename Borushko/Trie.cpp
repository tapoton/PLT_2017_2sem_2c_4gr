#include <iostream> 
#include <cctype> 
#include <string>

using namespace std;

const int alphSize = 26;
const int alphIndex = 97;

class Trie
{
	struct Node
	{
		char value;
		Node* parent;
		Node* children[alphSize];
		unsigned int endOfWord, isLeaf : 1;
		Node()
		{
			endOfWord = 0;
			isLeaf = 1;
			parent = nullptr;
			for (int i = 0; i < alphSize; i++)
				children[i] = nullptr;
		}
	};
	Node* root;
	template <typename T>
	void goRound(T func, Node* begin)
	{
		if (begin != nullptr)
		{
			func(begin);
			for (int i = 0; i < alphSize; i++)
				if (begin->children[i] != nullptr)
					goRound(func, begin->children[i]);
		}
	}
	void (processWord)(Node* temp, void (func)(char), void endCall())
	{
		if (temp == nullptr || temp->parent == nullptr)
		{
			endCall();
			return ;
		}
		processWord(temp->parent, func, endCall);
		func(temp->value);
	}
	bool nodeIsLeaf(Node* temp)
	{
		bool res = 1;
		for (int i = 0; i < alphSize && res; i++)
			res = temp->children[i] == nullptr;
		return res;
	}
	template <typename T>
	void deleteWord(Node* endOfWord, T cond)
	{
		while ((cond(endOfWord)) && (endOfWord->parent != nullptr))
		{
			endOfWord->parent->children[(int)endOfWord->value - alphIndex] = nullptr;
			Node* toDelete = endOfWord;
			endOfWord = endOfWord->parent;
			toDelete->parent = nullptr;
			for (int i = 0; i < alphIndex; i++)
				toDelete->children[i] = nullptr;
			//delete toDelete;
		}
	}
	bool isPresent(string S, Node* temp)
	{
		string reverse = S;
		int subLength = S.length();
		for (int i = 0; i < subLength; i++)
			reverse[i] = S[subLength - i - 1];
		Node* current = temp;
		int dist = 0;
		while (current != nullptr)
		{
			dist++;
			current = current->parent;
		}
		bool result = (dist >= subLength);
		current = temp;
		while (result)
		{
			int i;
			for (i = 0; i < subLength && result; i++, current = current->parent)
				result = (current != nullptr) && (current->value == reverse[i]);
			if (result)
				break;
			dist -= i;
			result = dist >= subLength;
		}
		return result;
	}
public:
	Trie()
	{
		root = nullptr;
	}
	void getBuSubstring(string S, void visualizer(char), void endCall())
	{
		if (root == nullptr)
			return;
		for (int i = 0; i < alphSize; i++)
			if (root->children[i] != nullptr)
			{
				visualizer(toupper(root->children[i]->value));
				goRound([=](Node* temp)
				{
					if (temp->endOfWord && isPresent(S,temp))
						processWord(temp, visualizer, endCall);
				}, root->children[i]);
				endCall();
			}
	}
	void visualize(void visualizer(char),void endCall())
	{
		if (root == nullptr)
			return;
		for (int i = 0; i < alphSize ; i++)
			if (root->children[i] != nullptr)
			{
				visualizer(toupper(root->children[i]->value));
				goRound([=](Node* temp)
				{
					if (temp->endOfWord)
						processWord(temp, visualizer, endCall);
				}, root->children[i]);
				endCall();
			}
	}
	void deleteBySubstring(string S)
	{
		if (root == nullptr)
			return;
		for (int i = 0; i < alphSize; i++)
			if (root->children[i] != nullptr)
			{
				goRound([=](Node* temp)
				{
					if (isPresent(S, temp) && temp->isLeaf)
						deleteWord(temp, [=](Node* cpy)->bool {return nodeIsLeaf(cpy); });
				}, root->children[i]);
			}
	}
	void add(string S)
	{
		if (root == nullptr)
			root = new Node;
		root->value = '\0';
		Node* temp = root;
		for (int i = 0; i < S.length(); i++)
		{
			Node* next = temp->children[(int)tolower(S[i]) - alphIndex];
			if (next == nullptr)
			{
				temp->children[(int)tolower(S[i]) - alphIndex] = new Node;
				temp->children[(int)tolower(S[i]) - alphIndex]->value = tolower(S[i]);
				temp->children[(int)tolower(S[i]) - alphIndex]->parent = temp;
				temp->isLeaf = 0;
			}
			temp = temp->children[(int)tolower(S[i]) - alphIndex];
		}
		temp->endOfWord = 1;
	}
};

void print(char a)
{
	cout << a;
}

void step()
{
	cout << ('\n');
}

int main()
{
	Trie A;
	string a;
	while (1)
	{
		int n;
		cout << "1: add word; \n2: show tree; \n3: get word by substring; \n4: delete word containing substring; \n0: exit \n";
		cin >> n;
		switch (n)
		{
		case 1:
		{
			cout << "Enter word:";
			cin >> a;
			A.add(a);
			break;
		}
		case 2:
		{
			cout << "Tree:\n";
			A.visualize(print , step);
			break;
		}
		case 3:
		{
			cout << "Enter substring:";
			cin >> a;
			cout << "Words containing substring '" << a << "' :\n";
			A.getBuSubstring(a , print , step);
			break;
		}
		case 4:
		{
			cout << "Enter substring:";
			cin >> a;
			cout << "Tree:\n";
			A.deleteBySubstring(a);
			A.visualize(print, step);
			break;
		}
		case 0: return 0;
		default: break;
		}
	}
	return 0;
}
