// Example input:
// x750xh55 abc1 name1 j937tt86 abc2 name2 h649jj36 abc3 name3 j856ps12 abc4 name4 p098zb77 abc5 name5 k894kk30 abc6 name6 e909io77 abc7 name7 u234nj55 abc8 name8

#include <iostream>
#include <string>

using namespace std;

const int hashTableSize = 17;
const int keySize = 8;

class hashTable {

	struct Node {
		string key;
		string mark;
		string name;
		Node* next;
	};
	
	Node* table[hashTableSize];

	void createNode(Node* current, string key, string mark, string name) {
		current->key = key;
		current->mark = mark;
		current->name = name;
		current->next = NULL;
	}

	int hash(string key) {
		int s = 0;
		for (int i = 0; i < keySize; i++) {
			s += key[i];
		}
		return s % hashTableSize;
	}

	void show(Node *temp, unsigned int level = 0) {
		if (temp == NULL) {
			return;
		}
		for (unsigned int i = 0; i < level; cout << "\t", i++);
		cout << temp->key << endl;
		for (unsigned int i = 0; i < level; cout << "\t", i++);
		cout << temp->mark << endl;
		for (unsigned int i = 0; i < level; cout << "\t", i++);
		cout << temp->name << endl;

		show(temp->next, level + 1);
		cout << endl;
	}


public:

	hashTable() {
		for (int i = 0; i < hashTableSize; i++) {
			table[i] = NULL;
		}
	}

	void insertNode(string key, string mark, string name) {
		int index = hash(key);
		if (table[index]) {
			Node* p = new Node;
			p = table[index];
			while (p->next != NULL) {
				p = p->next;
			}
			Node* child = new Node;
			createNode(child, key, mark, name);
			p->next = child;
		}
		else {
			Node* p = new Node;
			createNode(p, key, mark, name);
			table[index] = p;
		}
	}

	void search(string key) {
		string mark, name;
		int index = hash(key);
		Node* p = new Node;
		p = table[index];
		while (p->key != key && p->next) {
			p = p->next;
		}
		if (p->next == NULL && p->key != key) {
			cout << "Wrong key!" << endl;
		}
		else {
			mark = p->mark;
			name = p->name;
			cout << "Mark: " << mark << endl;
			cout << "Name: " << name << endl;
		}
	}
	
	void show() {
		cout << endl;
		for (int i = 0; i < hashTableSize; i++) {
			// cout << "hash(key) = " << i << endl;
			// cout << endl;
			show(table[i]);
		}
	}
};

void main() {
	hashTable table;

	string number, mark, name;
	cout << "Enter a number (" << keySize << " symbols), a mark and a name:" << endl;
	while (cin.peek() != '\n') {
		cin >> number >> mark >> name;
		if (number.length() != keySize) {
			cout << "Wrong number! (" << keySize << " symbols)" << endl;
		}
		else {
			table.insertNode(number, mark, name);
		}
	}

	table.show();

	cout << "\nEnter a key to search: ";
	cin >> number;
	if (number.length() != keySize) {
		cout << "Wrong key! (" << keySize << " symbols)" << endl;
	}
	else {
		table.search(number);
	}

	system("pause");
}
