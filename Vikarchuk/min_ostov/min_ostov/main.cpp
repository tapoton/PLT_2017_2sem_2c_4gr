#include<iostream>
#include<queue>
using namespace std;

static const int MAX_VERT = 20000;
static const int inf = 1000000;
int n, m;
vector< vector< pair<int,int> >> edges; 
bool visited[MAX_VERT];
vector <int> visited_verticles;

int main()
{
	cin >> n >> m;
	
	for (int i = 0; i < n; i++)
		edges.push_back({});

	int x, y, w;
	pair<int, int> sample;
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y >> w;
		sample.first = y;
		sample.second = w;
		edges[x].push_back(sample);
		sample.first = x;
		edges[y].push_back(sample);
	}
	
	int min_weight = 0;
	
	int currnode = 0, visited_count = 0;
	visited[currnode] = true;
	visited_verticles.push_back(currnode);
	visited_count++;

	while (visited_count < n)
	{
		int min_dist = inf;
		int new_vert;
		
		for (int i = 0; i < visited_count; i++) // searching for minimum edge weight from current core of the graph
		{
			int vi = visited_verticles[i];   // verticle from semi-core we're currently analyzing
			for (int j = 0; j < edges[vi].size(); j++)
			{
				if (!visited[edges[vi][j].first])
				{
					int curr_dist = edges[vi][j].second;
					if (curr_dist < min_dist)
					{
						min_dist = curr_dist;
						new_vert = edges[vi][j].first;
					}
				}
			}
		}
		visited[new_vert] = true;
		visited_verticles.push_back(new_vert);
		visited_count++;
		min_weight += min_dist;

	}
	cout << min_weight;

	system("pause");
	return 0;
}