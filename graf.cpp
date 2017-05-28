/// Задан граф. Определить, изоморфны ли 2 графа. /// 
#include <iostream>
#include <ctime>

using namespace std;

void bild(bool **&g, int n)
{
	g = new bool *[n];
	for (int i = 0; i < n; i++)
		g[i] = new bool [n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			g[i][j] = rand() % 2;
}

void print(bool **g, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			if (g[i][j])
				cout << 1 << " ";
			else
				cout << 0 << " ";
		cout << endl;
	}
}

bool chek(bool **g1, bool **g2, int n, int *f)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (g1[i][j] != g2[f[i]][f[j]])
				return (false);
	return (true);
}

bool bild_next(int *&f, bool *&use, int n)
{
	use[f[n - 1]] = false;
	int i = n - 2;
	bool fl = true;
	while ((i >= 0) && fl)
	{
		int j;
		for (j = f[i] + 1; j < n; j++)
		{
			if (!use[j])
			{
				use[f[i]] = false;
				f[i] = j;
				use[j] = true;
				fl = false;
				break;
			}
		}
		if (j == n)
		{
			use[f[i]] = false;
			i--;
		}
	}
	if (i < 0)
		return (false);
	else
	{
		i++;
		while (i < n)
		{
			for (int j = 0; j < n; j++)
				if (!use[j])
				{
					f[i] = j;
					use[j] = true;
					i++;
					break;
				}
		}
		/*
		cout << endl;
		for (int j = 0; j < n; j++)
			cout << f[j] << " ";
		cout << endl;
		*/
		return (true);
	}
}

bool izomorf(bool **g1, bool **g2, int n)
{
	bool *use;
	int *f;
	use = new bool [n];
	f = new int [n];
	for (int i = 0; i < n; i++)
	{
		f[i] = i;
		use[i] = true;
	}
	do
	{
		if (chek(g1, g2, n, f))
			return (true);
	} while (bild_next(f, use, n));

	return (false);
}

bool **graf_a, **graf_b;
const int size_graf = 2;

int main()
{
	srand(time(NULL));

	bild(graf_a, size_graf);
	bild(graf_b, size_graf);

	print(graf_a, size_graf);
	cout << endl;
	print(graf_b, size_graf);
	cout << endl;

	if (izomorf(graf_a, graf_b, size_graf))
		cout << "izomorfni" << endl;
	else
		cout << "net" << endl;

	system("pause");

	return (0);
}