#include<bits/stdc++.h>
using namespace std;

bool cmp(const pair<int,int> &s1, const pair<int,int> &s2)
{
    return s1.second>s2.second;
}
///DFS & Others
class Graph1
{
    int n,t,cc,scc;
    pair<int,int> *st,*ft;
    vector<int> *adjList,*revAdjList;
    bool *visit;
public:
    Graph1(int n)
    {
        this->n = n;
        adjList = new vector<int>[n+1];
        revAdjList = new vector<int>[n+1];
        st = new pair<int,int>[n+1];
        ft = new pair<int,int>[n+1];
        visit = new bool[n+1];
    }
    ~Graph1()
    {
        delete[] adjList;
        delete[] revAdjList;
        delete[] st;
        delete[] ft;
        delete[] visit;
    }
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
    }
    void addUnDirectedEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    void addRevEdge(int u, int v)
    {
        revAdjList[u].push_back(v);
    }
    void explore(int x)
    {
        visit[x] = true;
        st[x].first = x;
        st[x].second = t++;
        for(int i=0; i<adjList[x].size(); i++)
        {
            if(!visit[adjList[x][i]])
                explore(adjList[x][i]);
        }
        ft[x].first = x;
        ft[x].second = t++;
    }
    void dfs()
    {
        for(int i=0; i<=n; i++)
            visit[i] = false;
        t=0;
        cc=0;
        for(int i=1; i<=n; i++)
        {
            if(!visit[i])
            {
                explore(i);
                cc++;
            }
        }

    }
    bool isPath(int u, int v)
    {
        for(int i=0; i<=n; i++)
            visit[i] = false;
        explore(u);
        if(visit[v])
            return true;
        else
            return false;
    }
    void exploreSCC(int x,bool print)
    {
        visit[x] = true;
        if(print)
        {
            cout<<x<<" ";
        }
        for(int i=0; i<revAdjList[x].size(); i++)
        {
            if(!visit[revAdjList[x][i]])
                exploreSCC(revAdjList[x][i],print);
        }
    }
    void SCC(bool print)
    {
        dfs();
        sort(ft+1,ft+n+1,cmp);
        for(int i=0; i<=n; i++)
            visit[i] = false;
        scc=0;
        for(int i=1; i<=n; i++)
        {
            if(!visit[ft[i].first])
            {
                scc++;
                if(print)
                {
                    cout<<"\nSCC No: "<<scc<<endl;
                }
                exploreSCC(ft[i].first,print);
            }

        }
        if(print)
        {
            cout<<endl;
        }
    }
    bool isCycle()
    {
        SCC(false);
        if(scc==n)
            return false;
        else
            return true;
    }
    void topologicalSort()
    {
        if(isCycle())
        {
            cout<<"Topological Sort: Not Possible\n";
        }
        else
        {
            dfs();
            sort(ft+1,ft+n+1,cmp);
            cout<<"Topological Sort:\n";
            for(int i=1; i<=n; i++)
            {
                cout<<ft[i].first<<" ";
            }
            cout<<endl;
        }
    }
};

