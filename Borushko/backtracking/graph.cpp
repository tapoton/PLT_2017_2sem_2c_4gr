#include "graph.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace  std;

Graph::Graph() {
    dim = 0;
}

Graph::Graph(int d) {
    srand(time(0));

    dim = d;

	adjMatrix = new bool*[dim];
	for (int i = 0; i < dim; i++)
		adjMatrix[i] = new bool[dim];

    for (int i = 0; i < dim; i++)
        adjMatrix[i][i] = 1;
    for (int i = 0; i < dim; i++)
        for (int j = i+1; j < dim; j++)
            adjMatrix[i][j] = adjMatrix[j][i] = rand()%2;

    colors = new int[dim];
    for (int i = 0; i < dim; i++)
        colors[i] = 0;
}

void Graph::printAdjMatrix() {
    for (int i = 0; i < dim; i++) {
        for (int j =0; j < dim; j++)
                cout << adjMatrix[i][j] << ' ';
        cout << endl;
    }
}

bool Graph::isColored() {
    for (int i = 0; i < dim; i++)
        if (colors[i] == 0) return false;
    return true;
}

void Graph::colorGraph() {
    int colorQ = 1; //счетчик цветов
    bool isGraphColored = false;
    bool **adjMatrixReserve = new bool*[dim];
    for (int i = 0; i < dim; i++)
        adjMatrixReserve[i] = new bool[dim];

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            adjMatrixReserve[i][j] = adjMatrix[i][j];

	int k = 0;
    while (!isGraphColored && k < dim) {
       int l = 0;
       while (colors[k] != 0) k++;//находим первую неокрашенную вершину
       colors[k] = colorQ; //окрашиваем в текущий цвет
       while (adjMatrixReserve[k][l] != 0 && l < dim) l++;//находим первую несмежную с ней вершину
       if (l == dim) {
           colorQ++;
           k++;
       } else {
           if (colors[l] == 0 )
               colors[l] = colorQ;

               /* Побитовое сложение k- и l-й строк матрицы */
               for (int i = 0; i < dim; i++)
                   adjMatrixReserve[k][i] = adjMatrixReserve[k][i] || adjMatrixReserve[l][i];
               /* ---------- */

               /* Исключение окрашенной вершины */
               for (int i = 0; i < dim; i++)
                   adjMatrixReserve[l][i] = 1;
               /* ---------- */
       }

       /* Проверка окончания набора в очередную цветовую группу. Если група сформирована, инкрементируем счетчик цветов */
       bool isColorComplete = true;
       for (int i = 0; i < dim; i++)
           if (adjMatrixReserve[k][i] == 0) isColorComplete = false;
       if (isColorComplete) colorQ++;
       /* ---------- */

        isGraphColored = this->isColored();
    }

    /* Вывод цветовых групп */
	cout << "Nodes:  | ";
	for (int i = 0; i < dim; i++) cout << i << " | ";
	cout << endl;
	cout << "Colors: | ";
	for (int i = 0; i < dim; i++) cout << colors[i] << " | ";
	cout << endl;
	/* ---------- */

	for (int i = 0; i < dim; i++) delete[] adjMatrixReserve[i];
    delete[] adjMatrixReserve;
}

Graph::~Graph() {

}
