#include<iostream>
using namespace std;
struct Node
{
	int value;
	Node* Next, *Prev;

};

class List
{
private:
	Node *Head, *Tail;
public:
	List()
	{
		Head = NULL;
		Tail = NULL;
	}
	~List()
	{
		while (Head)
		{
			Tail = Head->Next;
			delete Head;
			Head = Tail;
		}
	}
	void Add(int a)
	{
		Node *pv = new Node;
		pv->Next = NULL;
		pv->value = a;

		if (Head != NULL)
		{
			pv->Prev = Tail;
			Tail->Next = pv;
			Tail = pv;
		}
		else
		{
			pv->Prev = NULL;
			Head = Tail = pv;
		}
	}
	void Show()
	{
		Node*pv = Tail;
		while (pv)
		{
			cout << pv->value << " ";
			pv = pv->Prev;
		}
		cout << endl;

	}
};
int** Create_matr(int n)
{
	int **a;
	a = new int*[n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];
	return a;
}
void Inint_matr(int **a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			a[i][j] = 0;
		}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			cin >> a[i][j];
			a[j][i] = a[i][j];
		}
}

void Print_matr(int **a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
}

int Floyd_Yo(int **a, int** h, int n, int b, int c)
{
	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
				if ((a[i][k] * a[k][j] != 0) && (i != j))
				{
					if ((a[i][k] + a[k][j] < a[i][j]) || (a[i][j] == 0))
					{
						a[i][j] = a[i][k] + a[k][j];
						h[i][j] = k;
						
					}
				}
			}

	}

	if (a[b][c]>0)

		return a[b][c];

}


void main()
{
	setlocale(LC_ALL, "Russian");
	List Head;

	int n;
	cout << "введите количество вершин ";
	cin >> n;
	while ((n < 1) && (n > 100))
	{
		cout << "Ошибка, неверное количество вершин ";
		cin >> n;
	};

	int **way;
	way = Create_matr(n);

	int**a;
	a = Create_matr(n);

	Inint_matr(a, n);


	int b;
	int c;
	cout << "введите номера вершин ";
	cin >> b;
	cin >> c;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			way[i][j] = b;

	Print_matr(a, n);


	cout <<"Кратчайший путь от вершины "<<b<<" до "<<c<<" : "<<Floyd_Yo(a, way, n, b, c) <<endl;

	cout << endl;
	
	Print_matr(a, n);
	cout << endl;
	Print_matr(way, n);

	int k = c;
	cout << "Путь: ";
	while (k != b)
	{
		Head.Add(k);
		k = way[b][k];
	}
	Head.Add(k);

	Head.Show();

	system("pause");
}
