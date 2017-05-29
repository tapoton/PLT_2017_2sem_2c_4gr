#include <iostream>
using namespace std;
int n;
int const MAX = 1000;
class graf
{
	int **G;
public:

	void n_perif()
	{
		int x, t;
		do
		{
			cout << " Enter the N: ";
			cin >> x;
		} while (x < 0);
		do
		{
			cout << " Choose the town  ";
			cin >> t;
		} while (t <= 0 || t > n);
		cout << x << " perefir city " << t << " :  " << endl;
		for (int i = 0; i < n; i++)
		{
			if (i != t - 1 && G[i][t - 1] > x)
				cout << " city : " << i + 1 << ' ';
		}
		cout << endl;
	}
	int min_xy(bool * b, int x, int y, int r = 0)
	{
		if (b[x])return MAX;
		if (x == y)return r;
		int min = MAX;
		b[x] = 1;
		for (int i = 0; i < n; i++)
		{
			int p = min_xy(b, y, i, r + G[i][x]);
			if (p < min) min = p;
		}
		b[x] = 0;
		return min;
	}
	void optim_graf()
	{
		bool *b = new bool[n];
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{

				for (int k = 0; k < n; k++)
					b[k] = 0;
				G[j][i] = G[i][j] = min_xy(b, i, j);
			}

		}
		delete b;
	}
	void print_graf()
	{
		cout << " Graf : " << endl;
		for (int i = 0; i < n; i++)
		{
			cout << " ";
			for (int j = 0; j < n; j++)
				cout << G[i][j] << "    ";
			cout << endl;
		}
	}
	graf()
	{
		do
		{
			cout << " Enter the number of cities: ";
			cin >> n;
		} while (n <= 0);
		G = new int*[n];
		for (int i = 0; i < n; i++)
			G[i] = new int[n];
		int road;
		for (int i = 0; i < n; i++)
		{
			G[i][i] = 0;
			for (int j = i + 1; j < n; j++)
			{
				cout << " Enter the road " << (i + 1) << " - " << (j + 1) << ": ";
				cin >> road;
				if (road<=0) road = MAX;

				G[j][i] = G[i][j] = road;
			}
		}
	}
	~graf()
	{
		for (int i = 0; i < n; i++)
			delete G[i];
		delete[] G;
	}
};

void main()
{
	graf a;
	a.print_graf();
	a.optim_graf();
	a.print_graf();

	a.n_perif();
	system("PAUSE");

}