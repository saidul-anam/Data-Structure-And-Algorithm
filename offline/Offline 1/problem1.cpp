#include<bits/stdc++.h>
using namespace std;
vector<int>critical;
vector<int>pseudocritical;
vector<vector<int>>totalmst;
int lowweight=0;
class unionfined{
int *parent;
int *Rank;
public:
unionfined(int i){
    parent=new int[i];
    Rank=new int[i];
    for(int j=0;j<i;j++){
        parent[j]=j;
        Rank[j]=0;
    }
    }
    int Findparent(int i){
if(parent[i]==i){
    return i;
}
else return parent[i]=Findparent(parent[i]);
}
void unionset(int u,int v){
u=Findparent(u);
v=Findparent(v);
if(Rank[u]<Rank[v]){
    parent[u]=v;
}
else if(Rank[v]<Rank[u]) {
    parent[v]=u;
}
else{
    parent[v]=u;
    Rank[u]++;
}
}
};
class mst{
int minweight;
int k;
public:
    mst(int i){
        k=i;
            }
int getmst(vector<vector<int>>arr1,int del,int take){
    vector<vector<int>>arr=arr1;
    sort(arr.begin(),arr.end());
    minweight=0;
    unionfined x(k);
    if(take!=-1){
        x.unionset(arr[take][1],arr[take][2]);
        minweight+=arr[take][0];
    }
for(int i=0;i<arr.size();i++){
        if(i!=del){
        int start=x.Findparent(arr[i][1]);
        int finish=x.Findparent(arr[i][2]);
     if(start!=finish){
            minweight+=arr[i][0];
        x.unionset(start,finish);
     }
}
}
for(int i=0;i<k;i++){
    if(x.Findparent(i)!=x.Findparent(1)){
        return INT_MAX;
    }
}
return minweight;
}
};
void allcombination(int var,int total,int vertex,int edge,vector<vector<int>>graph,vector<int>comb,int weight){
if(total==vertex-1){
  int counterweight=0;
    unionfined x(vertex);
    vector<vector<int>>res;
for(auto a:comb){
        int start=x.Findparent(graph[a][1]);
        int finish=x.Findparent(graph[a][2]);
     if(start!=finish){
            counterweight+=graph[a][0];
        x.unionset(start,finish);
     }
}
for(int i=0;i<vertex;i++){
    if(x.Findparent(i)!=x.Findparent(0)){
        return;
    }
    }
    if(counterweight==weight){
            ///cout<<counterweight<<" "<<weight<<endl;
    totalmst.push_back(comb);}
return;
}
if(var==edge){
    return;
}
comb.push_back(var);
allcombination(var+1,total+1,vertex,edge,graph,comb,weight);
comb.pop_back();
allcombination(var+1,total,vertex,edge,graph,comb,weight);
}


void allmst(vector<vector<int>>graph,int vertex,int edge,int weight){

vector<int>comb;
allcombination(0,0,vertex,edge,graph,comb,weight);
}



void check(int n,int m){
    vector<vector<int>>arr;
for(int i=0;i<m;i++){
    int x,y,z;
    cin>>x>>y>>z;
    arr.push_back({z,x,y,i});
}
   mst a(n);
int weight=a.getmst(arr,-1,-1);
allmst(arr,n,m,weight);
cout<<"MSTs:"<<endl;
for(int i=0;i<totalmst.size();i++){
        cout<<i+1<<" : [";
    for(int j=0;j<n-2;j++){
        cout<<"["<<arr[totalmst[i][j]][1]<<", "<<arr[totalmst[i][j]][2]<<", "<<arr[totalmst[i][j]][0]<<"], ";
    }
            cout<<"["<<arr[totalmst[i][n-2]][1]<<", "<<arr[totalmst[i][n-2]][2]<<", "<<arr[totalmst[i][n-2]][0]<<"]]"<<endl;
}
}
int main(){
 int n,m;
 cin>>n>>m;
 check(n,m);
}
