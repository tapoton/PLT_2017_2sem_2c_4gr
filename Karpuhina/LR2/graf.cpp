#include "stdafx.h"
#include <vector> 
#include <stdio.h> 
#include <iostream> 
#include <conio.h> 
#include <stdlib.h> 


using namespace std;

void Graph(vector<vector<int>>&c, int n)
{

	// матрица смежности для ориентированного графа. Заполнение массива 0 и 1 
	for (int i = 0; i < n; i++)
	{
		vector<int> d;
		for (int j = 0; j<n; j++)
		{
			d.push_back(rand() % 2); //заполняю одномкрный вектор 
		}
		c.push_back(d); //заполняю одномкрными векторами двымерный вектор 
	}
	for (int i = 0; i<n; i++)
		c[i][i] = 0;
}

void dfs(vector<vector<int>> *graph, vector<bool> &visited, int v) //обход в глубину графа
{
	visited[v] = 1; 
	for (int i = 0; i < (*graph)[v].size(); i++)
	{
		if ((*graph)[v][i] > 0 && visited[i] == 0) //если можем попасть в какую-то вершину, идем
		{
			dfs(graph, visited, i);
		}
	}
}

void searchUnreachable(vector<vector<int>> *graph, int v)
{
	vector<bool> visited(graph->size());
	for (int i = 0; i < visited.size(); i++)
	{
		visited[i] = 0;
	}
	dfs(graph, visited, v);

	cout << "Unreachable vertices from " << v << " are:" << endl;

	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i] == 0)
		{
			cout << i << ' ';
		}
	}
}


void Print(vector<vector<int>> c, int n) //печать графа 
{
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			printf("%d ", c[i][j]);
		printf("\n");
	}
}

int main()
{
	vector<vector<int>> c; 
	int n;  
	cout << "Vvedite chislo vershin: ";  
	cin >> n;

	Graph(c, n);

	Print(c, n);



	int s; // Начальная вершина 
	cout << "Vvedite nachal'nyuy vershiny: "; 
	cin >> s;
	searchUnreachable(&c, s);
	system("pause");
	return 0;

}




