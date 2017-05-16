#include <iostream>
#include<fstream>
#include<string>
using namespace std;
#define HASHTAB_SIZE 50
struct listnode {
	string key; // идентификатор
	int count; // кол-во появления слова
	listnode *next;
};
class hashTable {
	listnode **hashtab;
public:
	hashTable()
	{
		hashtab = new listnode *[HASHTAB_SIZE];
		int i;
		for (i = 0; i < HASHTAB_SIZE; i++)
			hashtab[i] = NULL;
	}
	int hashtab_hash(string key) {
		{
			int sum = 0;
			for (unsigned int i = 0; i < key.length(); i++)
			sum += key[i];
			return (sum % HASHTAB_SIZE);
		}
	}
	listnode* hashtab_lookup(string key) {
		listnode *p = hashtab[hashtab_hash(key)];
		while (p && p->key != key)
			p = p->next;
		return p;
	}
	void Insert(string key) {
		if (key != "\0") {
			int index = hashtab_hash(key);
			listnode*node = hashtab_lookup(key);
			if (!node) {
				listnode *NewNode = new listnode;
				if (NewNode)
				{
					NewNode->key = key;
					NewNode->count = 1;
					NewNode->next = hashtab[index];
					hashtab[index] = NewNode;
				}
			}
			else node->count++;
		}
	}
	void Print()
	{
		cout << "The resulting hash function:" << endl;
		int sum = 0;
		for (int i = 0; i < HASHTAB_SIZE; i++)
			if (hashtab[i]) {
				listnode *q;
				while (hashtab[i])
				{
					q = hashtab[i];
					sum += q->count;
					cout << q->key << " = " << q->count << endl;
					hashtab[i] = hashtab[i]->next;
				}
			}
	cout << "The total amount: " << sum << endl;
}
	};

	int main() {
		hashTable list;
		char symbol[] = "-=+/*,.;:'\"><(){}[]!^$@?|&";
		int const n = 20; int  m = sizeof(symbol) - 1;
		char ch_mas[n];

		ifstream File("code(Pascal).txt");
		if (!File)
			cout << "Error opening file" << endl;
		while (File >> ch_mas)
		{
			if (ch_mas[0] >= '0'&&ch_mas[0] <= '9')
				ch_mas[0] = '\0';
			for (int i = 0; ch_mas[i]; i++)
				for (int j = 0; j < m; j++)
					if (ch_mas[i] == symbol[j])
						ch_mas[i] = '\0';

			list.Insert(ch_mas);
		}


		list.Print();
		system("pause");
		return 0;
	}