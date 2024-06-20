#include<bits/stdc++.h>
using namespace std;
vector<int>critical;
vector<int>pseudocritical;
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
for(int i=0;i<k;i++){
    if(x.Findparent(i)!=x.Findparent(0)){
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
 sort(critical.begin(),critical.end());
 sort(pseudocritical.begin(),pseudocritical.end());
 cout<<"Critical edges:[";
 for(int i=0;i<critical.size()-1;i++){
    cout<<critical[i]<<",";
 }
 cout<<critical[critical.size()-1]<<"]"<<endl;
 cout<<"Pseudo critical edges:[";
 for(int i=0;i<pseudocritical.size()-1;i++){
    cout<<pseudocritical[i]<<",";
 }
 cout<<pseudocritical[pseudocritical.size()-1]<<"]"<<endl;
}
