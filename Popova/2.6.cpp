/*
2.6.
Set of records is given: title of the film, director, starring, 
plot. Find more information using the title.
*/

#include <iostream>
#include <string>

using namespace std;

const int HashTableSize = 5;


struct Film {
	string Name;
	string Director;
	string Starring;
	string Legend;
};

class HashTable {
        struct Node {
		Film film;
		Node* next;
	};
	Node* Cell[HashTableSize];
	int Hash(string key) {
		int h = 0;
		for (unsigned int i = 0; i < key.length(); i++) {
			h += key[i];
		}
		return h%HashTableSize;
	}
	void createNode(Node* curr, string name, string director, string starring, string legend) {
		curr->film.Name = name;
		curr->film.Director = director;
		curr->film.Starring = starring;
		curr->film.Legend = legend;
		curr->next = NULL;
	}
	void getInfo(Node curr) {
		cout << "\n Title: " << curr.film.Name;
		cout << "\n Directed by: " << curr.film.Director;
		cout << "\n Starring: " << curr.film.Starring;
		cout << "\n Plot: " << curr.film.Legend << endl;
	}
public:
	HashTable() {
		for (int i = 0; i < HashTableSize; i++) {
			Cell[i] = NULL;
		}
	}

	void insert(string key, string director, string starring, string legend)
	{
		int index = Hash(key);
		if (!Cell[index]) {
			Node *p = new Node;
			createNode(p, key, director, starring, legend);
			Cell[index] = p;
			return;
		}
		Node* p = Cell[index];
		while (p->next) {
			p = p->next;
		}
		Node* pull = new Node;
		createNode(pull, key, director, starring, legend);
		p->next = pull;
	}

	Node searchFilm(string key)
	{
		Node result;
		int index = Hash(key);
		Node* p = Cell[index];
		if (p) {
			while (p->film.Name != key && p->next) {
				p = p->next;
			}
			if (!p->next && p->film.Name != key) {
				cout << '\n' << key << " was not found\n";
			}
			else {
				cout << '\n' << key << " was found!\n";
				result.film.Name = p->film.Name;
				result.film.Director = p->film.Director;
				result.film.Starring = p->film.Starring;
				result.film.Legend = p->film.Legend;
				getInfo(result);

			}
		}
		else {
			cout <<'\n'<< key <<" was not found\n";
		}
		return result;
	}
};

void main() {
	HashTable table;
	table.insert("Pulp Fiction", "Tarantino", "Travolta, Thurman, Tarantino", "norm");
	table.insert("La La Land", "Chazelle", "Gosling, Stone, Legend", "norm");
	table.insert("Brigada", "Sidorov", "Bezrukov, Panin, Guseva", "norm");
	table.insert("Operation bI", "Gaidai", "Demianenko, Selezneva", "norm");
	table.insert("Fulp Piction", "Mikhalkov", "Bezrukov", "good");
	table.searchFilm("Fulp Piction");
	table.searchFilm("Titanic");
	table.searchFilm("Pulp Fiction");
	table.searchFilm("Brigada");
	system("pause");
}