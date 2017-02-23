#include "Trie.h"

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

Trie::insertWord(string word) {
    w = boost::algorithm::to_lower(word); //преобразование к нижнему регистру (во избежание неопределенностей с индексами)
    int n = w.length(); //длина слова
    int index; //номер очередного символа в алфавите (номер в табл. ASCII - 97)

    Node *parent = root;
    Node *current = root;

    for (int i = 0; i < n; i++) {
        index = (int) w[i] - 97;
        current = new Node;
        current->parent = parent;
        parent->isLeaf = false;
        current->Ch = w[i];
        parent->children[index] = current;
        parent = current;
    }
}

Trie::removeWord() {

}

Trie::searchBySeq() {

}
