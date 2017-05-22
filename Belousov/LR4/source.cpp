/*
Дан ориентированный взвешенный граф. Для него вам необходимо найти кратчайшее расстояние от вершины S до вершины F.
Выведите искомое кратчайшее расстояние или -1, если пути между указанными вершинами не существует.
*/
#include<iostream> 
#include<fstream> 

using namespace std;

char fname[] = "matr.txt";

void readgraph(char *fname, int &n, int &start, int &finish, double **&a) {
	ifstream f(fname);
	f >> n; f >> start; f >> finish;
	a = new double*[n];
	for (int i = 0; i < n; i++) {
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
			f >> a[i][j];
	}
	cout<<n<<' '<<start<<' '<<finish<<' '<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout<< a[i][j]<<"\t";
		cout<<endl;
	}

	f.close();
}

void Dijkstra(int st, int finish, int n, double** &w)
{
	bool* visited = new bool[n];
	double* D = new double[n];//по окончании работы алгоритма равно длине кратчайшего пути из a до вершины u 
	double max = 0, max_w = 0;
	for (int i = 0; i<n; i++)
	{
		max = 0;
		for (int j = 0; j<n; j++)
		{
			if (w[i][j]>max) max = w[i][j];
		}
		max_w += max;
	}
	max_w += 1.0;//бесконечность для поиска 
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
			if (w[i][j]<-0.5) w[i][j] = max_w;
	for (int i = 0; i<n; i++)
	{
		D[i] = max_w;
		visited[i] = false;
	}
	D[st] = 0;
	double min_dist = 0;
	int min_ver = st;
	while (min_dist < max_w)
	{
		int i = min_ver;
		visited[i] = true;
		for (int j = 0; j < n; ++j)
			if (D[i] + w[i][j] < D[j])
				D[j] = D[i] + w[i][j];
		min_dist = max_w;
		for (int j = 0; j < n; ++j)
			if (!visited[j] && D[j] < min_dist)
			{
				min_dist = D[j];
				min_ver = j;
			}
	}

	cout<<"Distance:\t\n";
	
	if (D[finish] != max_w)
		cout<<st<<" -> "<<finish<<" = "<<D[finish]<<endl;
	else
		cout<<st<<" -> "<<finish<<" = "<<"-1"<<endl;
	delete[]D;
	delete[]visited;

}

int main()
{
	int n = 0, start = 0, finish = 0;
	double** a;
	readgraph(fname, n, start, finish, a);
	Dijkstra(start, finish, n, a);
	for (int j = 0; j<n; j++)
		delete a[j];
	delete a;
	system("pause");
	return 0;
}

/*Пример данных в файле:
4  0  3
0  1 -1 -1
2  0  1  3
4  1  0  1
1  3  1  0

4 - количество вершин
0 - номер начальной вершины
3 - номер конечной вершины
*/
