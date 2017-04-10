#include<iostream>

using namespace std;

class Maze {

	int* maze; // a given maze represented as an array
	int n, m; // size of the maze
	bool** graph; // graph for the given maze
	bool** visited; // graph of visited vertices

	int search(bool &t, int current = 0) {
		if (maze[current] == 2) {
			return 0;
		}

		bool found = false;
		int shortest = 0;
		for (int i = 0; i < n*m; i++) {
			int S = 0;
			int h = 0;
			if (graph[current][i] && !visited[current][i] && i != current) {
				h = i - current;
			}

			if (h != 0) {
				int current1 = current;
				while (current1 + h >= 0 && current1 + h < n*m && graph[current1][current1 + h]) {
					visited[current1][current1 + h] = visited[current1 + h][current1] = true;
					current1 += h;
					if (maze[current1] == 2) {
						found = true;
						break;
					}
				}
				S++;
				S += search(found, current1);
				visited[current1][current1 - h] = visited[current1 - h][current1] = false;
			}
			
			if (S != 0 && (shortest > S || shortest == 0)) {
				shortest = S;
			}
		}
		if (!found && current != 0) {
			shortest--;
		}
		t = found;
		return shortest;
	}

public:

	void init(int initN, int initM) {
		n = initN;
		m = initM;
		maze = new int[n*m];

		graph = new bool*[n*m];
		visited = new bool*[n*m];
		for (int i = 0; i < n*m; i++) {
			graph[i] = new bool[n*m];
			visited[i] = new bool[n*m];
		}

		for (int i = 0; i < n*m; i++) {
			for (int j = 0; j < n*m; j++) {
				graph[i][j] = false;
				visited[i][j] = false;
			}
		}
	}

	void input() {
		for (int i = 0; i < n*m; i++) {
			cin >> maze[i];
		}

		for (int i = 0; i < n*m; i++) { // Check if there is a path from the i-th point in the maze to the ...
			if (maze[i] != 1) {
				if (i + 1 < n*m && (i + 1) % m != 0 && maze[i + 1] != 1) { // ... right
					graph[i][i + 1] = graph[i + 1][i] = true;
				}
				if (i + m < n*m && maze[i + m] != 1) { // ... down
					graph[i][i + m] = graph[i + m][i] = true;
				}
			}
		}
	}
	
	int search() {
		bool t = false;
		return search(t);
	}
};

int main() {

	Maze objMaze;

	int N, M;
	cin >> N >> M;
	objMaze.init(N, M);
	objMaze.input();

	cout << objMaze.search() << endl;

	system("pause");
	return 0;
}
