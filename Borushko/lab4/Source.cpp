#include <iostream>
#include <queue>

using namespace std;

class ChessTable
{
	int dimension;
	int **Table;
	int verticalSteps[8] = {1,1,-1,-1,2,2,-2,-2};
	int horizontalSteps[8] = {2,-2,-2,2,1,-1,1,-1};
public:
	bool canMakeStep(int x, int y, int index)
	{
		x += horizontalSteps[index];
		y += verticalSteps[index];
		return ((x > 0) && (x < dimension) && (y > 0) && (y < dimension) && (Table[x][y] == -1));
	}
	void makeStep(int x, int y, int index, int num)
	{
		if (canMakeStep(x, y, index))
		{
			x += horizontalSteps[index];
			y += verticalSteps[index];
			Table[x][y] = Table[y][x] = num;
		}
	}
	ChessTable(const int n = 8)
	{
		if (n <= 0)
			throw "Error:Negative or zero-sized value.\n";
		Table = new int*[n];
		for (int i = 0; i < n; i++)
			Table[i] = new int[n];
		dimension = n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				Table[i][j] = -1;
	}
	int knightWalk(int x1, int y1, int x2, int y2)
	{
		queue<int> Q;
		int num = 1;
		Table[x1][y1] = 0;
		Q.push(x1);
		Q.push(y1);
		while (!Q.empty())
		{
			queue<int> higherLvl;
			while (!Q.empty())
			{
				int x = Q.front();
				Q.pop();
				int y = Q.front();
				Q.pop();
				for (int i = 0; i < 8; i++)
					if (canMakeStep(x, y, i))
					{
						higherLvl.push(x + horizontalSteps[i]);
						higherLvl.push(y + verticalSteps[i]);
						makeStep(x, y, i, num);
					}
			}
			num++;
			Q = higherLvl;
		}
		return Table[x2][y2];
	}
};

int main()
{
	try
	{
		int dimension;
		cout << "Dimension of the table:\n";
		cin >> dimension;
		ChessTable T(dimension);
		int x1, y1;
		cout << "A coords:\nx1 = ";
		cin >> x1;
		cout << "y1 = ";
		cin >> y1;
		int x2, y2;
		cout << "D coords:\nx2 = ";
		cin >> x2;
		cout << "y2 = ";
		cin >> y2;
		cout << "Minimum path length: " << T.knightWalk(x1,y1,x2,y2) << ".\n";
	}
	catch (const char* err)
	{
		cout << err << endl;
	}
	return 0;
}