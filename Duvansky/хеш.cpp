#include<iostream>
#include<string>
using namespace std;

struct family
{
	int kv;
	string fam;
};
class HashTable
{
	int size;
	struct Node
	{
		family inf;
		Node* next;
	};
	Node** mas;
public:
	HashTable(int k)
	{   
		size=k;
	
		mas=new Node*[size];
		for(int i=0;i<size;i++)
			mas[i]=NULL;
	}
	
	int Hash(int key)
	{
		return key%size;
	}
	void add(int kv,string f,Node** l)
	{
		int k=Hash(kv);
		Node*cur=new Node;
			cur->inf.kv=kv;
			cur->inf.fam=f;
			cur->next=NULL;
		if (l[k])
		{
			cur->next=l[k];
			l[k]=cur;
		}
		else l[k]=cur;
	}
	Node* poisk(int key)
	{
		int k=Hash(key);
		Node* cur=mas[k];
		if(!cur)
		{
			
		        return NULL;
		}
		while(cur->inf.kv!=key&&cur->next)
		{
			cur=cur->next;
		}
		if(cur->inf.kv!=key) 
		{
			return NULL;
			}
		return cur;

	}
	void showpoisk(Node* p)
	{
		
		if(p) 
		{
			cout<<p->inf.fam<<' '<<p->inf.kv<<endl;
		} else cout<<"element not found"<<endl;
	}
	void initial()
	{
		int k,schet=0;
		string f;
		cout<<"Vvedite familiyu i kvartiru, chtoby zakonchit, vmesto familii i kvartiri vvedite 0"<<endl;
		cin>>f>>k;
		while(f!="0")
		{
			schet++;
			if(schet==size)//esli tablica zapolnena, ee razmer uvelichivaetsya vdvoe 
			{
				
				size*=2;
				Node*cur=new Node;
				Node** m=new Node*[size];
				for(int i=0;i<size;i++)
			        m[i]=NULL;

				for(int i=0;i<size/2;i++)
				{
					cur=mas[i];
					while(cur)
					{
					add(cur->inf.kv,cur->inf.fam,m);
						cur=cur->next;
					}

				}
				
				mas=m;
				
			}
			add(k,f,mas);
			cout<<"Vvedite familiyu i kvartiru, chtoby zakonchit, vmesto familii vvedite 0"<<endl;
			cin>>f>>k;
		}
	}
	void Del(int key)
	{
		int k=Hash(key);
		Node* cur=mas[k];
		Node* a=poisk(key);
		if(!a) 
		{
			cout<<"element did not exist";
			return;}
		if(cur==a&&cur->next==NULL)
		{   
			delete cur;
			delete a;
			mas[k]=NULL;
			return;
		}
		if(cur==a&&cur->next!=NULL)
		{
			mas[k]=cur->next;
			delete cur;
			return;
		}
		while(cur->next!=a)
			cur=cur->next;
		cur->next=a->next;
		delete a;



	}
	
	
};
void main()
{
	HashTable table(100);
	table.initial();
	
	
	table.showpoisk(table.poisk(156));
	table.showpoisk(table.poisk(44));
	table.showpoisk(table.poisk(56));
	table.showpoisk(table.poisk(23));
	table.showpoisk(table.poisk(114));
	
	
	system("pause");

}