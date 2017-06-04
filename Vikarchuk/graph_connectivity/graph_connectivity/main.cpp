#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// bfs method
int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	int s = 0;

	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		g[u - 1].push_back(v - 1);
		g[v - 1].push_back(u - 1);
	}

	queue<int> q;

	q.push(s);
	vector<bool> used(n);

	used[s] = true;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (size_t i = 0; i < g[v].size(); ++i)
		{
			int to = g[v][i];
			if (!used[to])
			{
				used[to] = true;
				q.push(to);
			}
		}
	}

	vector<bool>::iterator it;

	it = find(used.begin(), used.end(), false); // find returns true if present , false otherwise
	if (it == used.end())
		cout << "yes";
	else
		cout << "no";
	system("pause");
	return 0;
}