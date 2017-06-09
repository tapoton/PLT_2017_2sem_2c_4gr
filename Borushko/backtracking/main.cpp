#include "graph.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int main() {
    int d = 4;
    Graph graph(d);
    graph.printAdjMatrix();
    graph.colorGraph();
    //system("Pause");
    return 0;
}
