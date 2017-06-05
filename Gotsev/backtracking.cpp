#include<iostream>
using namespace std;
//const int n = 5;

void Inint_matr(int **a,int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			a[i][j] = 0;
		}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			cout << "\nВВедите расстояние от " << i << " города до " << j << " города: ";
			cin >> a[i][j];
			a[j][i] = a[i][j];
		}
}

void Print_matr(int **a,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
}

int sum(int *a, int n)
{
	int s = 0;
	for (int i = 0; i < n; i++)
		s += a[i];
	return s;

}
int Floyd_Yo(int **a,int n)
{
	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if ((a[i][k] * a[k][j] != 0) && (i != j))
					if ((a[i][k] + a[k][j] < a[i][j]) || (a[i][j] == 0))
						a[i][j] = a[i][k] + a[k][j];
	}
	int min_sum = sum(a[0],n);
	int min_city = 0;
	for (int i = 1; i < n; i++)
		if (sum(a[i],n) < min_sum)
		{
			min_sum = sum(a[i],n);
			min_city = i;
		}
	return min_city;
}


void main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "введите количество городов в системе: ";
	cin >> n;
	int **a;
	a = new int*[n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];
	Inint_matr(a,n);
	Print_matr(a,n);
	cout << Floyd_Yo(a,n);
	
	

	system("pause");
}