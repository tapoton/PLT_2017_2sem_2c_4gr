/* Класс "trie-дерево":

*/

#ifndef __TRIE_H__
#define __TRIE_H__

const int aLength = 26;
const char a = 'a';

struct node { //Каждый эл-т ветви хранит свой номер и кол-во гласных в слове; индекс и ключ определяют друг друга
	bool end; //Каждый не родитель - концевой
	bool parent; //Нужен для обхода в missionX, для случая с подсловами
	char key;
	int length;
	int vowQuant; //Кол-во гласных
	node* child[aLength];
};

class Trie {

private:
	node* Head;

public:
	//Вспомогательные:
	Trie();
	void init(node*);
	int countCons(node*);
	node* getHead() { return Head; };

	//Основные:
	void push(char*);
	int missionX(int, node*);

	void print(char* indent, bool last, node* root);
};
#endif // !__TRIE_H__
