#include<iostream>
using namespace std;
 class Queue {
 public:
 	struct Node {
 		int info;
 		Node* next;
 	};
 
 	Node* head;
 
 	Queue() {
 		head = NULL;
 	}
 
 	bool is_empty() {
 		return head == NULL;
 	}
 
 	void push(int x) {
 		Node* p = new Node;
 		p->info = x;
 		p->next = NULL;
 
 		if (is_empty()) {
 			head = p;
 		}
 		else {
 			Node* cur = head;
 			while (cur->next) {
 				cur = cur->next;
 			}
 			cur->next = p;
 			cur = NULL;
 			delete cur;
 		}
 	}
 
 	int pop() {
		int k = head->info;
 		Node* p = head;
 		head = head->next;
 		p->next = NULL;
 		delete p;
 		return k;
	}
 };
 void make_graph(int**labirint,int n,int m,int**graph)
 {    
       
	  for (int i = 0; i < n; i++) { 
 	    for (int j = 0; j < m; j++) {
 			
 		  if (labirint[i][j] == 0) {
 					
 			for (int k = -1; k <= 1; k += 2) {
			int l;
 			for ( l = 1; j + l * k >= 0 && j + l * k < m && labirint[i][j+l*k] == 0; l++) {};//k=-1 - dvizhenie vlevo po labirintu, k=1 - dvizhenie vpravo po labirintu 
 			            if ( j + l * k >= 0 && j + l * k < m && labirint[i][j+l*k] == 2 ) {
 							graph[i*m+j][i*m+j + l * k] = 1;
 						}
 						else if (l - 1 != 0) {
 							graph[i*m+j][i*m+j + (l - 1) * k] = 1;
 						}
 
 			for (l = 1; i + l * k >= 0 && i + l * k < n && labirint[i + l * k][j] == 0; l++) {}; //k=-1 - dvizhenie vver po labirintu, k=1 - dvizhenie vniz po labirintu 
						if ( i + l * k >= 0 && i + l * k < n && labirint[i + l * k][j] == 2) {
 							graph[i*m+j][(i + l * k) * m + j] = 1;
 						}
 						else if (l - 1 != 0) {
 							graph[i*m+j][(i + (l - 1) * k) * m + j] = 1;
 						}
 					}
 				}
 			}
 		}
 }

 void make_labirint_2(int **labirint,int n,int m, int *labirint_2)
 {
	 for(int i=0;i<n;i++)
		 for(int j=0;j<m;j++)
			 labirint_2[i*m+j]=labirint[i][j];
 }
 int search(int*labirint_2,int**graph,bool*visited,int n,int m)
 {
 		int current = 0;
 		int* p;
 		p = new int[n*m];
 		p[current] = 0;
 		Queue queue;
 		queue.push(current);
 		visited[current] = true;
 
 		while (!queue.is_empty()) {
 			current = queue.pop();
			int i=0,j=0;
 			
			if (labirint_2[current] == 2) 
 				break;
 			
 			for (int i = 0; i < n*m; i++) {
 				if (graph[current][i] && current != i && !visited[i]) {
 					queue.push(i);
 					visited[i] = true;
 					p[i] = p[current] + 1;
 				}
 			}
 		}
 		return p[current];
 	}
 


	void main()
	{    
         int** labirint;
		 
 	     int n, m; 
 	     int** graph; 
 	     bool* visited; 
		
		 cin>>n>>m;
		  int* Labirint_2=new int[m*n];
		 labirint = new int*[n];
        for (int i=0;i<n;i++)
			labirint[i]=new int[m];
 		graph = new int*[n*m];
 		visited = new bool[n*m];
 		for (int i = 0; i < n*m; i++) {
 			graph[i] = new int[n*m];
 			visited[i] = false;
 		}
		for (int i = 0; i < n*m; i++) {
 			for (int j = 0; j < n*m; j++) {
 				graph[i][j] = 0;
 			}
 		}
		for (int i = 0; i < n; i++) {
 			for (int j = 0; j < m; j++) {
 				cin >> labirint[i][j];
 			}
 		}
		
		

		make_graph(labirint,n,m,graph);
		
		
		make_labirint_2(labirint,n,m,Labirint_2);
		for(int i=0;i<n*m;i++)
			{for(int j=0;j<n*m;j++)
			cout<<graph[i][j]<<" ";
		    cout<<endl;
		}
		

		cout<<endl<<"minimalnoe kol-vo naklonov : "<<search(Labirint_2,graph,visited,n,m)<<" ";

		system("pause");
	}