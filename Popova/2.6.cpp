/*
2.6.
Set of records is given: title of the film, director, starring, 
plot. Find more information using the title.
*/

#include <iostream>
#include <string>

using namespace std;

const int HashTableSize = 5;


class Node {
	friend class HashTable;
	string Name;
	string Director;
	string Starring;
	string Legend;
	Node* next;
public:
	Node() {};
	Node (string name, string director, string starring, string legend) {
		Name = name;
		Director = director;
		Starring = starring;
		Legend = legend;
		next = NULL;
	}
	void getInfo() {
		cout << "\n Title: " << Name;
		cout << "\n Directed by: " << Director;
		cout << "\n Starring: " << Starring;
		cout << "\n Plot: " << Legend << endl;
	}
};

class HashTable {
	Node* Cell[HashTableSize];
	int Hash(string key) {
		int h = 0;
		for (unsigned int i = 0; i < key.length(); i++) {
			h += key[i];
		}
		return h%HashTableSize;
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
			Cell[index] = new Node(key, director, starring, legend);
			return;
		}
		Node* p = Cell[index];
		while (p->next) {
			p = p->next;
		}
		p->next = new Node(key, director, starring, legend);
	}

	Node searchFilm(string key)
	{
		Node film;
		int index = Hash(key);
		Node* p = Cell[index];
		if (p) {
			while (p->Name != key && p->next) {
				p = p->next;
			}
			if (!p->next && p->Name != key) {
				cout << '\n' << key << " was not found\n";
			}
			else {
				cout << '\n' << key << " was found!\n";
				film.Name = p->Name;
				film.Director = p->Director;
				film.Starring = p->Starring;
				film.Legend = p->Legend;
				film.getInfo();
			}
		}
		else {
			cout <<'\n'<< key <<" was not found\n";
		}
		return film;
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