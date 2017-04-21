// Поиск многоугольника с наибольшим периметром 

#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;
int nbestsol; //Длина (число вершин) наилучшего решения
int *bestsol; //Список вершин наилучшего решения
double pbestsol; //Периметр для наилучшего решения

				 //Основная функция бэктрэкинга		
void btr(int k, int *path, int n, double **a) {
	//проверяет, что последняя вершина не совпадает с остальными, если это не так - возврат
	for (int i = 0; i < k - 1; i++) {
		if (path[i] == path[k - 1]) return;
	}
	//вычисляет длину замкнутого многоугольника с последней вершиной замкнутой на нулевую;
	
	double l = 0;
	path[k] = path[0];
	for (int i = 0; i < k; i++) {
		l += a[path[i]][path[i + 1]];
		cout << path[i]; 
	}
	cout << path[k]; 
	for (int i = k; i < n + 1; i++)	cout << "   ";
	cout << l << "\n";

				
	if (l > pbestsol)		
	{
		nbestsol = k;	pbestsol = l;
		for (int i = 0; i < k; i++)
			bestsol[i] = path[i];
	}
	for (int i = path[0] + 1; i < n; i++) {
		path[k] = i; btr(k + 1, path, n, a);
	}
}
//Инициализирующая функция бэктрэкинга

void startbtr(int n, double **a) {
	int *path = new int[n];
	for (int i = 0; i < n; i++) {
		path[0] = i; btr(1, path, n, a);
	}
}
void print() {
	cout << "Max perimetr : " << pbestsol << endl;

}
//Инициализация наилучшего решения многоугольником с единственной вершиной
void initbestsol(int n) {
	nbestsol = 1;
	bestsol = new int[n + 1];
	bestsol[0] = 0;
	pbestsol = 0;
}
/*Чтение графа из файла fname; в n - количество вершин
в a - матрица весов ребер; */
void readgraph(char *fname, int &n, double **&a) {
	ifstream f(fname);
	f >> n;
	a = new double*[n];
	for (int i = 0; i < n; i++) {
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
			f >> a[i][j];
	}
	f.close();
}

int main() {
	int n;
	double **a;
	readgraph("input.txt", n, a);
	initbestsol(n);
	startbtr(n, a);
	print();
	system("pause");
	return 0;
}

/*Пример задания графа в файле : 
4
0	7	4	6
7	0	2	3
4	2	0	8
6	3	8	0

4 - количество вершин
*/
