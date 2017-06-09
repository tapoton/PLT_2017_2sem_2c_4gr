#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
private:
    int dim;
    bool **adjMatrix;
    int *colors;

public:
    Graph();
    Graph(int dim);
    ~Graph();

    void printAdjMatrix();
    void colorGraph();
    bool isColored();
};

#endif // GRAPH_H
