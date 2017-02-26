#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

const int ALPHABET_SIZE = 26;

struct Node {
	bool is_end = false;
	int prefix_count = 0;
	Node* child[ALPHABET_SIZE] = {};
};


void insert(Node *& root, string word) {
	Node *current = root;
	current->prefix_count++;
	for (unsigned int i = 0; i < word.length(); i++) {
		int letter = (int)word[i] - (int)'a';
		if (current->child[letter] == NULL) {
			current->child[letter] = new Node;
		}
		current->child[letter]->prefix_count++;
		current = current->child[letter];
	}
	current->is_end = true;
}

void print(string prefix, Node const& node) {
	if (node.is_end) {
		cout << prefix<<'\n';
	}
	for (char index = 0; index < ALPHABET_SIZE; ++index) {
		char next = 'a' + index;
		Node const* Child = node.child[index];
		if (Child) {
			prefix.push_back(next);
			print(prefix, *Child);
			prefix.pop_back();
		}
	}
}

bool is_consist(string set, string word) {
	return (word.find_first_not_of(set) == string::npos);
}

void search (string prefix, string set, Node const& node) {
	if (is_consist(set, prefix) && node.is_end) {
		cout << prefix << " consists of letters from the set\n";
	}
	for (char index = 0; index < ALPHABET_SIZE; ++index) {
		char next = 'a' + index;
		Node const* Child = node.child[index];
		if (Child) {
			prefix.push_back(next);
			search (prefix,set, *Child);
			prefix.pop_back();
		}
	}
}

void main()
{
	Node* Dict = new Node;
	insert(Dict, "is");
	insert(Dict, "go");
	insert(Dict, "it");
	insert(Dict, "cap");
	insert(Dict, "car");
	insert(Dict, "if");
	insert(Dict, "cdr");
	print("", *Dict);
	string Set = "crda";
	//cout << "enter the set of numbers\n";
	//cin >> Set;
	cout << "set of letters: "<< Set << endl;
	search("", Set, *Dict);
	system("pause");
}
	