#include <iostream>
using namespace std;
struct edge
{
	int first, second;
	edge *next;
	bool lable;
};
class Graph {
	edge *P = NULL;
public:
	void input(int m) {
		for (int i = 0; i < m; i++)
		{
			edge *P1 = new edge;
			cin >> P1->first;
			cin >> P1->second;
			P1->lable = true;
			P1->next = P;
			P = P1;
		}
	}
	bool check(int *mas, int n, int A)
	{
		int i = 0;
		bool t = mas[i] != A;
		while (i < n && t) {
			t = mas[i] != A;
			i++;
		}
		return t;
	}
	void search(int top, int *Arr, int n) {
		edge*Ptr = P;
		static int i = -1;
		if (check(Arr, n, top)) {
			Arr[++i] = top;
			while (Ptr != NULL) {
				if (Ptr->first == top) {
					Ptr->lable = false;
					search(Ptr->second, Arr,n);
				}
				Ptr = Ptr->next;
			}
		}
	}
bool proverka(int *mas, int n, int k) {
		int i = 0;
		bool t = mas[i] != k;
		while (i < n &&t) {
			t = mas[i] != k;
			i++;
		}
		return t;
	}

};
int main() {
	setlocale(LC_ALL, "Russian");
	int n, m, A,k=0;
	cout << "Введите количество вершин"<<" ";
	cin >> n;
	cout << "\n Введите количество ребер"<<" ";
	cin >> m;
	int *Array = new int[n];
	Graph *graph = new Graph;
	graph->input(m);
	cout << "Введите номер вершины"<<" ";
	cin >> A;
	graph->search(A, Array, n);
	cout << "\n Вершины, недостижимые из данной вершины: \n";
	for (int i = 0; i < n; i++) {
		k = i + 1;
		if(graph->proverka(Array,n,k))
		cout << k<< " ";
	}
	system("pause");
	return 0;
}