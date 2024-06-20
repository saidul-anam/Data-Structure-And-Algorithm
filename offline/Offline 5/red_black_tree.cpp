
//In this code, there are several bugs,I could not fix those while doing this offline.Sorry, lads.Problem is basically on deletion.
// For a better code, follow this gfg link:https://www.geeksforgeeks.org/deletion-in-red-black-tree/


#include<bits/stdc++.h>
using namespace std;
template<typename t>
class Node{
    public:
Node<t> *parent;
Node<t> *right;
Node<t> *left;
int key;
t value;
char colour;
Node(){
this->parent=NULL;
this->colour='B';
this->left=NULL;
this->right=NULL;

}
Node(int key,t value){
this->key=key;
this->value=value;
this->colour='R';
this->parent=NULL;
this->right=NULL;
this->left=NULL;
}
};
template<typename t>
class RedBlackTree{
private:
    Node<t> *root;
    Node<t> *tnull;
 void leftrotate(Node<t> *node){
        Node<t> *y=node->right;
        node->right=y->left;
        if(y->left != tnull){
            y->left->parent = node;}
        y->parent = node->parent;
        if(node->parent == NULL)
            root = y;
        else if(node == node->parent->left)
            node->parent->left = y;
        else
            node->parent->right = y;
        y->left = node;
        node->parent = y;
    }

    void rightrotate(Node<t> *node){
        Node<t> *y=node->left;
        node->left=y->right;
        if(y->right != tnull){
            y->right->parent = node;}
        y->parent = node->parent;
        if(node->parent == NULL)
            root = y;
        else if(node == node->parent->right)
            node->parent->right = y;
        else
            node->parent->left = y;
        y->right = node;
        node->parent = y;
    }

    void FindInsertHelp(Node<t> *node){
        Node<t> *ptr;
        while(node != root && node->parent->colour == 'R'){
            if(node->parent == node->parent->parent->right){
                ptr = node->parent->parent->left;
                if(ptr->colour == 'R'){
                    ptr->colour = 'B';
                    node->parent->colour = 'B';
                    node->parent->parent->colour = 'R';
                    node = node->parent->parent;
                }
                else{
                    if(node == node->parent->left){
                        node = node->parent;
                        rightrotate(node);
                    }
                    node->parent->colour = 'B';
                    node->parent->parent->colour = 'R';
                    leftrotate(node->parent->parent);
                }
            }
            else{
                ptr = node->parent->parent->right;
                if(ptr->colour == 'R'){
                    ptr->colour = 'B';
                    node->parent->colour = 'B';
                    node->parent->parent->colour = 'R';
                    node = node->parent->parent;
                }
                else{
                    if(node == node->parent->right){
                        node = node->parent;
                        leftrotate(node);
                    }
                    node->parent->colour = 'B';
                    node->parent->parent->colour = 'R';
                    rightrotate(node->parent->parent);
                }
            }
        }
        root->colour = 'B';
    }
    Node<t>*successor(Node<t> *node){
        Node<t>*temp=node;
    while(temp->left!=tnull){
        temp=temp->left;
    }
    return temp;
    }
    Node<t>*replace(Node<t> *node){
    if(node->left!=NULL&&node->right!=NULL){
        return successor(node->right);
    }
    else if(node->left==NULL&&node->right==NULL){
        return NULL;
    }
    else if(node->left!=NULL&&node->right==NULL){
        return node->left;
    }
    else {
        return node->right;
    }
    }
    bool hasredchild(Node<t>*node){
    if((node->left!=NULL &&node->left->colour=='R')||(node->right!=NULL&&node->right->colour=='R')){
        return true;
    }
    return false;
    }
    bool isleft(Node<t>*node){
    if(node->parent->left==node){ return true;}
    return false;
    }
    Node<t>*siblings(Node<t>*node){
    if(node==root) return NULL;
    if(node->parent->right==node)return node->parent->left;
    else return node->parent->right;
    }


    void fixdoubleblack(Node<t>*node){
    if(node==root){
        return;
    }
    Node<t>*parent=node->parent;
    Node<t>*sibling=siblings(node);
    if(sibling==NULL){
        fixdoubleblack(parent);
    }
    else if(sibling->colour=='R'){
        parent->colour='R';
        sibling->colour='B';
        if(sibling->parent->left==sibling){
            rightrotate(parent);
        }
        else{
            leftrotate(parent);
        }
        fixdoubleblack(node);
    }
    else{
            if(hasredchild(sibling)){
            if(sibling->left!=NULL&&sibling->left->colour=='R'){
                if(isleft(sibling)){
                    sibling->left->colour=sibling->colour;
                    sibling->colour=parent->colour;
                    rightrotate(parent);
                }
                else{
                     sibling->left->colour=parent->colour;
                    rightrotate(sibling);
                    leftrotate(parent);
                }
            }
               else{
                if(isleft(sibling)){
                    sibling->right->colour=parent->colour;
                    leftrotate(sibling);
                    rightrotate(parent);}
                else{
                    sibling->right->colour=sibling->colour;
                    sibling->colour=parent->colour;
                    leftrotate(parent);
                }
            }
            parent->colour='B';
            }
            else{
    sibling->colour='R';
    if(parent->colour=='B'){
        fixdoubleblack(parent);
    }
    else{
        parent->colour='B';
    }
   }
    }
    }

