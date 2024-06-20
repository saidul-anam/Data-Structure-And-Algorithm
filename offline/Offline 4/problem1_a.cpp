#include<bits/stdc++.h>
using namespace std;
#define N 10000
int resgraph[N][N];
int graph[N][N];
bool bfs(int s,int t,int n,int parent[N]){
bool vis[n];
memset(vis,0,sizeof(vis));
queue<int>q;
q.push(s);
vis[s]=true;
parent[s]=-1;
while(!q.empty()){
    int u=q.front();
    q.pop();
    for(int i=0;i<n;i++){
        if(vis[i]==0&&resgraph[u][i]>0){
                if(i==t){
                    parent[i]=u;
                    return true;
                }
        q.push(i);
        vis[i]=1;
        parent[i]=u;
        }
    }
}
return false;
}
void ford_fulkerson(int n){
int s,t;
cin>>s>>t;
int parent[n];
for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
    resgraph[i][j]=graph[i][j];
}
}
int flow=0;
while(bfs(s,t,n,parent)){
    int low=INT_MAX;
    for(int i=t;i!=s;i=parent[i]){
        int u=parent[i];
        low=min(low,resgraph[u][i]);
    }
     for(int i=t;i!=s;i=parent[i]){
        int u=parent[i];
        resgraph[u][i]-=low;
        resgraph[i][u]+=low;
    }
    flow+=low;
}
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        if(graph[i][j]>0){
            graph[i][j]=graph[i][j]-resgraph[i][j];
        }
    }
}
int m=0,l=0;
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        if(graph[i][j]>m){
            m=graph[i][j];
            l=i;
        }
    }
}
cout<<l<<" "<<m;
}

int main(){
int n,m;
cin>>n>>m;
for(int i=0;i<=n;i++){
    for(int j=0;j<=n;j++){
        graph[i][j]=0;
    }
}
for(int i=0;i<m;i++){
    int x,y,z;
    cin>>x>>y>>z;
    graph[x][y]=z;
}
ford_fulkerson(n+1);
}
