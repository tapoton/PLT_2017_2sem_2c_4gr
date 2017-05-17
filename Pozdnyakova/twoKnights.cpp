#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

const int N=8;
const int dx[]={2, 2, 1, 1,-1,-1,-2,-2};
const int dy[]={1,-1, 2,-2, 2,-2, 1,-1};

class ChessBoard
{
private:
    
    int graph[N][N];
    
public:
    
    void setKnights (int x1, int y1, int x2, int y2)
    {
        for (unsigned int i=0; i<N; i++)
            for (unsigned int j=0; j<N; j++)
                graph[i][j]=0;
        
        graph[x1][y1]=1;
        graph[x2][y2]=1;
    }
    
    void showBoard ()
    {
        cout << endl << "  ";
        for (unsigned int i=0; i<N; i++)
            cout << setw(2) << i+1 << " ";
        for (unsigned int i=0; i<N; i++)
        {
            cout << endl << char(97+i) << " ";
            for (unsigned int j=0; j<N; j++)
                cout << setw(2) << graph[i][j] << " ";
        }
    }
    
    
    int bfs(int x, int y, int u, int v)
    {
        queue<int> qXY;
        
        graph[x][y]=0;
        graph[u][v]=0;
        qXY.push(x);
        qXY.push(y);
        
        while (!qXY.empty())
        {
            int x, y;
            x = qXY.front(); qXY.pop();
            y = qXY.front(); qXY.pop();
 
            for (int i = 0; i < 8; i++)
            {
                int newX = x + dy[i];
                int newY = y + dx[i];
                
                if (newX>=0 && newY>=0 && newX<8 && newY<8 && graph[newX][newY]==0)
                {
                        graph[newX][newY]=graph[x][y]+1;
                        qXY.push(newX);
                        qXY.push(newY);
                }
            }
        }
        if (graph[u][v]>0 && graph[u][v]%2==0) return graph[u][v]/2;
           else return  0;
    }
};

    int main()
{
    cout << "\nEnter the coordinates where the first knight is: ";
    int x1;
    char let1;
    cin >> let1 >> x1;
    int y1 = int(let1-'a');
    x1--;
    
    cout << "\nEnter the coordinates where the second knight is: ";
    int x2;
    char let2;
    cin >> let2 >> x2;
    int y2 = int(let2-'a');
    x2--;
    
    if (x1>=0 && x1<8 && x2>=0 && x2<8 && y1>=0 && y1<8 && y2>=0 && y2<8)
    {
        ChessBoard board;
        board.setKnights(x1, y1, x2, y2);
        board.showBoard();
        int k = board.bfs(x1, y1, x2, y2);
        if (k) cout << "\nKnights need to do " << k << " step(s).";
        else cout << "\nNo possible way!";
    }
    else cout << "\nWrong input!";
    
    cout << endl;
    return 0;
};
