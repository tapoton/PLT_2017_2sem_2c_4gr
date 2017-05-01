#include <iostream>
#include <set>
#include <stack>
using namespace std;

set<int> initSet (int begin, int end)
{
    set<int> nums={};
    for (unsigned int i=begin+1; i<end; i++) nums.insert(i);
    return nums;
}

class Graph
{
private:
    
    unsigned int n;
    int ** AdjacencyMatrix;
    bool* visited;
    
public:
    
    Graph ()
    {
        cout << "\nEnter the number of graph's nodes: ";
        unsigned int num;
        cin >> num;
        n=num;
        AdjacencyMatrix = new int*[n];
        for(unsigned int i=0; i<n; i++)
            AdjacencyMatrix[i]= new int[n];
        visited = new bool [n];
        
    }
    
    void Adjacency ()
    {
        cout << "\nEnter 1 for YES, 0 for NO";
        unsigned int ok=-1;
        for (unsigned int i=0; i<n; i++)
            for (unsigned int j=i; j<n; j++)
            {
                if (i==j) AdjacencyMatrix[i][j]=0;
                else
                {
                    cout << "\nIs " << i+1 << " node connected with " << j+1 << " node? ";
                    cin >> ok;
                    if (ok) AdjacencyMatrix[i][j]=AdjacencyMatrix[j][i]=1;
                    else AdjacencyMatrix[i][j]=AdjacencyMatrix[j][i]=0;
                }
            }
    }

    void DFS (int begin, int end, set<int> &commonNode)
    {
        static stack<int> way;
        static set<int> path;
        
        if (begin==end)
        {
            way.push(begin+1);
            stack<int> top = way;
            cout << "\n";
            while(!top.empty())
            {
                cout << top.top() << " ";
                top.pop();
            }
            way.pop();
            
            set<int> v_intersection={};
            set_intersection(path.begin(), path.end(), commonNode.begin(), commonNode.end(), inserter(v_intersection,v_intersection.begin()));
            commonNode=v_intersection;
        }
        
        visited[begin]=true;
        way.push(begin+1);
        path.insert(begin+1);
        
        for (unsigned int i=0; i< n; i++)
            if (AdjacencyMatrix[begin][i]==1 && !visited[i]) DFS(i, end, commonNode);
        
        visited[begin]=false;
        path.erase(path.find(begin+1));
        way.pop();
    }

    
    void show ()
    {
        cout << "\nAdjacencyMatrix: ";
        for (unsigned int i=0; i<n; i++)
        {
            cout << "\n| ";
            for (unsigned int j=0; j<n; j++)
                cout << AdjacencyMatrix[i][j] << " ";
            cout << "|";
        }
        cout << endl;
    }
};


int main() {
    Graph graph;
    graph.Adjacency();
    graph.show ();
    
    cout << "\nNumber of the nodes between which all ways should be found: ";
    unsigned int begin, end;
    cin >> begin >> end;
    set<int> commonNode = initSet(begin, end);
    
    cout << "\nAll path from " << begin << " to " << end << ": ";
    graph.DFS(begin-1, end-1, commonNode);
    
    
    if (!commonNode.empty())
    {
        cout << "\nCommon node(s): ";
        for (int n : commonNode) cout << n << ' ';
        cout << endl;
    } else {
        cout << "\nThere aren't common nodes!";
    }
    cout << endl;
    return 0;
}
