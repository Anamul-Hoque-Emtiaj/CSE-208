#include<bits/stdc++.h>
using namespace std;

enum COLOR {RED, BLACK};

template <typename T>
class node
{
public:
    T val;
    node *par, *right, *left;
    COLOR color;
    node()
    {

    }
    node(T v, node<T> *temp)
    {
        val = v;
        par = left = right = temp;
        color = RED;
    }
};

template <typename T>
class RBT
{
    node<T>* root,*NILL;
    void leftRotate(node<T> *x)
    {
        node<T> *y = x->right;
        x->right = y->left;
        if(y->left!=NILL)
            y->left->par = x;
        y->par = x->par;
        if(x->par==NILL)
            root = y;
        else if(x==x->par->left)
            x->par->left = y;
        else
            x->par->right = y;
        y->left = x;
        x->par = y;
    }
    void rightRotate(node<T> *x)
    {
        node<T> *y = x->left;
        x->left = y->right;
        if(y->right!=NILL)
            y->right->par = x;
        y->par = x->par;
        if(x->par==NILL)
            root = y;
        else if(x==x->par->left)
            x->par->left = y;
        else
            x->par->right = y;
        y->right = x;
        x->par = y;
    }

    void InsertFixUp(node<T> *newNode)
    {
        while(newNode->par->color==RED)
        {
            if(newNode->par = newNode->par->par->left)
            {
                node<T>* uncle = newNode->par->par->right;
                if(uncle->color==RED)
                {
                    newNode->par->color = BLACK;
                    uncle->color = BLACK;
                    newNode->par->par = RED;
                    newNode = newNode->par->par;
                }
                else
                {
                    if(newNode = newNode->par->right)
                    {
                        newNode = newNode->par;
                        leftRotate(newNode);
                    }
                    newNode->par->color = BLACK;
                    newNode->par->par->color = RED;
                    rightRotate(newNode->par->par);
                }
            }
            else
            {
                node<T>* uncle = newNode->par->par->left;
                if(uncle->color==RED)
                {
                    newNode->par->color = BLACK;
                    uncle->color = BLACK;
                    newNode->par->par = RED;
                    newNode = newNode->par->par;
                }
                else
                {
                    if(newNode = newNode->par->left)
                    {
                        newNode = newNode->par;
                        rightRotate(newNode);
                    }
                    newNode->par->color = BLACK;
                    newNode->par->par->color = RED;
                    leftRotate(newNode->par->par);
                }
            }
        }
        root->color = BLACK;
    }

    node<T> * Minimum(node<T>* rt)
    {
        if (rt->left == NILL)
            return rt;
        else return Minimum(rt->left);
    }

    void Transplant(node<T> *u, node<T> *v)
    {
        if(u->par==NILL)
            root = v;
        else if(u==u->par->left)
            u->par->left = v;
        else
            u->par->right = v;
        v->par = u->par;
    }

