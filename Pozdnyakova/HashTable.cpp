#include <iostream>
#include <fstream>
using namespace std;

const int tableSize = 107;
const int wordLength = 30;

class HashTable {
private:
    unsigned int count[tableSize];
    char words[tableSize][wordLength];
    
public:
    HashTable()
    {
        for (unsigned int i = 0; i < tableSize; i++ )
        {
            count[i] = 0;
            words[i][1] = '\0';
        }
    }
    
    unsigned int HashFunction(const char *word)
    {
        unsigned int hash = 0;
        for(; *word; word++)
            hash+= (unsigned char)(*word);
        return hash % tableSize;
    }
    
    void insertValue (unsigned int HashValue, const char* key)
    {
        count[HashValue]=1;
        for(unsigned int i=0; *key; key++, i++) words[HashValue][i]= *key;
    }
    
    void increaseValue (unsigned int hashValue)
    {
        count[hashValue]++;
    }
    
    void hasKey (const char* key)
    {
        unsigned int hashValue = HashFunction(key);
        if (count[hashValue]==0) insertValue(hashValue, key);
            else increaseValue(hashValue);
    }
    
    void print ()
    {
        for (unsigned int i=0; i< tableSize; i++)
            if (count[i]!=0)
            {   cout <<"\nThe word '";
                unsigned int j=0;
                while (words[i][j]!='\0') {cout << words[i][j]; j++;}
                cout << "' repeats "<< count[i] << " times.";
            }
    }
    
};

int main() {
    cout << "\nEnter the path to the file: ";
    string path;
    getline (cin, path);
    ifstream inputFile (path);
    if (!inputFile) {
        cout << "\nError opening file! Try again.";
        return -1;
    }
    cout << "\nThe file was opened successfully.";
    
    HashTable hashTable;
    char buffer[wordLength] = "\0", ch = inputFile.get();
    unsigned int index=0;
    
    while (!inputFile.eof())
    {
        if (ch!=' ' && ch!=',' && ch!=',' && ch!=':' && ch!=';' && ch!='\n')
        {
            buffer[index]=ch;
            index++;
        } else {
            buffer[index+1]='\0';
            if (buffer[0]>'A' && buffer[0]<'z') hashTable.hasKey(buffer);
            
            for (unsigned int i=0; i< index; buffer[i]='\0', i++);
            index=0;
        }
        ch = inputFile.get();
    }
    hashTable.print();
    return 0;
}
