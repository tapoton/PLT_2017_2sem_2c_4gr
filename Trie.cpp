#include "Trie.h"

Trie::Trie() {
    root = new Node;
    root->isLeaf = true;
    root->parent = NULL;
}

Trie::~Trie() {
    delete root;
}

Trie::insertWord(string word) {
    w = boost::algorithm::to_lower(word); //преобразование к нижнему регистру (для единообразия)
    int n = w.length(); //длина слова
    int index = (int) w[0] - 97; //номер очередного символа в алфавите (номер в табл. ASCII - 97)

}

Trie::removeWord() {

}

Trie::searchBySeq() {

}