    void DeleteFixUp(node<T>* x)
    {
        while(x!=root && x->color==BLACK)
        {
            if(x==x->par->left)
            {
                node<T>* sib = x->par->right;
                if(sib->color==RED)
                {
                    sib->color = BLACK;
                    x->par->color = RED;
                    leftRotate(x->par);
                    sib = x->par->right;
                }

                if(sib->left->color==BLACK && sib->right->color==BLACK)
                {
                    sib->color = RED;
                    x = x->par;
                }
                else
                {
                    if(sib->right->color==BLACK)
                    {
                        sib->left->color = BLACK;
                        sib->color = RED;
                        rightRotate(sib);
                        sib = x->par->right;
                    }
                    sib->color = x->par->color;
                    x->par->color = BLACK;
                    sib->right->color = BLACK;
                    leftRotate(x->par);
                    x = root;
                }
            }
            else
            {
                node<T>* sib = x->par->left;
                if(sib->color==RED)
                {
                    sib->color = BLACK;
                    x->par->color = RED;
                    rightRotate(x->par);
                    sib = x->par->left;
                }

                if(sib->left->color==BLACK && sib->right->color==BLACK)
                {
                    sib->color = RED;
                    x = x->par;
                }
                else
                {
                    if(sib->left->color==BLACK)
                    {
                        sib->right->color = BLACK;
                        sib->color = RED;
                        leftRotate(sib);
                        sib = x->par->left;
                    }
                    sib->color = x->par->color;
                    x->par->color = BLACK;
                    sib->left->color = BLACK;
                    rightRotate(x->par);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void DeleteNode(node<T>* x)
    {
        node<T>* y = x;
        COLOR c = x->color;
        node<T>* nn;
        if(x->left==NILL)
        {
            nn = x->right;
            Transplant(x,x->right);
        }
        else if(x->right==NILL)
        {
            nn = x->left;
            Transplant(x,x->left);
        }
        else
        {
            y = Minimum(x->right);
            c = y->color;
            nn = y->right;

            if(y->par==x)
                nn->par = y;
            else
            {
                Transplant(y,y->right);
                y->right = x->right;
                y->right->par = y;
            }
            Transplant(x,y);
            y->left = x->left;
            y->left->par = y;
            y->color = x->color;
        }
        if(c==BLACK)
        {
            DeleteFixUp(nn);
        }
    }
    void inorder(node<T>* root, int &c, int x)
    {
        if (root == NILL) return;
        inorder(root->left,c,x);
        if(root->val<x)
        {
            c++;
            inorder(root->right,c,x);
        }
    }
public:
    RBT()
    {
        NILL = new node<T>(NULL,NULL);
        NILL->color = BLACK;

        root = NILL;
    }
    void Insert(T v)
    {
        node<T> *newNode = new node<T>(v,NILL);
        if(root==NILL)
        {
            newNode->color = BLACK;
            root = newNode;
        }
        else
        {
            node<T> *temp = root;
            while(temp != NILL)
            {
                if(v < temp->val)
                {
                    if(temp->left == NILL)
                        break;
                    else
                        temp = temp->left;
                }
                else
                {
                    if(temp->right == NILL)
                        break;
                    else
                        temp = temp->right;
                }
            }
            newNode->par = temp;
            if(v < temp->val)
                temp->left = newNode;
            else
                temp->right = newNode;


        }
    }

    int Find(T v)
    {
        node<T> *temp = root;
        while(1)
        {
            if(temp==NILL)
                return 0;
            if(temp->val==v)
                return 1;
            if(v < temp->val)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
    }

    void Delete(T v)
    {
        node<T> *temp = root;
        while(1)
        {
            if(temp==NILL || temp->val==v)
                break;

            if(v < temp->val)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        if(temp!=NILL)
            DeleteNode(temp);
    }

    int LowerBound(int x)
    {
        int c = 0;
        inorder(root,c,x);
        return c;
    }
};

int main()
{
    freopen("inp.txt", "r", stdin);
    //freopen("out2.txt", "w", stdout);
    int n;
    cin>>n;
    cout<<n<<endl;
    RBT<int> rbt;
    while(n--)
    {
        int e,x,r;
        cin>>e>>x;
        cout<<e<<" "<<x<<" ";
        if(e==0)
        {
            cout<<rbt.Find(x)<<endl;
            rbt.Delete(x);
        }
        else if(e==1)
        {

            int f = rbt.Find(x);
            if(f==0)
            {
                rbt.Insert(x);
                cout<<1<<endl;
            }
            else
                cout<<0<<endl;
        }
        else if(e==2)
        {
            cout<<rbt.Find(x)<<endl;
            //cout<<-1<<endl;
        }
        else if(e==3)
        {
            cout<<rbt.LowerBound(x)<<endl;
            //cout<<-1<<endl;
        }
        else
        {
            cout<<"Wrong input given\n";
        }
    }
}
