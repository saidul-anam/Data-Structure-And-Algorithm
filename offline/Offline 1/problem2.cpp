#include<bits/stdc++.h>
using namespace std;
vector<int>critical;
vector<int>pseudocritical;
class unionfined{
int *parent;
int *Rank;
public:
unionfined(int i){
    parent=new int[i+1];
    Rank=new int[i+1];
    for(int j=1;j<i+1;j++){
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
int getmst(vector<vector<int>>arr,int del,int take){
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
for(int i=1;i<=k;i++){
    if(x.Findparent(i)!=x.Findparent(1)){
        return INT_MAX;
    }
}
return minweight;
}
};
void check(int n,int m){

    vector<vector<int>>arr;
for(int i=0;i<m;i++){
    int x,y,z;
    cin>>x>>y>>z;
    arr.push_back({z,x,y,i});
}
sort(arr.begin(),arr.end());

    mst a(n);
int weight=a.getmst(arr,-1,-1);
for(int i=0;i<m;i++){
    if(a.getmst(arr,i,-1)>weight){
        critical.push_back(arr[i][3]);
    }
    else if(a.getmst(arr,-1,i)==weight){
            pseudocritical.push_back(arr[i][3]);
    }
}
}
int main(){
 int n,m;
 cin>>n>>m;
 check(n,m);
 vector<string>print(m,"none");
 for(int i=0;i<critical.size();i++){
    print[critical[i]]="any";
 }
 for(int i=0;i<pseudocritical.size();i++){
    print[pseudocritical[i]]="at least one";
 }
 for(int i=0;i<m;i++){
        cout<<print[i]<<endl;
 }
}
