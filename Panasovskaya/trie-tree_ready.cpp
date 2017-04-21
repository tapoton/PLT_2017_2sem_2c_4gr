
#include <iostream>
#include<string>

const int ALPHABET_LENGTH = 26;
const int NUMBER = 'a';
using namespace std;

struct Node
{
    char key;
    bool end_of_word = false;
    Node* parent = NULL;
    Node* children [ALPHABET_LENGTH] = {};
};

void Insert_Node (Node *&root, char *word)
{
    if (root == NULL)
    {
        root = new Node;
        root -> key = '\0';
        root -> parent = NULL;
        root -> end_of_word = false;
        for ( int i=0; i<ALPHABET_LENGTH; i++)
		root -> children[i] = NULL;
    }
    
    Node* currentNode = root;
    
    while (*word != '\0')
    {
        if (currentNode -> children[*word - NUMBER] == NULL)
        {
            currentNode -> children[*word - NUMBER] = new Node();
            currentNode -> children[*word - NUMBER] -> key = *word;
            currentNode -> children[*word - NUMBER] -> parent = currentNode;
            for ( int i=0; root -> children[i] != NULL; currentNode -> children[*word - NUMBER] -> children[i] = NULL, i++);
        }
        
        currentNode = currentNode -> children[*word - NUMBER];
        
        ++word;
    }
    currentNode -> end_of_word = true;
}

int Number_Of_Children(Node* root)
{
	Node* tree = root;
	int  count = 0;
	for (int i = 0; i < ALPHABET_LENGTH; i++)
		if (tree->children[i]) 
		  count++;
	return count;
}

bool Word_A(string Buff)
{
	int n=Buff.length(),w=0;
	for(int i=0;i<n;i++)
	   if(Buff[i]=='a')
	      w++;
    
    if(w==0)
      return 0;
    else return 1;
		
}

int Tree_A(Node *root,int &kol,string Buff=" ")
{
	Node*tree=root;
	
	if(tree->key) Buff+=tree->key;
	
	if(tree->end_of_word)
	{
		bool A=Word_A(Buff);
	       if (A==1)
	            kol++;
	    
	}
	if(tree && Number_Of_Children(tree)==1)
	{
	
	while (tree && Number_Of_Children(tree)==1)
	{
		int i=0;
		while(!tree->children[i])
		     i++;
		Buff+=tree->children[i]->key;
		if(tree->children[i]->end_of_word)
		{
			bool A = Word_A(Buff);
			if (A==1)
			 kol++;
		}
    	tree = tree->children[i];
	}
   }
	if (tree && Number_Of_Children(tree)>1)
	{
		int i=0;
	
		while(i<ALPHABET_LENGTH)
		{
			if (tree->children[i])
			     Tree_A(tree->children[i],kol,Buff);
			  i++;
		}
	}
	
 }
void  Print_Tree (string Buff,bool end, Node* root)
{
	Node*tree=root;
	cout << Buff;

    if (end)
    {
        cout << "+-";
        Buff+= " ";
    }
    else
    {
        cout << "|- ";
        Buff+= "| ";
    }
    
    cout << tree -> key << endl;
    
    for (int i = 0; i< ALPHABET_LENGTH; i++)
        if (tree -> children[i]!=NULL)
   Print_Tree(Buff, tree -> children[i] -> end_of_word, tree -> children[i]);
	
}
int main()
{
    int kol=0;
    Node* Tree = NULL;
    Insert_Node (Tree, "cat");
    Insert_Node (Tree, "canon");
    Insert_Node (Tree, "can");
    Insert_Node (Tree, "able");
    Insert_Node (Tree, "world");
    Insert_Node (Tree, "work");
    Insert_Node (Tree, "meal");
    Insert_Node (Tree, "mean");
    Insert_Node (Tree, "ten");
    Insert_Node (Tree, "tennis");
    cout << "  Tree: " << endl;
    Print_Tree(" ",true, Tree);
    cout<<endl;
    cout<<"Number of words with letter 'a':  "; 
	Tree_A(Tree,kol," ");
	cout<<kol;

    return 0;
}
