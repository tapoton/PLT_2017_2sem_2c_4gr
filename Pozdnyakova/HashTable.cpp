#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const unsigned int tableSize = 53;

struct Node
{
    unsigned int count;
    string word;
    Node* next;
};

class HashTable
{
private:
    Node* list[tableSize];
    
    unsigned int hashFunction(string word)
    {
        unsigned int hash =0;
        for (unsigned int i=0; i < word.length(); i++) hash+=(char)word[i];
        return hash%tableSize;
    }
    
    void addNew (unsigned int hash, string key)
    {
        Node* newNode = new Node;
        newNode->count = 1;
        newNode->word = key;
        newNode->next = list[hash];
        list[hash] = newNode;
    }
    
    Node* searchWord (unsigned int hash, string key)
    {
        Node* temp = list[hash];
        while (temp)
        {
            if (temp->word == key) return temp;
            temp=temp->next;
        }
        return nullptr;
    }
    
public:
    
    void addNode (string key)
    {
        unsigned int hash = hashFunction(key);
        Node* found = searchWord(hash, key);
        if (!found) addNew(hash, key);
            else found -> count++;
    }
    
    void info (Node* current)
    {
        cout << "\nThe word '" << current->word << "' repeats ";
        cout << current->count << " time(s)."<< endl;
    }
    
    void print ()
    {
        for (unsigned int i =0; i< tableSize; i++)
            if (list[i])
            {
                Node* tmp = list[i];
                cout << "\nHash: " << i;
                while (tmp)
                {
                    info(tmp);
                    tmp=tmp -> next;
                }
            }
    }
};

bool onlyLetters (string buffer)
{
    unsigned int i=0;
    while (i< buffer.length())
    {
        if (buffer[i]<'A' || (buffer[i]>'Z' && buffer[i]<'a') || buffer[i]>'z') return false;
        i++;
    }
    return true;
}

int main() {
    cout << "\nEnter the path to the file: " << endl;
    string path;
    getline (cin, path);
    ifstream inputFile (path);
    if (!inputFile) {
        cout << "\nError opening file! Try again."<< endl;
        return -1;
    }
    cout << "\nThe file was opened successfully." << endl;
    
    HashTable table;
    string buffer = "";
    char ch = inputFile.get();;
    
    while (!inputFile.eof())
    {
        if ((ch>='A' && ch<='Z') || (ch>='a' && ch<='z')) buffer= buffer + ch;
        else
        {
            if (!buffer.empty() && onlyLetters(buffer)) table.addNode(buffer);
            buffer.clear();
        }
        ch = inputFile.get();
    }
    if (!buffer.empty() && onlyLetters(buffer)) table.addNode(buffer);
    buffer.clear();

    table.print();
    return 0;
}