///BFS & others
class Graph2
{
    int n, *level,*par;
    vector<int> *adjList;
public:
    Graph2(int n)
    {
        this->n = n;
        adjList = new vector<int>[n+1];
        level = new int[n+1];
        par = new int[n+1];
    }
    ~Graph2()
    {
        delete[] adjList;
        delete[] level;
        delete[] par;
    }
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
    }
    void addUnDirectedEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    void bfs(int s)
    {
        for(int i=0; i<=n; i++)
        {
            level[i] = n+5;
            par[i] = -1;
        }
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int t = q.front();
            q.pop();
            for(int i=0; i<adjList[t].size(); i++)
            {
                if(level[adjList[t][i]]==n+5)
                {
                    level[adjList[t][i]] = level[t] + 1;
                    par[adjList[t][i]] = t;
                    q.push(adjList[t][i]);
                }
            }
        }
    }
    int distance(int u, int v)
    {
        bfs(u);
        if(level[v]==n+5)
            return -1;
        else
            return level[v];
    }
    void shortestPath(int u, int v)
    {
        bfs(u);
        if(level[v]==n+5)
            cout<<"No path Possible\n";
        else
        {
            stack<int> st;
            st.push(v);
            while(par[v]!=-1)
            {
                st.push(par[v]);
                v = par[v];
            }
            while(!st.empty())
            {
                cout<<st.top()<<" ";
                st.pop();
            }
            cout<<endl;
        }
    }
    bool isBipartite()
    {
        bfs(n);
        bool f = true;
        for(int i=1; i<=n; i++)
        {
            for(int j=0; j<adjList[i].size(); j++)
            {
                if(level[i]==level[adjList[i][j]])
                {
                    f = false;
                    break;
                }
            }
        }
        return f;
    }
};

class Graph3
{
    int n, *dis,*par;
    bool *explore;
    vector<pair<int, int>> *adjList;
public:
    Graph3(int n)
    {
        this->n = n;
        adjList = new vector<pair<int, int>>[n+1];
        dis = new int[n+1];
        par = new int[n+1];
        explore = new bool[n+1];
    }
    ~Graph3()
    {
        delete[] adjList;
        delete[] dis;
        delete[] par;
        delete[] explore;
    }
    void addEdge(int u, int v, int w)
    {
        adjList[u].push_back(make_pair(v,w));
    }
    void addUnDirectedEdge(int u, int v, int w)
    {
        adjList[u].push_back(make_pair(v,w));
        adjList[v].push_back(make_pair(u,w));
    }
    void Dijkstra(int s)
    {
        for(int i=0; i<=n; i++)
        {
            dis[i] = 1000000;
            par[i] = -1;
        }
        priority_queue< pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > pq;
        dis[s] = 0;
        pq.push(make_pair(0,s));
        while(!pq.empty())
        {
            int t = pq.top().second;
            pq.pop();
            for(int i=0; i<adjList[t].size(); i++)
            {
                if(dis[adjList[t][i].first]> dis[t] + adjList[t][i].second)
                {
                    dis[adjList[t][i].first] = dis[t] + adjList[t][i].second;
                    par[adjList[t][i].first] = t;
                    pq.push(make_pair(dis[adjList[t][i].first],adjList[t][i].first));
                }
            }
        }
    }
    void shortestPath(int s, int d)
    {
        Dijkstra(s);
        if(dis[d]==1000000)
        {
            cout<<"No shortest Path Possible\n";
        }
        else
        {
            cout<<"Shortest Distance: "<<dis[d]<<endl;
            stack<int> st;
            st.push(d);
            while(par[d]!=-1)
            {
                st.push(par[d]);
                d = par[d];
            }
            while(!st.empty())
            {
                cout<<st.top()<<" ";
                st.pop();
            }
            cout<<endl;
        }
    }
    void bellmanford(int s, int d)
    {
        for(int i=0; i<=n; i++)
        {
            dis[i] = 1000000;
            par[i] = -1;
        }
        dis[s] = 0;
        for(int i=1; i<=n; i++)
        {
            int c=0;
            for(int j=0; j<=n; j++)
            {
                for(int k=0; k<adjList[j].size(); k++)
                {
                    if(dis[adjList[j][k].first]> dis[j]+adjList[j][k].second)
                    {
                        dis[adjList[j][k].first] =  dis[j]+adjList[j][k].second;
                        par[adjList[j][k].first] = j;
                        c++;
                    }
                }
            }
            if(c==0)
                break;
        }
        int c=0;
        for(int j=0; j<=n; j++)
        {
            for(int k=0; k<adjList[j].size(); k++)
            {
                if(dis[adjList[j][k].first]> dis[j]+adjList[j][k].second)
                {
                    dis[adjList[j][k].first] =  dis[j]+adjList[j][k].second;
                    par[adjList[j][k].first] = j;
                    c++;
                }
            }
        }
        if(c==0)
        {
            if(dis[d]==1000000)
            {
                cout<<"No shortest Path Possible\n";
            }
            else
            {
                cout<<"Shortest Distance: "<<dis[d]<<endl;
                stack<int> st;
                st.push(d);
                while(par[d]!=-1)
                {
                    st.push(par[d]);
                    d = par[d];
                }
                while(!st.empty())
                {
                    cout<<st.top()<<" ";
                    st.pop();
                }
                cout<<endl;
            }
        }
        else
            cout<<"contains negetive cycle\n";
    }
    void primesMST()
    {
        for(int i=0; i<=n; i++)
        {
            explore[i] = false;
            par[i] = -1;
        }
        priority_queue< pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > pq;
        pq.push(make_pair(0,1)); ///src = 1, weight =0
        dis[1] = 0;
        int mstCost = 0;
        while(!pq.empty())
        {
            int t = pq.top().second;
            if(!explore[t])
            {
                mstCost+=pq.top().first;
                for(int i=0; i<adjList[t].size(); i++)
                {
                    if(!explore[adjList[t][i].first])
                    {
                        par[adjList[t][i].first] = t;
                        dis[adjList[t][i].first] = dis[t] + adjList[t][i].second;
                        pq.push(make_pair(adjList[t][i].second,adjList[t][i].first));
                    }
                }
                explore[t] = true;
            }
            pq.pop();
        }
        cout<<mstCost<<endl;
        for(int i=0; i<=n; i++)
        {
            cout<<par[i]<<"-"<<i<<endl;
        }
    }
};

