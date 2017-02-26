#include <iostream>
const int ALPHABET_LENGTH = 26;
const int NUMBER = 'a';

struct Node
{
    char key;
    bool endOfWord = false;
    Node* parent = nullptr;
    Node* children [ALPHABET_LENGTH] = {};
};


void addNode (Node *&root, char *word)
{
    if (root == nullptr)
    {
        root = new Node;
        root -> key = '\0';
        root -> parent = nullptr;
        root -> endOfWord = false;
        for (unsigned int i=0; i<ALPHABET_LENGTH; root -> children[i] = nullptr, i++);
    }
    
    Node* currentNode = root;
    
    while (*word != '\0')
    {
        if (currentNode -> children[*word - NUMBER] == nullptr)
        {
            currentNode -> children[*word - NUMBER] = new Node();
            currentNode -> children[*word - NUMBER] -> key = *word;
            currentNode -> children[*word - NUMBER] -> parent = currentNode;
            for (unsigned int i=0; root -> children[i] != nullptr; currentNode -> children[*word - NUMBER] -> children[i] = nullptr, i++);
        }
        
        currentNode = currentNode -> children[*word - NUMBER];
        
        ++word;
    }
    currentNode -> endOfWord = true;
}


void printPretty (std::string indent, bool last, Node* root)
{
    std::cout << indent;

    if (last)
    {
        std::cout << "+-";
        indent+= " ";
    }
    else
    {
        std::cout << "|- ";
        indent+= "| ";
    }
    
    std::cout << root -> key << std::endl;
    
    for (unsigned int i = 0; i< ALPHABET_LENGTH; i++)
        if (root -> children[i]!=nullptr)
            printPretty(indent, root -> children[i] -> endOfWord, root -> children[i]);
}


char* wordReverse (char buf[])
{
    char* tmp = buf;
    int numberOfLetters=0;
    while (*tmp >= 'a' && *tmp <= 'z')
    {
        numberOfLetters++;
        tmp++;
    }
    
    char *change = new char[numberOfLetters];
    for (unsigned int i=0; i<numberOfLetters; i++)
        change[i]= buf [numberOfLetters-i-1];
    change[numberOfLetters] = '\0';
    
    return change;
}


void inverseTree (Node* basicTree, Node*& newTree)
{
    static int index=0;
    static char buffer[10];
    if (basicTree==nullptr)
    {
        std::cout<<"\nError: the basic tree is empty!";
        return;
    }
    
    for (unsigned int i=0; i<ALPHABET_LENGTH; i++)
    { if (basicTree -> children[i]!= nullptr)
        {
            
            buffer[index] = basicTree -> children[i] -> key;
            
            if (!basicTree -> children[i] -> endOfWord)
            {
                index++;
                inverseTree (basicTree -> children[i], newTree);
        
            }
            else
            {
                char* word = wordReverse(buffer);
//                std::cout << "\nWord-reverse is "<< word;
                addNode(newTree, word);
                buffer[index]='\0';
            }
        }
    }
    index--;
    buffer[index]='\0';
}

int main()
{
    Node* basicTree = nullptr;
    addNode (basicTree, "meat");
    addNode (basicTree, "tea");
    addNode (basicTree, "ten");
    addNode (basicTree, "eight");
    addNode (basicTree, "meal");
    addNode (basicTree, "mel");
    std::cout << "\nBasicTree: " << std::endl;
    printPretty("", true, basicTree);
    
    Node* newTree = nullptr;
    std::cout << "\nInverseTree: " << std::endl;
    inverseTree (basicTree, newTree);
//    std::cout << std::endl;
    printPretty("", true, newTree);

    return 0;
}
