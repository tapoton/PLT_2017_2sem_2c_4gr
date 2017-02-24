#include "Trie.h"
#define INDEX  'a'

Trie::Trie() {
    root = new Node;
    root->isLeaf = true;
    root->parent = nullptr;
    for (int i = 0; i < ALPH_SIZE; i++) {
        root->children[i] = nullptr;
    }
}

Trie::~Trie() {
    delete root;
}

void Trie::insertWord(string word) {
    string w; //преобразование к нижнему регистру (во избежание неопределенностей с индексами)
    int n = w.length(); //длина слова
    for (int i = 0; i < n; i++)
        w[i] = tolower(word[i]);
    int index; //номер очередного символа в алфавите (номер в табл. ASCII - 97)

    Node *parent = root;
    Node *current = root;

    for (int i = 0; i < n; i++) {
        index = (int) w[i] - ((int) INDEX);
        if (parent->children[i] == nullptr) {
            current = new Node;
            current->parent = parent;
            parent->isLeaf = false;
            current->Ch = w[i];
            parent->children[index] = current;
        }
        parent = current;
    }
}

void Trie::removeWord() {

}

/*string Trie::searchBySubString(string subString) {

}*/
