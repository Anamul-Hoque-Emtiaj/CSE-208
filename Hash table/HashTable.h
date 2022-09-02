#include<bits/stdc++.h>
using namespace std;

enum TYPE {SeparateChaining, LinearProbing, QuadraticProbing, DoubleHashing};

template <typename T>
class node
{
public:
    pair<string, T> val;
    node* next;
    node()
    {

    }
    node(string str, T v)
    {
        val = make_pair(str,v);
        next = NULL;
    }
};

template <typename T>
class HashTable
{
    int n;
    TYPE ty;
    vector<node<T>*> tableSC;
    vector<pair<string, T>> tableP;

    pair<string, T> NILL;
    pair<string, T> DELETED;
    T EMPTY;

    int hash1(string s)
    {
        long sum = 0, mul = 1;
        for (int i = 0; i < s.length(); i++)
        {
            mul = (i % 4 == 0) ? 1 : mul * 256;
            sum += s[i] * mul;
        }
        return (int)(abs(sum) % n);
    }

    int hash2(string s)
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

    int doubleHash(string str, int it)
    {
        return (hash1(str)+it*hash2(str))%n;
    }

    int linearProbing(string str, int it)
    {
        return (hash1(str) + it)%n;
    }

    int quadraticProbing(string str, int it)
    {
        int c1 = 17, c2 = 19;
        return (hash1(str) + c1*it + c2*it*it)%n;
    }

    void separateChainedHashInsert(string str, T val)
    {
        T f = separateChainedHashSearch(str).first;
        if(f==EMPTY)
        {
            int in = hash1(str);
            if(tableSC[in]==NULL)
            {
                node<T> *nn = new node<T>(str,val);
                tableSC[in] = nn;
            }
            else
            {
                node<T> *nn = new node<T>(str,val);
                nn->next = tableSC[in];
                tableSC[in] = nn;
            }
            ///cout<<"Insert: "<<str<<" "<<val<<endl;
        }
        else
            cout<<"Insert Error: Key already exist!\n";
    }

    void openAddressingHashInsert(string str, T val)
    {
        T f = openAddressingHashSearch(str).first;
        if(f==EMPTY)
        {
            int in=-1;
            for(int i=0; i<n; i++)
            {
                int tmp;
                if(ty==LinearProbing)
                    tmp = linearProbing(str,i);
                else if(ty==QuadraticProbing)
                    tmp = quadraticProbing(str,i);
                else
                    tmp = doubleHash(str,i);
                if(tableP[tmp]==NILL || tableP[tmp]==DELETED)
                {
                    in = tmp;
                    break;
                }
            }
            if(in!=-1)
            {
                tableP[in] = make_pair(str, val);
                ///cout<<"Insert: "<<str<<" "<<val<<endl;
            }
            else
                cout<<"Insert Error: Hash table overflowed!\n";
        }
        else
            cout<<"Insert Error: Key already exist!\n";

    }

    pair<T,int> separateChainedHashSearch(string str)
    {
        int in = hash1(str);
        if(tableSC[in]==NULL)
        {
            ///cout<<"Search: "<<str<<" Not found\n";
            return make_pair(EMPTY,-1);
        }
        else
        {
            node<T> *tmp = tableSC[in];
            while(1)
            {
                if(tmp->val.first==str)
                {
                    ///cout<<"Search: "<<str<<" "<<tmp->val.second<<endl;
                    return make_pair(tmp->val.second,-1);
                }
                if(tmp->next==NULL)
                    break;
                tmp = tmp->next;
            }
            ///cout<<"Search: "<<str<<" Not found\n";
            return make_pair(EMPTY,-1);
        }
    }

    pair<T,int> openAddressingHashSearch(string str)
    {
        T f = EMPTY;
        int pr;
        for(int i=0; i<n; i++)
        {
            int tmp;
            if(ty==LinearProbing)
                tmp = linearProbing(str,i);
            else if(ty==QuadraticProbing)
                tmp = quadraticProbing(str,i);
            else
                tmp = doubleHash(str,i);
            if(tableP[tmp].first==str)
            {
                f =  tableP[tmp].second;
                pr = i+1;
                break;
            }

            if(tableP[tmp]==NILL)
            {
                pr = i+1;
                break;
            }
        }
        /*if(f==EMPTY)
            cout<<"Search: "<<str<<" Not found\n";
        else
            cout<<"Search: "<<str<<" "<<f<<endl;*/
        return make_pair(f,pr);
    }

    void separateChainedHashDelete(string str)
    {
        T f = separateChainedHashSearch(str).first;
        if(f!=EMPTY)
        {
            int in = hash1(str);
            node<T> *tmp = tableSC[in];
            if(tmp->val.first==str)
                tableSC[in] = tmp->next;
            else
            {
                node<T> *prev;
                while(1)
                {
                    if(tmp->next->val.first==str)
                    {
                        prev = tmp;
                        break;
                    }
                    tmp = tmp->next;
                }
                prev->next = prev->next->next;
            }
            ///cout<<"Delete: "<<str<<endl;
        }
    }

    void openAddressingHashDelete(string str)
    {
        T f = openAddressingHashSearch(str).first;
        if(f!=EMPTY)
        {
            for(int i=0; i<n; i++)
            {
                int tmp;
                if(ty==LinearProbing)
                    tmp = linearProbing(str,i);
                else if(ty==QuadraticProbing)
                    tmp = quadraticProbing(str,i);
                else
                    tmp = doubleHash(str,i);
                if(tableP[tmp].first==str)
                {
                    tableP[tmp] = DELETED;
                    break;
                }
            }
            ///cout<<"Delete: "<<str<<endl;
        }
    }


public:
    HashTable(int n, TYPE ty)
    {
        this->n = n; ///array size--provided n should be prime
        this->ty = ty; ///Type of Collision Resolution method
        NILL = make_pair(NULL,-1);
        DELETED = make_pair(NULL,-2);
        EMPTY = (T) -3;
        tableSC.assign(this->n,NULL); /// for separate chaining
        tableP.assign(this->n, NILL); /// for open addressing

        /// never insert = NILL & deleted = DELETED
    }

    void Clear()
    {
        tableP.clear();
        tableSC.clear();
        tableSC.assign(n,NULL);
        tableP.assign(n, NILL);
    }

    void Insert(string str, T val)
    {
        if(ty==SeparateChaining)
            separateChainedHashInsert(str, val);
        else
            openAddressingHashInsert(str, val);
    }

    pair<T,int> Search(string str)
    {
        if(ty==SeparateChaining)
            return separateChainedHashSearch(str);
        else
            return openAddressingHashSearch(str);
    }

    void Delete(string str)
    {
        if(ty==SeparateChaining)
            separateChainedHashDelete(str);
        else
            openAddressingHashDelete(str);
    }
};

