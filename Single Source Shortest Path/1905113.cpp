#include<bits/stdc++.h>
using namespace std;

class Graph
{
    int n, *dis,*par;
    vector<pair<int, int>> *adjList;
public:
    Graph(int n)
    {
        this->n = n;
        adjList = new vector<pair<int, int>>[n+1];
        dis = new int[n+1];
        par = new int[n+1];
    }
    ~Graph()
    {
        delete[] adjList;
        delete[] dis;
        delete[] par;
    }
    void addEdge(int u, int v, int w)
    {
        adjList[u].push_back(make_pair(v,w));
    }
    void Dijkstra(int s, int d)
    {
        for(int i=0; i<=n; i++)
        {
            dis[i] = 10000000;
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


        if(dis[d]==10000000)
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
        for(int i=0; i<=n; i++)
        {
            dis[i] = 10000000;
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
            if(dis[d]==10000000)
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
    int n,m;
    cin>>n>>m;
    Graph g(n);
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    int s,d;
    cin>>s>>d;
    //g.Dijkstra(s,d);
    g.bellmanford(s,d);
}

