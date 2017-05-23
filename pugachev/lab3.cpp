#include <iostream>

using namespace std;

const int n = 6;

class Graph
{
public:
	struct node
	{
		int id;
		bool check;
		node* next;
	}*a = new node[n];

	Graph() {
	
		for (int i = 0; i < n; i++)
		{
			a[i].check = 1;
			a[i].id = i;
			a[i].next = NULL;
		}
		};
	 
	void init(int n)
	{
		cout << "Enter the graph every top connection, after enter -1\n";
		node* newn = new node;
		for (int i = 0; i < n; i++)
		{
			newn = &a[i];
			int number; cin >> number;
			
			while (number != -1)
			{
				node* p = new node;
				p->id = number;
				p->next = NULL;
				p->check = 0;
				newn->next = p;
				newn = newn->next;
				cin >> number;
				
			}
		}
		
	};
	void clearmark() {
		for (int i = 0; i < n; i++)
			a[i].check = 0;
	}
	void markup( int k)
	{
		
		node* newn = new node;
			newn = &a[k];
			newn->check = 1;
			while (newn->next != NULL)
			{
				newn = newn->next;
				if (!newn->check)
				{
					newn->check = 1;
					markup(newn->id);
				}
			}
	}
	
	void deleteOthers()
	{
		node* newn = new node;
		for (int i = 0; i < n; i++)
		{
			newn = &a[i];
			if (!newn->check)
			{
				deletespisok(newn->next);
				newn->next = NULL;
				
			}
		}
	}
	
	void deletespisok(node* newn)
	{
		if (newn->next != NULL)
			deletespisok(newn->next);
		delete newn;
	}
	
	
	void printstrok()
	{
		node* newsp = new node;
		for (int i = 0; i < n; i++)
		{
			newsp = &a[i];
			if(newsp->check)
			while (newsp != NULL)
				{
					
					cout << newsp->id << ' ';
					newsp = newsp->next;
				
				
			}cout << endl;
		}
	};
};


void main()
{
	
	Graph newgr;
	newgr.init(n);
	cout << "first goes number of top, then it's connections: \n";
	newgr.printstrok();
	newgr.clearmark();
	newgr.markup(0);
	newgr.deleteOthers();
	cout << "result\n";
	newgr.printstrok();
	system("pause");
}
// 1 -1 2 -1 0 3 -1 -1 2 -1 0 -1 