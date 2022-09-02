#include<bits/stdc++.h>
#include "HashTable.h"
using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;


    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

int nextPrime(int n)
{
    if(isPrime(n))
        return n;
    if (n <= 1)
        return 2;

    int prime = n;
    bool found = false;

    while (!found)
    {
        prime++;

        if (isPrime(prime))
            found = true;
    }

    return prime;
}

string generateString(int len)
{
    string word;

    for(int i = 0; i < len; i++)
    {
        char c = 'a' + rand() % 26;
        word.push_back(c);
    }

    return word;
}

int Hash1(string s, int n)
{
    int p = 31;
    const int m = 1e9 + 9;
    long long val = 0, pPow = 1;

    for (char c : s)
    {
        val = (val + (c - 'a' + 1) * pPow) % m;
        pPow = (pPow * p) % m;
    }
    return val%n;

}

int Hash2(string s, int n)
{
    long sum = 0, mul = 1;
    for (int i = 0; i < s.length(); i++)
    {
        mul = (i % 4 == 0) ? 1 : mul * 256;
        sum += s[i] * mul;
    }
    return (int)(abs(sum) % n);
}

void testHashFunc(vector<string> str)
{
    int n = str.size();
    vector<int>v;
    for(int j=0; j<n; j++)
    {
        v.push_back(Hash1(str[j],n));
    }

    set<int> s(v.begin(), v.end());
    cout<<"Hash1 function test for n = "<<n<<" : "<<((1.00*s.size())/(1.00*n))<<endl;
    v.clear();

    for(int j=0; j<n; j++)
    {
        v.push_back(Hash2(str[j],n));
    }

    set<int> s1(v.begin(), v.end());
    cout<<"Hash2 function test for n = "<<n<<" : "<<((1.00*s1.size())/(1.00*n))<<endl;

    /*for(int j=0; j<n; j++)
    {
        cout<<str[j]<<" "<<Hash1(str[j],n)<<" "<<Hash2(str[j],n)<<endl;
    }*/
}