class MyGraph
{
    int v,*par,*rnk;
    double *wgt;
    bool *explore;
    vector<pair<int, double>> *adjList;
    vector<pair<double,pair<int, int>>> edgeList;
    vector<pair<int, int>> selectedEdge;
public:
    MyGraph(int v)
    {
        this->v = v;
        par = new int[v+1];
        wgt = new double[v+1];
        rnk = new int[v+1];
        explore = new bool[v+1];
        adjList = new vector<pair<int, double>>[v+1];
    }
    ~MyGraph()
    {
        delete[] adjList;
        delete[] par;
        delete[] wgt;
        delete[] rnk;
        delete[] explore;
    }
    void addEdge(int p, int q, double w)
    {
        adjList[p].push_back(make_pair(q,w));
        adjList[q].push_back(make_pair(p,w));
        edgeList.push_back(make_pair(w,make_pair(p,q)));
    }

    double primesMST()
    {
        for(int i=0; i<=v; i++)
        {
            explore[i] = false;
            par[i] = -1;
            wgt[i] = 10000000;
        }
        priority_queue< pair<double, int>, vector <pair<double, int>>, greater<pair<double, int>> > pq; ///min heap
        pq.push(make_pair(0,0)); ///src = 0, cost =0
        double minCost = 0;
        selectedEdge.clear();
        while(!pq.empty())
        {
            int t = pq.top().second;
            double w = pq.top().first;
            pq.pop();
            if(!explore[t])
            {
                if(par[t]!=-1)
                {
                    minCost+=w;
                    selectedEdge.push_back(make_pair(par[t],t));
                }
                for(int i=0; i<adjList[t].size(); i++)
                {
                    if(!explore[adjList[t][i].first] && wgt[adjList[t][i].first]>adjList[t][i].second)
                    {
                        par[adjList[t][i].first] = t;
                        wgt[adjList[t][i].first]  = adjList[t][i].second;
                        pq.push(make_pair(adjList[t][i].second,adjList[t][i].first));
                    }
                }
                explore[t] = true;
            }

        }
        return minCost;
    }

    ///For kruskals
    int findSet(int x)
    {
        if(x == par[x])
            return x;
        return par[x] = findSet(par[x]);
    }

