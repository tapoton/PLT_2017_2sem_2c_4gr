#include <iostream>
#include <string>

using namespace std;

const int alphabet = 26;
const int max_word_length = 10;
const int first = 'a';

class TrieTree
{
	struct Node {
		char key;
		bool isEnd;
		Node* child[alphabet];
	};

	Node* head = NULL;

public:

	Node* getHead()
	{
		return head;
	}

	void createNode(Node *lead, int index, char c, bool check) {
		Node* follower = new Node;
		follower->isEnd = check;
		follower->key = c;
		for (unsigned int i = 0; i < alphabet; i++) {
			follower->child[i] = NULL;
		}
		lead->child[index] = follower;
	}

	void insertWord(string word) {
		if (head == NULL) {
			head = new Node;
			head->key = ' ';
			head->isEnd = false;
			for (unsigned int i = 0; i < alphabet; i++) {
				head->child[i] = NULL;
			}
		}

		Node* temp = head;

		for (unsigned int i = 0; i < word.length(); i++) {

			if (temp->child[word[i] - first] == NULL) {
				createNode(temp, word[i] - first, word[i], i + 1 == word.length() ? true : false);
			}
			else {
				if (i + 1 == word.length()) {
					temp->child[word[i] - first]->isEnd = true;
				}
			}

			temp = temp->child[word[i] - first];
		}
	}


	void show(Node *temp, unsigned int level = 0)
	{
		if (temp == NULL) {
			return;
		}
		for (unsigned int i = 1; i < level; i++) {
			cout << "\t";
		}
		cout << temp->key << endl;
		for (int i = 0; i < alphabet; i++) {
			show(temp->child[i], level + 1);
		}
	}

	int globalLevel = max_word_length;
	char str0[max_word_length];
	char str[max_word_length];

	void shortest(Node *temp, int level = 0) {
		if (temp == NULL) {
			return;
		}
		for (unsigned int i = 0; i < alphabet; i++) {
			if (temp->child[i] != NULL) {
				str0[level] = temp->child[i]->key;
				if (temp->child[i]->isEnd == true) {
					globalLevel = level;
					strncpy(str, str0, level + 1);
					return;
				}
				else {
					if (level < globalLevel) {
						shortest(temp->child[i], level + 1);
					}
					else return;
				}
			}
		}
		return;
	}

	void betterShort() {
		cout << "\nShortest: ";
		for (int i = 0; i <= globalLevel; i++) {
			cout << str[i];
		}
		cout << endl;
	}
};

void main() {
	TrieTree objTree;

	string str;
	cout << "Enter words: ";
	while (cin.peek() != '\n') {
		cin >> str;
		objTree.insertWord(str);
	}
	objTree.show(objTree.getHead());

	objTree.shortest(objTree.getHead());
	objTree.betterShort();

	system("pause");
}
