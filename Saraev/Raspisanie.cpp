#include <iostream>


using namespace std;



struct road
{
	int dep;         
    int arr;         
	int time_dep;
	int time_arr;      
};


//Помечаем деревни флажками
void InFlags(int N, int d, int *range, bool *flags,  int max=10000)
{
	for (int i = 0; i<N; i++)
	{
		flags[i] = 0;
		range[i] = max;
	}
	range[d] = 0;          
}



void Dijkstra(int N, int k_roads, road *R, int d, int v, bool *flags, int *range,  int max=10000)
{
	int min = 0;//Непосещенная вершина с минимальной пометкой
	do
	{
		min = N + 1;
		int min_time = max;//Минимальное время
		for (int i = 0; i<N; i++)                              
			if (!flags[i] && range[i]<min_time)
			{
				min = i;
				min_time = range[i];
			}

		if (min != N + 1)
		{
			for (int j = 0; j<k_roads; j++)
				if (R[j].time_dep >= min_time && R[j].dep == min + 1 && R[j].time_arr < range[R[j].arr - 1])
					range[R[j].arr - 1] = R[j].time_arr;
		}
		flags[min] = 1;
		if (min == v)
			return;
	} while (min < N + 1);
}




int main()
{
	setlocale(LC_ALL, "Russian");
	int N, d, v, k_roads;
		do
		{
			cout << "Введите количество деревень" << endl;
			cin >> N;
		} while (N <= 0 || N>100);
	    do
	    {
			cout << "Введите из какой деревни нужно уехать" << endl;
		    cin >> d;
	    } while (d <= 0 || d>N);
	    do
	    {
			cout << "Введите в какую деревню нужно приехать" << endl;
		    cin >> v;
	    } while (v <= 0 || v>N);
	
	d -= 1;
	v -= 1;
	do
	{
		cout << "Введите Количество дорог" << endl;
		cin >> k_roads;
	} while (k_roads < 0 || k_roads>10000);
	int *range = new int[N];
	bool *flags = new bool[N];
	road *R = new road[k_roads];
	for (int i = 0; i<k_roads; i++)
	{
		cout << "Введите Пункт отправления, Пункт прибытия, Время отправления, Время прибытия" << endl;
		cin >> R[i].dep >> R[i].arr >> R[i].time_dep >> R[i].time_arr;
	}
	InFlags(N, d, range, flags);
	Dijkstra(N, k_roads, R, d, v, flags, range);

	cout << "Результат: минимальное время, когда Мария Ивановна может попасть в деревню "<< v <<" = ";
	if (range[v] != 10000)
		cout << range[v] << endl;
	else
		cout << -1 << endl;


	system("PAUSE");
}