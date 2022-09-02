#include<bits/stdc++.h>
using namespace std;

class Graph
{
    int n;
    int **adjMatrix;
public:
    Graph(int n)
    {
        this->n = n;
        adjMatrix = new int*[n+1];
        for(int i=0; i<=n; i++)
        {
            adjMatrix[i] = new int[n+1];
            for(int j=0; j<=n; j++)
            {
                if(i==j)
                    adjMatrix[i][j] = 0;
                else
                    adjMatrix[i][j] = 10000000;
            }
        }
    }
    ~Graph()
    {
        for(int j=0; j<=n; j++)
        {
            delete adjMatrix[j];
        }
        delete[] adjMatrix;
    }
    void addEdge(int u, int v, int w)
    {
        adjMatrix[u][v] = w;
    }

    void floydWarshall()
    {
        int D[n+1][n+1];
        for(int i=0; i<=n; i++)
        {
            for(int j=0; j<=n; j++)
            {
                D[i][j] = adjMatrix[i][j];
            }
        }
        for(int k=0; k<=n; k++)
        {
            for(int i=0; i<=n; i++)
            {
                for(int j=0; j<=n; j++)
                {
                    if(D[i][j]>D[i][k]+D[k][j])
                    {
                        D[i][j] = D[i][k]+D[k][j];
                    }
                }
            }
        }
        cout<<"Shortest distance matrix\n";
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(D[i][j]!=10000000)
                    cout<<D[i][j]<<" ";
                else
                    cout<<"INF ";
            }
            cout<<endl;
        }
    }

    void APSP_MM()
    {
        int L[n+1][n+1],M[n+1][n+1];
        for(int i=0; i<=n; i++)
        {
            for(int j=0; j<=n; j++)
            {
                L[i][j] = adjMatrix[i][j];
            }
        }
        int m=1;
        while(m<n-1)
        {
            for(int i=0; i<=n; i++)
            {
                for(int j=0; j<=n; j++)
                {
                    M[i][j] = 10000000;
                    for(int k=0; k<=n; k++)
                    {
                        if(M[i][j]>L[i][k]+L[k][j])
                        {
                            M[i][j] = L[i][k] + L[k][j];
                        }
                    }
                }
            }
            for(int i=0; i<=n; i++)
            {
                for(int j=0; j<=n; j++)
                {
                    L[i][j] = M[i][j];
                }
            }
            m*=2;
        }

        cout<<"Shortest distance matrix\n";
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(L[i][j]!=10000000)
                    cout<<L[i][j]<<" ";
                else
                    cout<<"INF ";
            }
            cout<<endl;
        }
    }
};


int main()
{
    int n,m;
    cin>>n>>m;
    Graph g(n);
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    g.floydWarshall();
    //g.APSP_MM();
}


