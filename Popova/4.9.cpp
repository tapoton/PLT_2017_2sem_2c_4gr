#include <iostream>

using namespace std;

void walk(int S,int N,bool* visited, bool** graph) {
	visited[S] = true;
	for (int i = 0; i < N; i++) {
		if (graph[S][i]) {
			if (!visited[i]) {
				walk(i, N, visited, graph);
			}
		}
	}
	return;
}

int count_vertices(int N, bool* visited) {
	int count = 0;
	for (int i = 0; i < N; i++) {
		if (visited[i]) {
			count++;
		}
	}
	return count;
}

void main() {
	int N;
	cout << "Enter the number of vertices: ";
	cin >> N;
	bool** graph = new bool*[N];
	for (int i = 0; i < N; i++) {
		graph[i] = new bool[N];
	}
	cout << "\nEnter the matrix:\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> graph[i][j];
		}
		cout << '\n';
	}
	bool* visited = new bool[N];
	for (int i = 0; i < N; i++) {
		visited[i] = false;
	}
	cout << "\nEnter the vertex : ";
	int S;
	cin >> S;
	walk(S, N, visited, graph);
	cout << "\nThe number of vertices in one connected component with " << S << " : " << count_vertices(N, visited) << "\n";
	system ("pause");
}