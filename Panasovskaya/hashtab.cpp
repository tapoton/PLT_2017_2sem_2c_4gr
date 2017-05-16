#include<windows.h>
#include<iostream>  
#include <string>

#define Hash_Size 7
using namespace std;

class HashTable 
{
  private:
    struct Node 
	{
	       string Title;
   	       string Producer;
	       string Actors;
	       string Content;

		Node* next;
	};
	struct  Node* hashtab[Hash_Size];
	
	int Hash(string key) 
	{
		int h = 0;
		for ( int i = 0; i < key.length(); i++) 
			h += key[i];
		
		return h%Hash_Size;
	}
		
	
public:
	 HashTable () 
	{
		for (int i = 0; i < Hash_Size; i++) 
			hashtab[i] = NULL;
		
	}
	void createNode(Node* hashtab, string title, string producer, string actors, string content) 
	{
		hashtab->Title = title;
		hashtab->Producer = producer;
		hashtab->Actors = actors;
		hashtab->Content = content;
		hashtab->next = NULL;
	}
	void getNode(Node t) 
	{   
	    
		cout << "\n Title: " << t.Title;
		cout << "\n Producer: " << t.Producer;
		cout << "\n Actors: " << t.Actors;
		cout << "\n Content: " << t.Content << endl;
	
	}

	void insertFilm(string key, string producer, string actors, string content)
	{
		int index = Hash(key);
		if (hashtab[index]) 
		{
			Node* p = new Node;
			p = hashtab[index];
			while (p->next != NULL) 
				p = p->next;
			Node* child = new Node;
			createNode(child, key,producer, actors, content );
			p->next=child;
		}
		else 
		{
		    Node* p = new Node;
			createNode(p, key, producer, actors, content);
			hashtab[index] = p;
		}
       
	}


	Node searchFilm(string key)
	{
    	Node film;
    	
		int index = Hash(key);
		Node* a = new Node;
		a = hashtab[index];
		if(a) 
		{
			while (a->Title != key && a->next) 		
				a = a->next;
			
			if (a->Title != key && a->next == NULL) 	
				cout << " : There is no such film\n" ;
			
			else 
			{    
				film.Title = a->Title;
				film.Producer = a->Producer;
				film.Actors = a->Actors;
				film.Content = a->Content;
				getNode(film);
			}	
		}
		else cout << " : There is no such film.\n";
		
		return film;
	}
	
};

int  main() 
{
	HashTable Htable;
    Htable.insertFilm("Rogue one", "Gareth Edwards", "Felicity Jones,Diego Luna,Alan Tudyk", "fantasy");
	Htable.insertFilm("Personal shopper", "Olivier Assays", "Kristen Stewart,Lars Eidinger", "drama");
	Htable.insertFilm("Jackie", "Pablo Larrian", "Natalie Portman,John Hurt", "history");
	Htable.insertFilm("Jacike", " Larrian", " Portman, Hurt", "history");
	Htable.insertFilm("Miss Sloane", "John Madden", "John Lithgow, Mark Strong", "triller");
	Htable.insertFilm("Hidden Figures", "Theodore Melfi", "Taraji P. Henson,Octavia Spencer", "drama");
    Htable.insertFilm("Moonlight ", "Barry Jenkins", "Ashton Sanders,Naomie Harris", "drama");
	Htable.insertFilm("The whole truth", "Courtney Hunt", " Keanu Reeves,Rene Zellweger, ", "triller");
	
	Htable.searchFilm("Rogue one");
	Htable.searchFilm("Miss Sloane");
	Htable.searchFilm("Jackie"); 
	Htable.searchFilm("Jacike");
	return 0;
}