    void make_union(int x, int y)
    {
        int p1 = findSet(x);
        int p2 = findSet(y);
        if(p1!=p2)
        {
            if(rnk[p1]==rnk[p2])
            {
                par[p2] = p1;
                rnk[p1]+=1;
            }
            else if(rnk[p1]>rnk[p2])
                par[p2] = p1;
            else
                par[p1] = p2;
        }
    }
    double kruskalsMST()
    {
        for(int i=0; i<=v; i++)
        {
            par[i] = i;
            rnk[i] = 0;
        }
        sort(edgeList.begin(),edgeList.end());
        double minCOst=0;
        selectedEdge.clear();
        for(int i=0; i<edgeList.size(); i++)
        {
            if(findSet(edgeList[i].second.first)!=findSet(edgeList[i].second.second))
            {
                minCOst+=edgeList[i].first;
                selectedEdge.push_back(make_pair(edgeList[i].second.first,edgeList[i].second.second));
                make_union(edgeList[i].second.first,edgeList[i].second.second);
            }
        }
        return minCOst;
    }

    void task1()
    {
        cout<<"Cost of the minimum spanning tree :"<<primesMST()<<endl;
        cout<<"List of edges selected by Prim's:{("<<selectedEdge[0].first<<","<<selectedEdge[0].second<<")";
        for(int i=1; i<selectedEdge.size(); i++)
        {
            cout<<",("<<selectedEdge[i].first<<","<<selectedEdge[i].second<<")";
        }
        cout<<"}\n";
        kruskalsMST();
        cout<<"List of edges selected by Kruskal's:{("<<selectedEdge[0].first<<","<<selectedEdge[0].second<<")";
        for(int i=1; i<selectedEdge.size(); i++)
        {
            cout<<",("<<selectedEdge[i].first<<","<<selectedEdge[i].second<<")";
        }
        cout<<"}\n";
    }
};



class Graph4
{
    int n;
    int **adjMatrix,**par;
public:
    Graph4(int n)
    {
        this->n = n;
        adjMatrix = new int*[n+1];
        par = new int*[n+1];
        for(int i=0; i<=n; i++)
        {
            adjMatrix[i] = new int[n+1];
            par[i] = new int[n+1];
            for(int j=0; j<=n; j++)
            {
                if(i==j)
                    adjMatrix[i][j] = 0;
                else
                    adjMatrix[i][j] = 10000000;
            }
        }
    }
    ~Graph4()
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

    void printShortestPath(int i, int j)
    {
        if(i==j)
            cout<<i<<" ";
        else if(par[i][j]==-1)
        {
            cout<<"No path from "<<i<<" to "<<j<<" exist\n";
        }
        else
        {
            printShortestPath(i,par[i][j]);
            cout<<j<<" ";
        }
    }

