#include<bits/stdc++.h>
#define INF 10000000
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

    bool isSaturated()
    {
        return f==c;
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

    void addFlow(int v, double minCut)
    {
        if(d == v) // forward
        {
            f += minCut;
        }
        else if(s == v) // reverse
        {
            f -= minCut;
        }
    }
    void print()
    {
        cout<<s<<" "<<d<<endl;
    }
};

class FlowNetwork
{
    int v;
    vector<vector<Edge>>adjList;
    vector <Edge*> edgeTo;
    vector<Edge> minCut;

public:
    FlowNetwork(int n)
    {
        v = n;
        adjList = vector<vector<Edge>>(v);
        edgeTo = vector<Edge*>(v);
    }
    void addEdge(int s, int d, double c)
    {
        Edge e(s,d,c,0);
        adjList[s].push_back(e);
        adjList[d].push_back(e);
    }

    vector<Edge> getAdj(int u)
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

            for (Edge &e: adjList[u])
            {
                int v = e.otherNode(u);
                if (!visited[v] && e.residualCapacity(v) > 0)
                {
                    edgeTo[v] = &e;
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
        minCut.clear();
        while (bfs(s, t))
        {
            double bottleneck = INF;
            int v = t;
            Edge x;
            while (v!=s)
            {
                if(bottleneck > edgeTo[v]->residualCapacity(v))
                {
                   bottleneck = edgeTo[v]->residualCapacity(v);
                   x = *edgeTo[v];
                }
                v=edgeTo[v]->otherNode(v);
            }
            minCut.push_back(x);
            v = t;
            while (v!=s)
            {
                edgeTo[v]->addFlow(v, bottleneck);
                v=edgeTo[v]->otherNode(v);
            }
            maxFlow += bottleneck;
        }
        return maxFlow;
    }

    void min_Cut()
    {
        for(int i=0; i<minCut.size(); i++)
        {
            minCut[i].print();
        }
    }
    bool saturated(int x)
    {
        for (Edge e : adjList[x])
        {
            if (!e.isSaturated())
                return false;
        }
        return true;
    }
};

int main()
{
    int n,e;
    cin>>n>>e;
    FlowNetwork fn(n);
    while(e--)
    {
        int s,d;
        double c;
        cin>>s>>d>>c;
        fn.addEdge(s,d,c);
    }
    cout<<fn.EdmonKarp(0,n-1)<<endl;
    fn.min_Cut();
}

