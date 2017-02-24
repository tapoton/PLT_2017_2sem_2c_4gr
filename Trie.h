#include <iostream>
#define ALPH_SIZE 26
using namespace std;

struct Node {
    Node *parent;
    Node *children[ALPH_SIZE];
    char Ch;
    bool isLeaf;
};

class Trie {
public:
    Node *root;

    Trie();
    ~Trie();

    void insertWord(string word);
    //string searchBySubString(string subString);
    void removeWord();
};
