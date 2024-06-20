#include<bits/stdc++.h>
using namespace std;
int bellman_ford(vector<vector<int>>arr,int num,int m,int source,int dest){
vector<int>dist(num+1,INT_MAX);
 dist[source]=0;
    for(int i=0;i<num-1;i++){
    for(int j=0;j<m;j++){
            if(dist[arr[j][1]]!=INT_MAX){
            if(dist[arr[j][2]]>arr[j][0]+dist[arr[j][1]]){
                dist[arr[j][2]]=arr[j][0]+dist[arr[j][1]];
            }
            }
            }
    }
    for(int j=0;j<m;j++){
          if(dist[arr[j][2]]>arr[j][0]+dist[arr[j][1]]){
               return INT_MAX;
            }

    }
  return dist[dest];
 }
int main(){
    int n,m;
cin>>n>>m;
vector<vector<int>>graph;
for(int i=0;i<m;i++){
    int x,y,z;
    cin>>x>>y>>z;
    graph.push_back({z,x,y});
}
int a,b,l,h,source,dest;
cin>>a>>b>>l>>h>>source>>dest;
int ans=INT_MAX;
int weight=0;
int weight1=bellman_ford(graph,n,m,source,dest);

for(int i=l;i<=h;i++){
    graph.push_back({i,a,b});
    int value=bellman_ford(graph,n,m+1,source,dest);
    if(value!=INT_MAX&&value<ans){
        ans=value;
        weight=i;
    }
    graph.pop_back();
}
if(ans!=INT_MAX&&ans!=weight1)cout<<weight<< " "<<ans<<endl;
else cout<<"impossible"<<endl;

}