    void deletehelp(Node<t>*node){
     Node<t> *replacenode=replace(node);
     bool bothblack=false;
     if((replacenode==NULL||replacenode->colour=='B')&&node->colour=='B'){
        bothblack=true;
     }
     if(replacenode==NULL){
        //it means node is a leaf
        if(node==root){
            root=NULL;
        }
        else if(bothblack==true){
            fixdoubleblack(node);
        }
        else{
            if(node->parent!=NULL){
                if(node->parent->left==node){
                    if(node->parent->right!=NULL){
                        node->parent->right->colour='R';
                    }
                }
                else{
                    if(node->parent->left!=NULL){
                        node->parent->left->colour='R';
                    }
                }
            }
        if(node->parent->left==node){
            node->parent->left=NULL;
        }else{
        node->parent->right=NULL;
        }
     }
     delete node;
     return;
     }
   if(node->left==NULL||node->right==NULL){
    if(node==root){
        node->key=replacenode->key;
        node->value=replacenode->value;
        node->left=node->right=NULL;
        delete replacenode;
    }
    else{
     if(node->parent->left==node){
        node->parent->left=replacenode;
     }
     else{
        node->parent->right=replacenode;
     }
     replacenode->parent=node->parent;
     delete node;
     if(bothblack==true){
        fixdoubleblack(replacenode);
     }
        else{
            replacenode->colour='B';
        }
    }
    return;
   }
    int keys=replacenode->key;
    t values=replacenode->value;
    replacenode->key=node->key;
    replacenode->value=node->value;
    node->key=keys;
    node->value=values;

     deletehelp(replacenode);
    }


public:
    RedBlackTree(){
    tnull=new Node<t>();
    tnull->colour='B';
    root=tnull;
    }
   void insert(int key,t value){
        Node<t>*node = new Node<t>(key,value);
        node->parent = NULL;
        node->left = tnull;
        node->right = tnull;
        node->colour = 'R';

        Node<t> *y = NULL;
        Node<t> *x = this->root;

        while(x != tnull){
            y = x;
            if(node->key < x->key){
                x = x->left;}
            else{
                x = x->right;}
        }
        node->parent = y;
        if(y == NULL){
            root = node;
        }
        else if(node->key < y->key){
            y->left = node;
        }
        else{
            y->right = node;}
        if(node->parent == NULL){
            node->colour = 'B';
            return;
        }
        if(node->parent->parent == NULL){
            return;
        }
        FindInsertHelp(node);
    }

    Node<t> *findhelp(Node<t> *node,int n){
        if(node==NULL){
            return NULL;
        }
    if(node->key>n){
        return findhelp(node->left,n);
    }
    else if(node->key==n){
        return node;
    }
    else if(node->key<n){
        return findhelp(node->right,n);
    }
    }



  Node<t> *find(int n){
 return findhelp(root,n);
  }

   void Delete(int n){
  Node<t>*u=find(n);
  if(u==NULL){
    return ;
  }
  else{
    deletehelp(u);
  }

   }

    void inorder(Node<t> *x) {
    if (x == NULL)
      return;
    inorder(x->left);
    cout << x->key << "->"<<x->value<<endl;
    inorder(x->right);
  }
   void printInOrder() {
      inorder(root);
  }

};

template<typename t>
class Map{
    RedBlackTree<t> a;
    int Count;
    priority_queue<int> del;
    public:
        Map(){
        a=new RedBlackTree<t>();
        Count=0;}
        void Insert(int ar,t b){
        a.insert(ar,b);
        del.push(ar);
        }
        void Erase(int ar){
        a.Delete(ar);
        }
        void Clear(){
        if(Count==0){
            cout<<"unsucessful"<<endl;
        }
        else{
            while(!del.empty()){
                int ar=del.top();
                del.pop();
                a.Delete(ar);
            }
            cout<<"successful"<<endl;
        }
        }
        bool Find(int ar){
        Node<t>*u=a.find(ar);
        if(u->key!=a){
            return false;
        }
         return true;
        }
        bool Empty(){
        if(Count==0) return true;
        else return false;
        }
        int Size(){
        return Count;
        }
   void Iteration(){
   a.printInOrder();
   }

};


int main() {
Map<string>hello;
while(true){
    string s;
    cin>>s;
    if(s=="I"){
        int a;
        string si;
        cin>>a>>si;
        hello.Insert(a,si);
    }
    if(s=="Clr"){
        hello.Clear();
    }
    if(s=="E"){
        int a;
        cin>>a;
        hello.Erase(a);
    }
    if(s=="F"){
            int a;
    cin>>a;
        if(hello.Find(a)){
            cout<<a<<" found"<<endl;
        }
        else {
            cout<<a<<" not found"<<endl;
        }
    }
    if(s=="Em"){
        if(hello.Empty()){
            cout<<"yes"<<endl;
        }
        else{
            cout<<"no"<<endl;
        }
    }
    if(s=="S"){
        cout<<hello.Size()<<endl;
    }
    if(s=="Itr"){
        hello.Iteration();
    }
}


}
