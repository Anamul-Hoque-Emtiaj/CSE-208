#include<bits/stdc++.h>
using namespace std;

template <typename T>
class node
{
public:
    T key;
    int degree;
    node *par,*left,*right,*child;
    bool mark;

    node()
    {

    }
    node(T v)
    {
        this->key = v;
        this->degree = 0;
        this->mark = false;
        this->par = NULL;
        this->child = NULL;
        this->left = this;
        this->right = this;
    }

};

template <typename T>
class  FibonacciHeap
{
public:
    int n;
    node<T> *mini;
    FibonacciHeap()
    {
        n = 0;
        mini = NULL;
    }

    ///insert
    void Insert(T v)
    {
        node<T>* new_node = new node<T>(v);
        if(mini==NULL)
            mini = new_node;
        else
        {
            (mini->left)->right = new_node;
            new_node->right = mini;
            new_node->left = mini->left;
            mini->left = new_node;
            if(new_node->key < mini->key)
                mini = new_node;
        }
        n++;
    }
    ///union
    FibonacciHeap<T>* Union(FibonacciHeap<T> *H)
    {
        if(H->mini==NULL)
            return this;

        (mini->right)->left = (H->mini)->left;
        ((H->mini)->left)->right = mini->right;
        mini->right = (H->mini);
        (H->mini)->left = mini;
        if((H->mini)->key < mini->key)
            mini = (H->mini);
        n+=H->n;
        return this;
    }
    void link(node<T> *x, node<T> *y)
    {
        (y->left)->right = y->right;
        (y->right)->left = y->left;

        y->par = x;
        y->left = y;
        y->right = y;
        y->mark = false;

        if(x->child==NULL)
            x->child = y;
        else
        {
            ((x->child)->left)->right = y;
            y->right = x->child;
            y->left = (x->child)->left;
            (x->child)->left = y;
            if (y->key < (x->child)->key)
                (x->child) = y;
        }
        x->degree = x->degree+1;
    }

    void consolidate()
    {
        int temp1 = (log(n)) / (log(1.62));
        node<T>* arr[temp1+1];
        for(int i = 0; i <= temp1; i++)
            arr[i] = NULL;

        node<T>* ptr1 = mini->right;
        while(1)
        {
            int d = ptr1->degree;
            while(arr[d]!=NULL)
            {
                node<T> *ptr2 = arr[d];
                if(ptr2->key < ptr1->key)
                    swap(ptr1,ptr2);

                if(ptr2 == mini)
                    mini = ptr1;

                link(ptr1, ptr2);

                if(ptr1->right == ptr1)
                    mini = ptr1;
                arr[d] = NULL;
                d++;
            }
            arr[d] = ptr1;
            if(ptr1==mini)
                break;

            ptr1 = ptr1->right;
        }
        mini = NULL;

        for(int i = 0; i <= temp1; i++)
        {
            if(arr[i]!=NULL)
            {
                arr[i]->left = arr[i];
                arr[i]->right = arr[i];

                if(mini != NULL)
                {
                    (mini->left)->right = arr[i];
                    arr[i]->right = mini;
                    arr[i]->left = mini->left;
                    mini->left = arr[i];
                    if (arr[i]->key < mini->key)
                        mini = arr[i];
                }
                else
                {
                    mini = arr[i];
                }

                if(mini == NULL)
                    mini = arr[i];
                else if (arr[i]->key < mini->key)
                    mini = arr[i];
            }
        }
    }

    void Extract_min()
    {
        if(mini!=NULL)
        {
            node<T>* temp = mini;
            if(temp->child!=NULL)
            {
                node<T> *ptr1 = temp->child;
                while(1)
                {
                    ptr1->par = NULL;

                    (mini->left)->right = ptr1;
                    ptr1->right = mini;
                    ptr1->left = mini->left;
                    mini->left = ptr1;
                    if (ptr1->key < mini->key)
                        mini = ptr1;

                    if(ptr1==temp->child)
                        break;
                    ptr1 = ptr1->right;
                }
            }
            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;
            mini = temp->right;
            if(temp == temp->right && temp->child == NULL)
                mini = NULL;
            else
            {
                mini = temp->right;
                consolidate();
            }
            n--;
        }
    }
    void cut(node<T>* x, node<T>* y)
    {
        if(x == x->right)
            y->child = NULL;

        (x->left)->right = x->right;
        (x->right)->left = x->left;
        if(x == y->child)
            y->child = x->right;

        x->par = NULL;
        x->mark = false;
        x->right = x;
        x->left = x;

        (mini->left)->right = x;
        x->right = mini;
        x->left = mini->left;
        mini->left = x;

        y->degree = y->degree - 1;
    }

    void cascading_cut(node<T>* y)
    {
        node<T>* x = y->par;
        if(x != NULL)
        {
            if (y->mark)
            {
                cut(y, x);
                cascading_cut(x);
            }
            else
            {
                y->mark = true;
            }
        }
    }

    void Decrease_key(node<T>* temp, int v)
    {
        if(mini!=NULL && temp!=NULL)
        {
            temp->key = v;
            node<T>* temp2 = temp->par;
            if (temp2 != NULL && temp->key < temp2->key)
            {
                cut(temp, temp2);
                cascading_cut(temp2);
            }
            if (temp->key < mini->key)
                mini = temp;
        }
    }

    T Min()
    {
        return mini->key;
    }

    void Delete(node<T> *temp)
    {
        Decrease_key(temp,(Min()->key)-5);
        Extract_min();
    }

    bool empty()
    {
        return mini==NULL;
    }
};

int main()
{

}

