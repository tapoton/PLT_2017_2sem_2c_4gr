#include<iostream>

using namespace std;

class Maze;
class Queue {

	struct Node {
		int number;
		Node* next;
	};

	Node* head;

	Queue() {
		head = NULL;
	}

	bool empty() {
		return head == NULL;
	}

	void push(int x) {
		Node* temp = new Node;
		temp->number = x;
		temp->next = NULL;

		if (empty()) {
			head = temp;
		}
		else {
			Node* p = head;
			while (p->next) {
				p = p->next;
			}
			p->next = temp;
			p = NULL;
			delete p;
		}
	}

	int pop() {
		int temp = head->number;
		Node* p = head;
		head = head->next;
		p->next = NULL;
		delete p;
		return temp;
	}

public:
	friend class Maze;
};

class Maze {

	int* maze; // a given maze represented as an array
	int n, m; // size of the maze
	bool** graph; // graph for the given maze
	bool* visited; // array of visited vertices

public:

	void init(int initN, int initM) {
		n = initN;
		m = initM;
		maze = new int[n*m];

		graph = new bool*[n*m];
		visited = new bool[n*m];
		for (int i = 0; i < n*m; i++) {
			graph[i] = new bool[n*m];
			visited[i] = false;
		}

		for (int i = 0; i < n*m; i++) {
			for (int j = 0; j < n*m; j++) {
				graph[i][j] = false;
			}
		}
	}

	void input() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> maze[i * m + j];
			}
		}

		for (int y = 0; y < n; y++) { // Check if there is a path from the current point (x, y) in the maze to the ...
			for (int x = 0; x < m; x++) {
				int current = y * m + x;
				if (maze[current] == 0) {
					int i;
					for (int h = -1; h <= 1; h += 2) {
						for (i = 1; x + i * h >= 0 && x + i * h < m && maze[current + i * h] == 0; i++) {}; // ... left (h = -1) and right (h = 1)
						if (maze[current + i * h] == 2 && x + i * h >= 0 && x + i * h < m) {
							graph[current][current + i * h] = true;
						}
						else if (i - 1 != 0) {
							graph[current][current + (i - 1) * h] = true;
						}

						for (i = 1; y + i * h >= 0 && y + i * h < n && maze[(y + i * h) * m + x] == 0; i++) {}; // ... up (h = -1) and down (h = 1)
						if (maze[(y + i * h) * m + x] == 2 && y + i * h >= 0 && y + i * h < n) {
							graph[current][(y + i * h) * m + x] = true;
						}
						else if (i - 1 != 0) {
							graph[current][(y + (i - 1) * h) * m + x] = true;
						}
					}
				}
			}
		}
	}

	int search() {
		int current = 0;
		int* level;
		level = new int[n*m];
		level[current] = 0;
		Queue queue;
		queue.push(current);
		visited[current] = true;

		while (!queue.empty()) {
			current = queue.pop();
			if (maze[current] == 2) {
				break;
			}
			for (int i = 0; i < n*m; i++) {
				if (graph[current][i] && current != i && !visited[i]) {
					queue.push(i);
					visited[i] = true;
					level[i] = level[current] + 1;
				}
			}
		}
		return level[current];
	}
};

int main() {

	Maze objMaze;

	int N, M;
	cin >> N >> M;
	objMaze.init(N, M);
	objMaze.input();

	cout << objMaze.search();

	system("pause");
	return 0;
}
