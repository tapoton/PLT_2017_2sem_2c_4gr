#include <iostream>
#include <string>

using namespace std;

const int hashTableSize = 17;

struct carInfo {
	string key;
	string mark;
	string name;
};

class hashTable {

	struct Node {
		carInfo info;
		Node* next;
	};
	
	Node* table[hashTableSize];

	void createNode(Node* current, string key, string mark, string name) {
		current->info.key = key;
		current->info.mark = mark;
		current->info.name = name;
		current->next = NULL;
	}

	int hash(string key) {
		int s = 0;
		for (unsigned int i = 0; i < key.length(); i++) {
			s += key[i];
		}
		return s % hashTableSize;
	}

	void show(Node *temp, unsigned int level = 0) {
		if (temp == NULL) {
			return;
		}
		for (unsigned int i = 0; i < level; cout << "\t", i++);
		cout << temp->info.key << endl;
		for (unsigned int i = 0; i < level; cout << "\t", i++);
		cout << temp->info.mark << endl;
		for (unsigned int i = 0; i < level; cout << "\t", i++);
		cout << temp->info.name << endl;

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

	carInfo search(string key) {
		carInfo car;
		int index = hash(key);
		Node* p = new Node;
		p = table[index];
		if (p) {
			while (p->info.key != key && p->next) {
				p = p->next;
			}
			if (p->next == NULL && p->info.key != key) {
				cout << "Wrong key!" << endl;
			}
			else {
				car.mark = p->info.mark;
				car.name = p->info.name;
			}
		}
		else cout << "Wrong key!" << endl;
		return car;
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
	cout << "Enter a number, a mark and a name:" << endl;

	while (true) {
		cin >> number;
		if (number == ".") break;
		else cin >> mark >> name;
		table.insertNode(number, mark, name);
	}

	table.show();

	carInfo car;
	cout << "\nEnter a key to search: ";
	cin >> number;
	car = table.search(number);
	if (car.mark.length() > 0 && car.name.length() > 0) {
		cout << "Mark: " << car.mark << endl;
		cout << "Name: " << car.name << endl;
	}
	system("pause");
}

// Example input:
/*
x750xh55 abc1 name1
j937tt86 abc2 name2
h649jj36 abc3 name3
j856ps12 abc4 name4
p098zb77 abc5 name5
k894kk30 abc6 name6
e909io77 abc7 name7
u234nj55 abc8 name8
*/
