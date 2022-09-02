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
    bool saturated(int x)
    {
        for (Edge* e : adjList[x])
        {
            if (!e->isSaturated())
                return false;
        }
        return true;
    }
};

class Team
{
public:
    string name;
    int w; // number of win
    int l; // number of losses
    int r; // number of remaining
    Team()
    {

    }
    Team(string name, int w, int l, int r)
    {
        this->name = name;
        this->w = w;
        this->l = l;
        this->r = r;
    }
};

class Baseball_Elimination
{
    int n;
    double totalMatch;
    vector<Team> teams;
    vector<vector<double>> matches;
public:
    Baseball_Elimination(int n)
    {
        this->n = n;
        totalMatch = 0;
        teams = vector<Team>(n+1);
        matches = vector<vector<double>>(n+1);
        for(int i = 0; i<=n; i++)
            matches[i].assign(n+1, 0);
    }
    void addTeam(int id, string name, int w, int l, int r, vector<double> v)
    {
        Team t(name,w,l,r);
        teams[id] = t;
        for(int i=0; i<n; i++)
        {
            matches[id][i] = v[i];
        }
    }

    void isEliminated(int id)
    {
        for (int i = 0; i < n; i++)
        {
            if (teams[id].w + teams[id].r < teams[i].w)
            {
                cout<<endl<<teams[id].name<<" is eliminated."<<endl;
                cout<<"They can win at most "<<teams[id].w<<" + "<<teams[id].r<<" = "<<teams[id].w + teams[id].r<<" games.\n";
                cout<<teams[i].name<<" has won a total of "<<teams[i].w<<" games.\n";
                cout<<"They play each other 0 times."<<endl;
                cout<<"So on average, each of the teams in this group wins "<<teams[i].w<<"/1 = "<<teams[i].w<<" games.\n";
                return ;
            }
        }

        int NumOfmatches = ((n-1)*(n-2))/2;
        FlowNetwork myNetwork(NumOfmatches+n+2);
        int s = n;
        int t = s + 1;
        int node = t + 1; //matches starting index

        for (int i = 0; i < n; i++)
        {
            if(i==id)
                continue;
            for (int j = i + 1; j < n; j++)
            {
                if (j!=id)
                {
                    myNetwork.addEdge(s, node, matches[i][j]);
                    myNetwork.addEdge(node, i, INF);
                    myNetwork.addEdge(node, j, INF);
                    node++;
                }
            }
            myNetwork.addEdge(i, t, teams[id].w + teams[id].r - teams[i].w);
        }
        double max_flow = myNetwork.EdmonKarp(s, t);
        //cout<<teams[id].name<<" "<<max_flow<<endl;
        if(!myNetwork.saturated(s))
        {
            cout<<endl<<teams[id].name<<" is eliminated."<<endl;
            cout<<"They can win at most "<<teams[id].w<<" + "<<teams[id].r<<" = "<<teams[id].w + teams[id].r<<" games.\n";

            vector<bool> visited(NumOfmatches+n+2, false);
            vector<int> v;
            stack<int> traverse;
            traverse.push(n);
            while (!traverse.empty()) ///DFS
            {
                int tp = traverse.top();
                traverse.pop();
                if (!visited[tp])
                {
                    visited[tp] = true;
                    for(Edge* e: myNetwork.getAdj(tp))
                    {
                        if(e->residualCapacity(e->otherNode(tp))>0)
                        {
                            traverse.push(e->otherNode(tp));
                            if(e->otherNode(tp)<n)
                                v.push_back(e->otherNode(tp));
                        }
                    }
                }
            }
            sort( v.begin(), v.end() );
            v.erase( unique( v.begin(), v.end() ), v.end() );
            double win = 0;
            for(int i=0; i<v.size(); i++)
            {
                if(win==0)
                    cout<<teams[v[i]].name;
                else
                    cout<<","<<teams[v[i]].name;
                win+=teams[v[i]].w;
            }
            cout<<" have won a total of "<<win<<" games.\n";

            double remain=0;
            for (int i = 0; i < v.size() - 1; i++)
            {
                for (int j = i + 1; j < v.size(); j++)
                    remain += matches[v[i]][v[j]];
            }
            cout<<"They play each other "<<remain<<" times.\n";
            cout<<"So on average, each of the team wins "<<win+remain<<"/"<<v.size()<<" = "<<(win+remain)/v.size()<<" games.\n";
        }
    }
};

int main()
{
    freopen("Input.txt", "r", stdin);
    int n;
    cin>>n;
    Baseball_Elimination obj(n);
    string name;
    int id,w,l,r,t;
    for(int i=0; i<n; i++)
    {
        cin>>name>>w>>l>>r;
        vector<double> v;
        for(int j=0; j<n; j++)
        {
            cin>>t;
            v.push_back(t);
        }
        obj.addTeam(i,name,w,l,r,v);
    }
    for(int i=0; i<n; i++)
    {
        obj.isEliminated(i);
    }
}
