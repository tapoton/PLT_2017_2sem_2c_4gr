#include <iostream>
#define ALPH_SIZE (26)
using namespace std;

struct Node {
    Node *parent;
    Node *children[ALPH_SIZE];
    bool isLeaf;
};

class Trie {
private:
    Node *root;
public:
    Trie();
    ~Trie();

    void insertWord(string word);
    string searchBySeq();
    void removeWord();
};
