#include<iostream>
#include <fstream>

using namespace std;

void dfs(int N, int v, int **a, int counter, int *visited)
{
	visited[v] = counter;

	for (int i = 0; i < N; i++)
	{
		if (a[v][i] == 1 && visited[i] == 0)
			dfs(N, i, a, counter, visited);
	}

}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N, M;

	in >> N >> M;

	int **a = new int *[N];
	for (int i = 0; i<N; i++)
		a[i] = new int[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			a[i][j] = 0;

	int x, y;

	for (int i = 0; i < M; i++)
	{
		in >> x >> y;
		a[x][y] = 1;
		a[y][x] = 1;
	}

	for (int i = 0; i<N; i++)
	{
		cout << endl;
		for (int j = 0; j<N; j++)
			cout << a[i][j];
	}

	int counter = 0;
	int *visited = new int[N];

	for (int i = 0; i< N; i++)
		visited[i] = 0;
		
	for (int i = 0; i < N; i++)
		if (visited[i] == 0)
		{
			counter++;
			dfs(N, i, a, counter, visited);

		}

	out << counter<<endl;

	int*kol = new int[counter+1];
	for (int i = 1; i <=counter; i++)
		kol[i] = 0;

	for (int i = 1; i <= counter; i++)
		for (int j = 0; j<N; j++)
			if (visited[j] == i)
				kol[i] = kol[i] + 1;

	for (int i = 1; i <=counter; i++)
	{
		out << kol[i] << endl;
		for (int j = 0; j<N; j++)
			if (visited[j] == i)
				out << j;
		out << endl;
	}

	delete[] kol;
	delete[] visited;
	for (int i = 0; i < N; i++)
		delete[] a[i];

	out.close();
	in.close();
	return 0;
}
