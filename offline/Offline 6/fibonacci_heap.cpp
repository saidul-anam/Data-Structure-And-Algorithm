#include<bits/stdc++.h>
using namespace std;

class node
{
public:
    node *parent;
    node *left;
    node *right;
    node *child;
    int key;
    int value;
    int degree;
    int mark;
    node(int key,int value)
    {
        this->parent=NULL;
        this->left=NULL;
        this->right=NULL;
        this->child=NULL;
        this->key=key;
        this->value=value;
        this->degree=0;
        this->mark=0;
    }
};
class fib_heap
{
    int total_node;
    node *maximum;
    node *findarr[10000];
public:
    fib_heap()
    {
        for(int i=0; i<=10000; i++)
        {
            findarr[i]=NULL;
        }
        total_node=0;
    }
    void make_heap()
    {
        maximum=NULL;
    }
    bool isempty()
    {
        if(total_node==0) return true;
        return false;
    }
    void insertion(int key,int value)
    {
        node *bot=new node(key,value);
        bot->left=bot;
        bot->right=bot;
        if(maximum==NULL)
        {
            maximum=bot;
        }
        else
        {
            (maximum->left)->right=bot;
            bot->right=maximum;
            bot->left=maximum->left;
            maximum->left=bot;
            if(maximum->value<bot->value)
            {
                maximum=bot;
            }
        }
        findarr[value]=bot;
        total_node++;
    }
    void docut(node *found,node *parentnode)
    {
        if(found==found->right)
        {
            parentnode->child=NULL;
            parentnode->degree-=1;
        }
        else
        {
            (found->left)->right=found->right;
            (found->right)->left=found->left;
            parentnode->child=found->right;
            parentnode->degree-=1;
        }
        (maximum->left)->right=found;
        found->right=maximum;
        found->left=maximum->left;
        maximum->left=found;
        found->parent=NULL;
        found->mark=0;
    }
    void recurcut(node *parentnode)
    {
        if(parentnode->parent!=NULL)
        {
            if(parentnode->mark==0)
            {
                parentnode->mark=1;
            }
            else
            {
                docut(parentnode,parentnode->parent);
                recurcut(parentnode->parent);
            }
        }
    }
    void increasekey(int keys,int val)
    {
        node *found=findarr[keys];
        if(maximum==NULL||findarr[keys]==NULL)
        {
            return;
        }
        if(found->key!=keys) return;
        if(found->value>val)return ;
        found->value=val;
        if(found->parent!=NULL)
        {
            if(found->value>found->parent->value)
            {
                docut(found,found->parent);
                recurcut(found->parent);
            }
        }
        if(found->value>maximum->value)
        {
            maximum=found;
        }
    }

    pair<int,int> extractmax()
    {
        if(maximum==NULL) return {-1,-1};
        int maximus=maximum->value;
        int val=maximum->key;
        node *z=maximum;
        if(maximum->child!=NULL)
        {
            node *x=maximum->child;
            do
            {
                node *temp=x->right;
                (maximum->left)->right=x;
                x->right=maximum;
                x->left=maximum->left;
                maximum->left=x;
                x->parent=NULL;
                x=temp;
            }
            while(x!=z->child);
        }
        (z->left)->right=z->right;
        (z->right)->left=z->left;
        if(z==z->right&&z->child==NULL)
        {
            maximum=NULL;
        }
        else
        {
            maximum=z->left;
            merging();
        }
        findarr[z->value]=NULL;
        total_node--;
        delete z;
        return {val,maximus};
    }
    void merging()
    {
        float m=log(total_node)/log(2);
        int x=m;
        node *arr[x+1];
        for(int i=0; i<=x; i++)
        {
            arr[i]=NULL;
        }
        node *temp=maximum;
        do
        {
            int z=temp->degree;
            while(arr[z]!=NULL)
            {
                node *temp1=arr[z];
                if(temp->value<temp1->value)
                {
                    node *temp2=temp;
                    temp=temp1;
                    temp1=temp2;
                }
                if(temp1==maximum)
                {
                    maximum=temp;
                }
                meld(temp1,temp);
                if(temp->right==temp)
                {
                    maximum=temp;
                }
                arr[z]=NULL;
                z++;
            }
            arr[z]=temp;
            temp=temp->right;
        }
        while(temp!=maximum);
        maximum=NULL;
        for(int i=0; i<=x; i++)
        {
            if(arr[i]!=NULL)
            {
                arr[i]->left=arr[i];
                arr[i]->right=arr[i];
                if(maximum!=NULL)
                {
                    maximum->left->right=arr[i];
                    arr[i]->right=maximum;
                    arr[i]->left=maximum->left;
                    maximum->left=arr[i];
                    if(arr[i]->value>maximum->value)
                    {
                        maximum=arr[i];
                    }
                }
                else
                {
                    maximum=arr[i];
                }
            }
        }
    }
    int findmax()
    {
        return maximum->value;
    }

