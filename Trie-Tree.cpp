#include <iostream> 
#include <cctype> 
#include <string>

using namespace std;

#ifndef NULL
#define NULL 0
#endif

template <typename T>
class Stack
{
	struct Node
	{
		T value;
		Node* Next;
		Node()
		{
			this->Next = nullptr;
		}
	};
	Node* Head;
	unsigned int size;
public:
	Stack()
	{
		Head = nullptr;
		size = 0;
	}
	inline bool is_empty()
	{
		return Head == nullptr;
	}
	inline unsigned int get_size()
	{
		return size;
	}
	void push(T val)
	{
		Node* temp = new Node;
		if (temp == nullptr)
			exit(1);
		temp->value = val;
		temp->Next = Head;
		Head = temp;
		size++;
	}
	T& pop()
	{
		if (is_empty())
			throw 1;
		Node* to_delete = Head;
		Head = Head->Next;
		T temp = to_delete->value;
		to_delete->value = NULL;
		delete to_delete;
		size--;
		return temp;
	}
};


const int a_size = 26;
const int alph_n = 97;

class Trie_Tree
{
	struct Node
	{
		char val;
		Node* parent;
		Node* child[a_size];
		unsigned int eow : 1;
		Node()
		{
			eow = 0;
			parent = nullptr;
			for (int i = 0; i < a_size; i++)
				child[i] = nullptr;
		}
	};
	Node* root;
	template <typename T>
	void rec_Depth_traverse(T func, Node* begin)
	{
		if (begin != nullptr)
		{
			func(*begin);
			for (int i = 0; i < a_size; i++)
				if (begin->child[i] != nullptr)
					passive_rec_Depth_traverse(func, begin->child[i]);
		}
	}
	template <typename T>
	void iter_Depth_traverse(T (func), Node* begin)
	{
		Stack<Node*> S;
		S.push(begin);
		while (!S.is_empty())
		{
			Node* temp = S.pop();
			func(temp);
			for (int i = a_size - 1; i > -1 ; i--)
				if (temp->child[i] != nullptr)
					S.push((temp->child[i]));
		}
	}
	void (work_with_word)(Node* temp, void*(func)(char), void end_call())
	{
		Stack<char> S;
		while (temp->parent != nullptr)
		{
			S.push(temp->val);
			temp = temp->parent;
		}
		while (!S.is_empty())
			func(S.pop());
		end_call();
	}
	bool equal(string S,Node* temp)
	{
		Stack<char> W;
		while (temp != nullptr && temp->parent != nullptr)
		{
			W.push(temp->val);
			temp = temp->parent;
		}
		bool result = (W.get_size() == S.length());
		for (int i = 0; i < S.length() && result; i++)
			result = (W.pop() == S[i]);
		return result;
	}
public:
	Trie_Tree()
	{
		root = new Node;
	}
	void visualize(void *(visualizer)(char),void end_call())
	{
		for (int i = 0; i < a_size ; i++)
			if (root->child[i] != nullptr)
			{
				visualizer(toupper(root->child[i]->val));
				end_call();
				iter_Depth_traverse([=](Node* temp)
				{
					if (temp->eow)
						work_with_word(temp, visualizer, end_call);
				}, root->child[i]);
				end_call();
			}
	}
	void find_word(string S, void *(visualizer)(char), void end_call())
	{
		for (int i = 0; i < a_size; i++)
			if (root->child[i] != nullptr)
			{
				end_call();
				iter_Depth_traverse([=](Node* temp)
				{
					if (temp->eow && equal(S, temp))
					{
						work_with_word(temp, visualizer, end_call);
						end_call();
						return ;
					}
				}, root->child[i]);
			}
		throw 2;
	}
	void add(string S)
	{
		Node* temp = root;
		for (int i = 0; i < S.length(); i++)
		{
			Node* next = temp->child[(int)tolower(S[i]) - alph_n];
			if (next == nullptr)
			{
				temp->child[(int)tolower(S[i]) - alph_n] = new Node;
				temp->child[(int)tolower(S[i]) - alph_n]->val = tolower(S[i]);
				temp->child[(int)tolower(S[i]) - alph_n]->parent = temp;
			}
			temp = temp->child[(int)tolower(S[i]) - alph_n];
		}
		temp->eow = 1;
	}
};

void* print(char a)
{
	cout << a;
	return nullptr;
}

void step()
{
	cout << ('\n');
}

int main()
{
	Trie_Tree A;
	string a;
	while (1)
	{
		try
		{
			int n;
			cout << "Enter 1 to add,\n2 to peek,\n3 to find word,\n0 to end.\n";
			cin >> n;
			switch (n)
			{
			case 1:
			{
				cout << "Enter the string:\n";
				cin >> a;
				A.add(a);
				break;
			}
			case 2:
			{
				cout << "Here's your tree:\n";
				A.visualize(print, step);
				break;
			}
			case 3:
			{
				cout << "Enter the string:\n";
				cin >> a;
				cout << "There you go:\n";
				A.find_word(a, print, step);
				break;
			}
			case 0:return 0;
			default: cout << "NO!FUCK YOU!STAY AWAY!\n"; break;
			}

		}
		catch (int a)
		{
			switch (a)
			{
			case 1:cout << "Stack error.\n"; break;
			case 2:cout << "Word not found.\n"; break;
			}
		}
	}
	return 0;
}
