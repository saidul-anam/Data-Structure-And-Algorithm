#include<bits/stdc++.h>
using namespace std;
int main(){
int city,road,source,dest,capacity;
cin>>city>>road>>capacity;
vector<int>gasprice(city+1);
for(int i=1;i<=city;i++){
    cin>>gasprice[i];
}
vector<vector<int>>graph;
for(int i=0;i<road;i++){
    int u,v,w;
    cin>>u>>v>>w;
    if(w<capacity)graph.push_back({w,u,v});
}
cin>>source>>dest;
vector<pair<int,pair<int,int>>>newgraph[city+1][capacity+1];
for(int i=1;i<=city;i++){
    for(int j=0;j<capacity;j++){
        newgraph[i][j].push_back({gasprice[i],{i,j+1}});
    }
}
for(int i=0;i<graph.size();i++){
    int dist=graph[i][0];
    int from=graph[i][1];
    int to=graph[i][2];
    for(int k=0;k<=capacity;k++){
            if(dist-k>=capacity){
        int cost1=gasprice[from]*(dist-k);
       int cost2=gasprice[to]*(dist-k);
        newgraph[from][k].push_back({cost1,{to,dist-k}});
        newgraph[to][k].push_back({cost2,{from,dist-k}});
    }
    }
    for(int j=capacity;j>=0;j--){
        if(j-dist>=0){
            newgraph[from][j].push_back({0,{to,j-dist}});
            newgraph[to][j].push_back({0,{from,j-dist}});
        }
        else{break;}
    }
}
int num=city;
vector<int>visited[num+1];
for(int i=1;i<=num;i++){
    for(int j=0;j<=capacity;j++){ visited[i].push_back(0);}
}
priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>>Q;
vector<int>dist[num+1];
for(int i=1;i<=num;i++){
    for(int j=0;j<=capacity;j++){ dist[i].push_back(INT_MAX);}
}
 Q.push({0,{source,0}});
 dist[source][0]=0;
 while(!Q.empty()){
pair<int,int> u=Q.top().second;
Q.pop();
if(visited[u.first][u.second]==0){
    visited[u.first][u.second]=1;
    for(auto a:newgraph[u.first][u.second]){
        if(visited[a.second.first][a.second.second]==0){
            if(dist[a.second.first][a.second.second]>a.first+dist[u.first][u.second]){
                dist[a.second.first][a.second.second]=a.first+dist[u.first][u.second];
                Q.push({dist[a.second.first][a.second.second],a.second});
            }
        }
    }
}
 }
int ans=INT_MAX;
 for(int i=0;i<=capacity;i++){
    if(dist[dest][i]!=INT_MAX){
        ans=min(ans,dist[dest][i]);
    }
 }
 if(ans!=INT_MAX) cout<<ans<<endl;
   else cout<<"impossible"<<endl;
   }