    void Delete(int x)
    {
        if(findarr[x]==NULL)
        {
            cout<<"NOT FOUND"<<endl;
            return;
        }
        increasekey(findarr[x]->value,INT_MAX);
        pair<int,int> hell=extractmax();
    }
    void meld(node *temp,node *temp1)
    {
        (temp->left)->right=temp->right;
        (temp->right)->left=temp->left;
        if(temp1->right==temp1)
        {
            maximum=temp1;
        }
        temp->left=temp;
        temp->right=temp;
        temp->parent=temp1;
        if(temp1->child==NULL)
        {
            temp1->child=temp;
        }
        temp->right=temp1->child;
        temp->left=(temp1->child)->left;
        ((temp1->child)->left)->right=temp;
        (temp1->child)->left=temp;
        if(temp->value>temp1->child->value)
        {
            temp1->child=temp;
        }
        temp1->degree++;

    }

    void printHeap()
    {
        node *temp=maximum;
        int i=1;
        do
        {
            cout<<endl;
            cout<<"Tree "<<i<<": "<<endl;
            print_tree(temp);
            temp=temp->right;
            i++;
        }
        while(temp!=maximum);
    }
    void print_tree(node *temp)
    {
        queue<node*>q;
        q.push(temp);
        while(!q.empty())
        {
            node *temp1=q.front();
            q.pop();
            node *temp2=temp1->child;
            cout<<"("<<temp1->key<<","<<temp1->value<<")";
            if(temp1->child!=NULL) cout<<"->";
            if(temp2==NULL)
            {
                break;
            }
            while(true)
            {
                if(temp2->right==temp1->child)
                {
                    cout<<"("<<temp2->key<<","<<temp2->value<<")"<<endl;
                    q.push(temp2);
                    break;
                }
                cout<<"("<<temp2->key<<","<<temp2->value<<"),";
                q.push(temp2);
                temp2=temp2->right;
            }
        }
    }

    void test()
    {
        if(isempty())cout<<"Yes,Empty"<<endl;
        else cout<<"Not Empty"<<endl;
        insertion(0,12);
        insertion(1,13);
        insertion(2,14);
        insertion(3,15);
        if(isempty())cout<<"Yes,Empty"<<endl;
        else cout<<"Not Empty"<<endl;
        insertion(4,16);
        insertion(5,17);
        insertion(6,18);
        increasekey(12,25);
        insertion(7,19);
        printHeap();
        cout<<"first extract max"<<endl;
        extractmax();
        printHeap();
        cout<<"second extract max"<<endl;
        extractmax();
        printHeap();
        insertion(8,20);
        insertion(9,21);
          printHeap();
           cout<<"doing double delete now"<<endl;
        Delete(16);
          printHeap();
        Delete(20);
         cout<<" double delete completed"<<endl;
        insertion(10,22);
        printHeap();
        extractmax();
        printHeap();
        cout<<endl;
        if(isempty())cout<<"Yes,Empty"<<endl;
        else cout<<"Not Empty"<<endl;
        cout<<"Passed"<<endl;
    }
};
int main()
{

    fib_heap arr;
    arr.test();

}
