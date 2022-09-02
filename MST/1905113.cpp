#include<bits/stdc++.h>
using namespace std;

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

int main()
{
    freopen("mst.in", "r", stdin);
    int v,e;
    cin>>v>>e;
    MyGraph g(v);
    while(e--)
    {
        int p,q;
        double w;
        cin>>p>>q>>w;
        g.addEdge(p,q,w);
    }
    g.task1();
}
