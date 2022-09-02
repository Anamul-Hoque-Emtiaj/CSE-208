#include<iostream>
using namespace std;

struct edge
{
    int dest;
    edge *next;
};

class graph
{
public:
    int n,*level,*par;
    edge **adjList

    graph(int n)
    {
        this->n = n;
        par = new int[n+1];
        level = new int[n+1];
        adjList = new edge*[n+1];
    }
    void addEdge(int u, int v)
    {
        if(adjList[u]==NULL)
        {
            edge *t = new edge();
            t->dest = v;
            t->next = NULL;
            adjList[u] = v;
        }
        else
        {
            edge *h = adjList[u];
            while(h->next!=NULL)
            {
                h = h->next;
            }
            edge *t = new edge();
            t->dest = v;
            t->next = NULL;
            h->next = t;
        }
    }
    void bfs(ll s)
    {
        for(int i=0; i<=n; i++)
        {
            level[i] = 1000000;
            par[i] = -1;
        }
        level[s] = 0;
        queue<int> myQ;
        myQ.push(s);
        while(!myQ.empty())
        {
            ll f = myQ.front();
            myQ.pop();
            node *t = arr[f];
            while(t!=NULL)
            {
                if(level[t->value]==1000000)
                {
                    level[t->value] = level[f] + 1;
                    par[t->value] = f;
                    myQ.push(t->value);
                }
                t = t->next;
            }
        }
    }
};

int main()
{
    int n;
    cin>>n;
}
