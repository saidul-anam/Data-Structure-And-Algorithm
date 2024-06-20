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
    for(int i=0;i<=n;i++){
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
int ford_fulkerson(int n){
int s=0,t=n;
int parent[n];
for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
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
return flow;
}

int main(){
int n,m;
cin>>n>>m;
for(int i=0;i<=n+m;i++){
    for(int j=0;j<=n+m;j++){
        graph[i][j]=0;
    }
}
vector<int>arr[n+m+1];
for(int i=1;i<n+m+1;i++){
    int x,y,z;
    cin>>x>>y>>z;
    arr[i].push_back(x);
    arr[i].push_back(y);
      arr[i].push_back(z);
      }
for(int i=1;i<=n;i++){
    graph[0][i]=1;
}
for(int i=n+1;i<n+m+1;i++){
    graph[i][n+m+1]=1;
}
for(int i=1;i<=n;i++){
    for(int j=n+1;j<n+m+1;j++){
        if(((abs(arr[i][0]-arr[j][0])<=10)&&(abs(arr[i][1]-arr[j][1])<=5))&&arr[i][2]==arr[j][2]){
            graph[i][j]=1;
        }
    }
}
cout<<ford_fulkerson(n+1+m);
}