int main()
{
    cout<<"Enter the Value of N: ";
    int n;
    cin>>n;
    n = nextPrime(n);

    double sc_arr[6][2], lp_arr[6][4], qp_arr[6][4], dh_arr[6][4];
    HashTable<int> sc(n,SeparateChaining), lp(n,LinearProbing), qp(n,QuadraticProbing), dh(n,DoubleHashing);


    for(int i=0; i<6; i++)
    {
        int s = (0.4 + i*0.1)*n;
        set<string> st;
        while(1)
        {
            if(st.size()==s)
                break;
            st.insert(generateString(7));
        }
        vector<string> str = vector<string>(st.begin(), st.end());
        //testHashFunc(str);
        for(int j=0; j<str.size(); j++)
        {
            sc.Insert(str[j],j+1);
            lp.Insert(str[j],j+1);
            qp.Insert(str[j],j+1);
            dh.Insert(str[j],j+1);
        }

        double t_sc=0, t_lp = 0, t_qp = 0, t_dh = 0;
        int pc_lp = 0, pc_qp = 0, pc_dh = 0;

        int si = (s*0.1);
        for(int j=1; j<=si; j++)
        {
            int in = rand()%s;
            auto start = chrono::high_resolution_clock::now();
            pair<int,int> psc = sc.Search(str[in]);
            auto stop = chrono::high_resolution_clock::now();
            t_sc += (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

            start = chrono::high_resolution_clock::now();
            pair<int,int> plp = lp.Search(str[in]);
            stop = chrono::high_resolution_clock::now();
            t_lp += (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
            pc_lp += plp.second;

            start = chrono::high_resolution_clock::now();
            pair<int,int> pqp = qp.Search(str[in]);
            stop = chrono::high_resolution_clock::now();
            t_qp += (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
            pc_qp += pqp.second;

            start = chrono::high_resolution_clock::now();
            pair<int,int> pdh = dh.Search(str[in]);
            stop = chrono::high_resolution_clock::now();
            t_dh += (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
            pc_dh += pdh.second;

        }
        sc_arr[i][0] = 1.00*t_sc/si;

        lp_arr[i][0] = 1.00*t_lp/si;
        lp_arr[i][1] = 1.00*pc_lp/si;

        qp_arr[i][0] = 1.00*t_qp/si;
        qp_arr[i][1] = 1.00*pc_qp/si;

        dh_arr[i][0] = 1.00*t_dh/si;
        dh_arr[i][1] = 1.00*pc_dh/si;

        for(int j=1; j<=si; j++)
        {
            int in = rand()%s;
            sc.Delete(str[in]);
            lp.Delete(str[in]);
            qp.Delete(str[in]);
            dh.Delete(str[in]);
        }

        t_sc=0, t_lp = 0, t_qp = 0, t_dh = 0;
        pc_lp = 0, pc_qp = 0, pc_dh = 0;

        for(int j=1; j<=si; j++)
        {
            int in = rand()%s;
            auto start = chrono::high_resolution_clock::now();
            pair<int,int> psc = sc.Search(str[in]);
            auto stop = chrono::high_resolution_clock::now();
            t_sc += (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

            start = chrono::high_resolution_clock::now();
            pair<int,int> plp = lp.Search(str[in]);
            stop = chrono::high_resolution_clock::now();
            t_lp += (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
            pc_lp += plp.second;

            start = chrono::high_resolution_clock::now();
            pair<int,int> pqp = qp.Search(str[in]);
            stop = chrono::high_resolution_clock::now();
            t_qp += (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
            pc_qp += pqp.second;

            start = chrono::high_resolution_clock::now();
            pair<int,int> pdh = dh.Search(str[in]);
            stop = chrono::high_resolution_clock::now();
            t_dh += (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
            pc_dh += pdh.second;

        }

        sc_arr[i][1] = 1.00*t_sc/si;

        lp_arr[i][2] = 1.00*t_lp/si;
        lp_arr[i][3] = 1.00*pc_lp/si;

        qp_arr[i][2] = 1.00*t_qp/si;
        qp_arr[i][3] = 1.00*pc_qp/si;

        dh_arr[i][2] = 1.00*t_dh/si;
        dh_arr[i][3] = 1.00*pc_dh/si;

        sc.Clear();
        lp.Clear();
        qp.Clear();
        dh.Clear();
    }

    ///printing part
    ofstream output;
    output.open("out.csv");
    output<<fixed<<setprecision(6);

    output<<"\n\n,  ,Table 1: Performance of separate chaining in various load factors\n";
    output<<", ,  , Before deletion, After deletion\n";
    output<<", , Load factor,Avg search time,Avg search time\n";

    for(int i=0; i<6; i++)
    {
        output<<", ,"<<(0.4+i*0.1)<<","<<sc_arr[i][0]<<","<<sc_arr[i][1]<<"\n";
    }

    output<<"\n\n,  ,Table 2: Performance of linear probing in various load factors\n";
    output<<", ,  , Before deletion, , After deletion, \n";
    output<<", , Load factor,Avg search time,Avg number of probes,Avg search time,Avg number of probes\n";

    for(int i=0; i<6; i++)
    {
        output<<", ,"<<(0.4+i*0.1)<<","<<lp_arr[i][0]<<","<<lp_arr[i][1]<<","<<lp_arr[i][2]<<","<<lp_arr[i][3]<<"\n";
    }

    output<<"\n\n,  ,Table 3: Performance of quadratic probing in various load factors\n";
    output<<", ,  , Before deletion, , After deletion, \n";
    output<<", , Load factor,Avg search time,Avg number of probes,Avg search time,Avg number of probes\n";

    for(int i=0; i<6; i++)
    {
        output<<", ,"<<(0.4+i*0.1)<<","<<qp_arr[i][0]<<","<<qp_arr[i][1]<<","<<qp_arr[i][2]<<","<<qp_arr[i][3]<<"\n";
    }

    output<<"\n\n,  ,Table 4: Performance of double hashing in various load factors\n";
    output<<", ,  , Before deletion, , After deletion, \n";
    output<<", , Load factor,Avg search time,Avg number of probes,Avg search time,Avg number of probes\n";

    for(int i=0; i<6; i++)
    {
        output<<", ,"<<(0.4+i*0.1)<<","<<dh_arr[i][0]<<","<<dh_arr[i][1]<<","<<dh_arr[i][2]<<","<<dh_arr[i][3]<<"\n";
    }


    for(int i=0; i<6; i++)
    {
        output<<"\n\n,  ,Table "<<i+5<<": Performance of various collision resolution methods in load factor "<<(0.4+0.1*i)<<"\n";
        output<<", ,  , Before deletion, , After deletion, \n";
        output<<", , Method,Avg search time,Avg number of probes,Avg search time,Avg number of probes\n";

        output<<", , Separate chaining,"<<sc_arr[i][0]<<",N/A,"<<sc_arr[i][1]<<",N/A\n";
        output<<", , Linear Probing,"<<lp_arr[i][0]<<","<<lp_arr[i][1]<<","<<lp_arr[i][2]<<","<<lp_arr[i][3]<<"\n";
        output<<", , Quadratic Probing,"<<qp_arr[i][0]<<","<<qp_arr[i][1]<<","<<qp_arr[i][2]<<","<<qp_arr[i][3]<<"\n";
        output<<", , Double Hashing,"<<dh_arr[i][0]<<","<<dh_arr[i][1]<<","<<dh_arr[i][2]<<","<<dh_arr[i][3]<<"\n";
    }
    cout<<"done";
}

