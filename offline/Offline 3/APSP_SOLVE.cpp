#include<bits/stdc++.h>
using namespace std;
int graph[101][101];
void floyd_warshall(int n,int m){
for(int k=1;k<=n;k++){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(graph[i][j]>graph[i][k]+graph[k][j]&&graph[i][k]!=INT_MAX&&graph[k][j]!=INT_MAX){
                graph[i][j]=graph[i][k]+graph[k][j];
            }
        }
    }
    }
    int minvalue;
    cin>>minvalue;
vector<int>arr;
int ans=INT_MAX;
for(int i=1;i<=n;i++){
        int attackontitan=0;
    for(int j=1;j<=n;j++){
        if(graph[i][j]<=minvalue){
            attackontitan++;
        }
    }
    if(attackontitan<ans){
        ans=attackontitan;
        arr.clear();
        arr.push_back(i);
    }
    else if(attackontitan==ans) arr.push_back(i);
}
for(int i=0;i<arr.size();i++){
    cout<<arr[i]<<" ";
}
cout<<endl;
}
int main(){
int n,m;
cin>>n>>m;
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        if(i==j) graph[i][j]=0;
        else graph[i][j]=INT_MAX;
    }
}
for(int i=0;i<m;i++){
    int x,y,z;
    cin>>x>>y>>z;
    graph[x][y]=z;
    graph[y][x]=z;
}
floyd_warshall(n,m);
}
