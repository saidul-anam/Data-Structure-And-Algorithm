#include<bits/stdc++.h>
using namespace std;
vector<int>val,weight,originalweight,originalval;
vector<vector<int>>usedweight;
vector<vector<vector<int>>>useditems;
int n,w,orw;
void knapsack(vector<vector<long>>&dp,int a){
 for(int i=1;i<=n;i++){
    for(int j=1;j<=n*a;j++){
        if(val[i]<=j){
            if(dp[i-1][j]< weight[i]+dp[i-1][j-val[i]]){
                dp[i][j]=dp[i-1][j];
                usedweight[i][j]=usedweight[i-1][j];
                useditems[i][j]=useditems[i-1][j];
            }
            else{
                dp[i][j]=weight[i]+dp[i-1][j-val[i]];
                usedweight[i][j]=usedweight[i-1][j-val[i]]+weight[i];
                useditems[i][j]=useditems[i-1][j-val[i]];
                useditems[i][j].push_back(i);
            }
        }
        else{
            dp[i][j]=dp[i-1][j];
            usedweight[i][j]=usedweight[i-1][j];
            useditems[i][j]=useditems[i-1][j];
        }
    }
 }
}

int roundedknapsack(double e,int v){
    vector<vector<long>> dp(n + 1, vector<long>(n *v+ 1, 1e9));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
double theta=(double)(e*v)/(double)(2*n);
 for(int i=1;i<=n;i++){
    double x=originalval[i]/theta;
    val[i]=ceil(x);
 }
 knapsack(dp,v);
 int resval=0,resweight=0;
 vector<int>resitem;
 for(int i=0;i<=v*n;i++){
    if(dp[n][i]<=w){
        resval=i;
        resweight=usedweight[n][i];
        resitem=useditems[n][i];
    }
 }
 cout << "Rounded with epsilon: " << e << endl;
    cout << "Theta: " << theta << endl;
    cout << "Answer of reduced instance: " << resval<< endl;
    cout << "Answer of reduced instance multiplied by theta: " << (double)resval * theta << endl;
    cout << "Indices: ";
     for(auto x:resitem){
        cout<<x<<" ";
     }
 cout<<endl;
 int orval=0;
  for(auto x:resitem){
    orval+=originalval[x];
  }
  cout << "Answer of original instance (rounded up): " <<orval << endl;
    cout << "Used weight: " << resweight << endl;
    cout << "Ratio: " << (double)(resval*theta)/(double)(orval) << endl;
}

int main(){
cin>>n>>w;
val.resize(n+1);
weight.resize(n+1);
originalval.resize(n+1);
originalweight.resize(n+1);
int vmax=0;
for(int i=1;i<=n;i++){
    cin>>originalval[i]>>originalweight[i];
    val[i]=originalval[i];
    weight[i]=originalweight[i];
    vmax=max(vmax,val[i]);
}
vector<vector<long>> dp(n + 1, vector<long>(n * vmax + 1, 1e9));
    usedweight.resize(n + 1, vector<int>(n * vmax + 1, 0));
    useditems.resize(n + 1, vector<vector<int>>(n * vmax + 1));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
knapsack(dp,vmax);
int resval=0,resweight=0;
vector<int>resitems;
for(int i=0;i<=n*vmax;i++){
    if (dp[n][i] <= w) {
            resval = i;
            resweight = usedweight[n][i];
            resitems = useditems[n][i];
        }
}
orw=resval;
 cout << "Original Instance:" << endl;
    cout << "Answer: " << resval << endl;
    cout << "Used weight: " << resweight << endl;
    cout << "Indices: ";
    for (int x : resitems) {
        cout << x << " ";
    }
    cout << endl;
 roundedknapsack(.5,vmax);
 cout<<endl;
 roundedknapsack(.2,vmax);
 cout<<endl;
 roundedknapsack(.1,vmax);
 cout<<endl;
 roundedknapsack(.05,vmax);
 cout<<endl;
}
