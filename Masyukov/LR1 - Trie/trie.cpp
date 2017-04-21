#include <iostream>
#include <string>

using namespace std;

const int alphabet = 26;
const int first = 'a';

class TrieTree
{
	struct Node {
		char key;
		bool isEnd;
		Node* child[alphabet];
	};

	Node* head = NULL;
	
	string shortest(Node* temp, string current_word = "") {
		if (temp->isEnd) {
			return current_word;
		}
		string shortest_word;

		for (unsigned int i = 0; i < alphabet; i++) {
			if (temp->child[i] != NULL) {
				current_word += temp->child[i]->key;
				string word = shortest(temp->child[i], current_word);
				if (shortest_word.length() > word.length() || shortest_word.length() == 0) {
					shortest_word = word;
				}

				if (shortest_word.length() > 0) {
					current_word.erase(current_word.length() - 1, 1);
				}
			}
		}
		return shortest_word;
	}

	void show(Node *temp, unsigned int level = 0) {
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

public:

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


	void show() {
		show(head);
	}
	
	string shortest() {
		return shortest(head);
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
	objTree.show();

	cout << "Shortest = " << objTree.shortest() << endl;

	system("pause");
}
