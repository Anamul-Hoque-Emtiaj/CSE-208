#include<bits/stdc++.h>
#define INF 1000000
using namespace std;

class Edge
{
    /// source, destination, flow, capacity
    int s,d;
    double c,f;
public:
    Edge()
    {

    }
    Edge(int s, int d, double c, double f)
    {
        this->s = s;
        this->d = d;
        this->c = c;
        this->f = f;
    }

    double residualCapacity (int v)
    {
        if (v == s)
            return f;

        if (v == d)
            return (c - f);

        return -1;
    }

    int otherNode(int u)
    {
        if (u == s)
            return d;

        if (u == d)
            return s;

        return -1;
    }

    void addFlow(int v, double bottleneck)
    {
        if(d == v) // forward
        {
            f += bottleneck;
        }
        else if(s == v) // reverse
        {
            f -= bottleneck;
        }
    }
};

class FlowNetwork
{
    int v;
    vector<vector<Edge*>>adjList;
    vector <Edge*> edgeTo;

public:
    FlowNetwork(int n)
    {
        v = n;
        adjList = vector<vector<Edge*>>(v);
        edgeTo = vector<Edge*>(v);
    }
    void addEdge(int s, int d, double c)
    {
        Edge *e = new Edge(s,d,c,0);
        adjList[s].push_back(e);
        adjList[d].push_back(e);
    }

    vector<Edge*> getAdj(int u)
    {
        return adjList[u];
    }

    bool bfs(int s, int t)
    {
        vector <bool> visited = vector<bool>(v, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            for (Edge* e: adjList[u])
            {
                int v = e->otherNode(u);
                if (!visited[v] && e->residualCapacity(v) > 0)
                {
                    edgeTo[v] = e;
                    visited[v] = true;
                    if (v==t)
                    {
                        return true;
                    }
                    q.push(v);
                }
            }
        }
        return false;
    }

    double EdmonKarp(int s, int t)
    {
        double maxFlow = 0;
        while (bfs(s, t))
        {
            double bottleneck = INF;
            for(int v = t; v !=s ; v = edgeTo[v]->otherNode(v))
            {
                bottleneck = min(bottleneck, edgeTo[v]->residualCapacity(v));
            }
            for(int v = t; v !=s ; v = edgeTo[v]->otherNode(v))
            {
                edgeTo[v]->addFlow(v, bottleneck);
            }
            maxFlow += bottleneck;
        }
        return maxFlow;
    }
};

int main()
{
    int t;
    cin>>t;
    for(int i=1; i<=t; i++)
    {
        int m,n;
        cin>>m>>n;
        int M[m][3],W[n][3];
        for(int j=0; j<m; j++)
            cin>>M[j][0]>>M[j][1]>>M[j][2];
        for(int j=0; j<n; j++)
            cin>>W[j][0]>>W[j][1]>>W[j][2];
        int totalVertex = n+m+2;
        int s=0;
        int t = n+m+1;
        int wi = m+1;
        FlowNetwork myNetwork(totalVertex);
        for(int j=1; j<=m; j++)
            myNetwork.addEdge(s,j,1);
        for(int j=wi; j<t; j++)
            myNetwork.addEdge(j,t,1);

        for(int j=0; j<m; j++)
        {
            for(int k=0; k<n; k++)
            {
                if(abs(M[j][0]-W[k][0])<=12 && abs(M[j][1]-W[k][1])<=5 && M[j][2]==W[k][2])
                {
                    myNetwork.addEdge(j+1,wi+k,1);
                }
            }
        }
        cout<<"Case "<<i<<": "<<myNetwork.EdmonKarp(s,t)<<endl;
    }
}

