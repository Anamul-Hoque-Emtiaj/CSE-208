#include<bits/stdc++.h>
using namespace std;

class Mat
{
public:
    vector<vector<int>> ar;
    int n,r,c,b,ord;
    Mat()
    {

    }
    Mat(int n, int r, int c,int ord)
    {
        this->n = n;
        this->r = r;
        this->c = c;
        this->ord = ord;
        ar.resize(n);
        for(int i=0; i<n; i++)
            ar[i].resize(n);
    }

    void addElement(int v, int i, int j)
    {
        ar[i][j] = v;
    }

    void calculateBound()
    {
        int t = 0;
        for(int i=0; i<=r; i++)
        {
            int cnt = 0;
            for(int j=c+1; j<n; j++)
            {
                if(ar[i][j]!=0)
                    cnt++;
            }
            if(cnt!=0)
            {
                int ri = (c-i+1) + cnt;
                t = max(t,ri);
            }
            int li = 0;
            for(int j=i; j>=0; j--)
            {
                if(ar[i][j]!=0)
                    li = (i-j+1);
            }
            int ri = 0;
            for(int j=i; j<=c; j++)
            {
                if(ar[i][j]!=0)
                    ri = (j-i+1);
            }
            t = max(t,max(ri,li));
        }

        for(int i=0; i<=c; i++)
        {
            int cnt = 0;
            for(int j=r+1; j<n; j++)
            {
                if(ar[j][i]!=0)
                    cnt++;
            }
            if(cnt!=0)
            {
                int ci = (r-i+1) + cnt;
                t = max(t,ci);
            }
            int ui = 0;
            for(int j=i; j>=0; j--)
            {
                if(ar[j][i]!=0)
                    ui = (i-j+1);
            }
            int di = 0;
            for(int j=i; j<=r; j++)
            {
                if(ar[j][i]!=0)
                    di = (j-i+1);
            }
            t = max(t,max(ui,di));
        }

        for(int i=r+1; i<n; i++)
        {
            int s=0;
            for(int j=0; j<n; j++)
            {
                if(ar[i][j]!=0)
                    s+=1;
            }
            t = max(t,(s+1)/2);
        }
        for(int i=c+1; i<n; i++)
        {
            int s=0;
            for(int j=0; j<n; j++)
            {
                if(ar[j][i]!=0)
                    s+=1;
            }
            t = max(t,(s+1)/2);
        }
        b = t;
    }
    void getMat(int **arr)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                arr[i][j] = ar[i][j];
            }
        }
    }
    void test()
    {
        cout<<r<<" "<<c<<endl;
    }
    void showMat()
    {
        //cout<<r<<" "<<c<<" "<<b<<endl;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(ar[i][j]==0)
                    cout<<"0 ";
                else
                    cout<<"X ";
            }
            cout<<endl;
        }
    }
};

struct compare
{
    bool operator()(const Mat& M1, const  Mat& M2)
    {
        if(M1.b==M2.b)
        {
            if((M1.r+M1.c)==(M2.r+M2.c))

                return M1.ord<M2.ord;
            else
                return (M1.r+M1.c)<(M2.r+M2.c);
        }
        else
        {
            return M1.b>M2.b;
        }

    }
};


int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n,cnt=0;
    cin>>n;
    Mat m(n,-1,-1,cnt++);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            char ch;
            cin>>ch;
            if(ch=='0')
                m.ar[i][j] = 0;
            else
                m.ar[i][j] = 1;
        }
    }
    priority_queue<Mat,vector<Mat>,compare> pq;
    m.calculateBound();
    pq.push(m);
    Mat tmp = pq.top();
    while(!(pq.top().r==n-2 && pq.top().c==n-2))
    {
        int r = pq.top().r;
        int c = pq.top().c;
        Mat mt = pq.top();
        pq.pop();
        if(r==c)
        {
            for(int t = c+1; t<n; t++)
            {
                Mat m(n,r,c+1,cnt++);
                for(int i=0; i<n; i++)
                {
                    for(int j=0; j<=c; j++)
                    {
                        m.addElement(mt.ar[i][j],i,j);
                    }
                }
                int in = c+1;
                for(int i=0; i<n; i++)
                {
                    m.addElement(mt.ar[i][t],i,in);
                }
                in = c+2;
                for(int i=c+1; i<n; i++)
                {
                    for(int j=0; j<n; j++)
                    {
                        if(i!=t)
                        {
                            m.addElement(mt.ar[j][i],j,in);
                        }

                    }
                    if(i!=t)
                    {
                        in++;
                    }
                }
                m.calculateBound();
                pq.push(m);
            }

        }
        else
        {
            for(int t = r+1; t<n; t++)
            {
                Mat m(n,r+1,c,0);
                for(int i=0; i<=r; i++)
                {
                    for(int j=0; j<n; j++)
                    {
                        m.addElement(mt.ar[i][j],i,j);
                    }
                }
                for(int i=0; i<n; i++)
                {
                    m.addElement(mt.ar[t][i],r+1,i);
                }
                int in = r+2;
                for(int i=r+1; i<n; i++)
                {
                    for(int j=0; j<n; j++)
                    {
                        if(i!=t)
                        {
                            m.addElement(mt.ar[i][j],in,j);
                        }

                    }
                    if(i!=t)
                    {
                        in++;
                    }
                }
                m.calculateBound();
                pq.push(m);
            }
        }
    }
    m = pq.top();
    cout<<m.b<<endl;
    m.showMat();
}