    void floydWarshall()
    {
        int D[n+1][n+1];
        for(int i=0; i<=n; i++)
        {
            for(int j=0; j<=n; j++)
            {
                D[i][j] = adjMatrix[i][j];
                if(adjMatrix[i][j]==0 || adjMatrix[i][j]==10000000)
                {
                    par[i][j] = -1;
                }
                else
                    par[i][j] = i;
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
                        par[i][j] = par[k][j];
                    }
                }
            }
        }
        cout<<"Shortest distance matrix\n";
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                cout<<D[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                printShortestPath(i,j);
                cout<<endl;
            }
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
                if(adjMatrix[i][j]==0 || adjMatrix[i][j]==10000000)
                {
                    par[i][j] = -1;
                }
                else
                    par[i][j] = i;
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
                            if(k!=j)
                                par[i][j] = k;
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
                cout<<L[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                printShortestPath(i,j);
                cout<<endl;
            }
        }
    }

    void Dijkstra(int s, int d)
    {
        int par[n+1],dis[n+1];
        for(int i=0; i<=n; i++)
        {
            dis[i] = INT_MAX;
            par[i] = -1;
        }
        priority_queue< pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > pq;
        dis[s] = 0;
        pq.push(make_pair(0,s));
        while(!pq.empty())
        {
            int t = pq.top().second;
            pq.pop();
            for(int i=0; i<=n; i++)
            {
                if(dis[i] > dis[t] + adjMatrix[t][i])
                {
                    dis[i] = dis[t] + adjMatrix[t][i];
                    par[i] = t;
                    pq.push(make_pair(dis[i],i));
                }
            }
        }


        if(dis[d]==INT_MAX)
        {
            cout<<"No shortest Path Possible\n";
        }
        else
        {
            cout<<"Shortest path cost: "<<dis[d]<<endl;
            stack<int> st;
            st.push(d);
            while(par[d]!=-1)
            {
                st.push(par[d]);
                d = par[d];
            }
            while(!st.empty())
            {
                if(st.size()==1)
                    cout<<st.top()<<endl;
                else
                    cout<<st.top()<<"->";

                st.pop();
            }
        }
    }

    void bellmanford(int s, int d)
    {
        int par[n+1],dis[n+1];
        for(int i=0; i<=n; i++)
        {
            dis[i] = INT_MAX;
            par[i] = -1;
        }
        dis[s] = 0;
        for(int i=1; i<=n; i++)
        {
            int c=0;
            for(int j=0; j<=n; j++)
            {
                for(int k=0; k<=n; k++)
                {
                    if(dis[k]> dis[j]+adjMatrix[j][k])
                    {
                        dis[k] =  dis[j]+adjMatrix[j][k];
                        par[k] = j;
                        c++;
                    }
                }
            }
            if(c==0)
                break;
        }
        int c=0;
        for(int j=0; j<=n; j++)
        {
            for(int k=0; k<=n; k++)
            {
                if(dis[k]> dis[j]+adjMatrix[j][k])
                {
                    dis[k] =  dis[j]+adjMatrix[j][k];
                    par[k] = j;
                    c++;
                }
            }
        }
        if(c==0)
        {
            if(dis[d]==INT_MAX)
            {
                cout<<"No shortest Path Possible\n";
            }
            else
            {
                cout<<"The graph does not contain a negative cycle\n";
                cout<<"Shortest path cost: "<<dis[d]<<endl;
                stack<int> st;
                st.push(d);
                while(par[d]!=-1)
                {
                    st.push(par[d]);
                    d = par[d];
                }
                while(!st.empty())
                {
                    if(st.size()==1)
                        cout<<st.top()<<endl;
                    else
                        cout<<st.top()<<"->";

                    st.pop();
                }
            }
        }
        else
            cout<<"The graph contains a negative cycle\n";
    }
};



int main()
{
    int n,s,u,v,w;
    cin>>n>>s;

    ///graph 1 start : DFS & Others
    /*
    Graph1 g(n);
    while(s--)
    {
        cin>>u>>v;
        g.addEdge(u,v);
        g.addRevEdge(v,u);
    }
    if(g.isPath(1,n))
    {
        cout<<"Has a path\n";
    }
    else
    {
        cout<<"No path possible\n";
    }
    g.SCC(true);
    if(g.isCycle())
        cout<<"Contain atleast one cycle\n";
    else
        cout<<"No cycle found\n";
    g.topologicalSort();
    */
    ///graph 1 end

    ///graph 2 start: BFS & others
    /*
    Graph2 g(n);
    while(s--)
    {
        cin>>u>>v;
        g.addUnDirectedEdge(u,v);
    }
    ///cin>>u>>v;
    cout<<g.distance(1,n)<<endl;
    g.shortestPath(1,n);
    if(g.isBipartite())
        cout<<"Bipartite\n";
    else
        cout<<" Not Bipartite\n";
    */
    ///graph 2 end

    Graph4 g(n);
    while(s--)
    {
        cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    g.APSP_MM();
    //cin>>u>>v;
    //g.shortestPath(u,v);
    //g.bellmanford(1,n);
    //g.primesMST();
}
