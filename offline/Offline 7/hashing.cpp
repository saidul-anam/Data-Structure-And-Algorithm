#include<bits/stdc++.h>
using namespace std;
///this part is for generating distinct string
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int random(int start, int end){
    return uniform_int_distribution<int>(start, end)(rng);
}
vector<string>generator(int n){
map<string ,int>check;
vector<string>allstr;
for(int i=0;i<n;i++){
        int z=5+random(0,5);
    string s(z,'*');
    for(int j=0;j<z;j++){
        int r=random(0,25);
        s[j]='a'+r;
    }
    if(!check[s]){
        check[s]=1;
        allstr.push_back(s);
    }
    else{
        n++;
    }
}
return allstr;
}
///this part ends here

///now the main part start(hashing)

class HashTable{
int n;
int old_n;
int method;
int func;
int list_size;
int tot_deleted;
vector<vector<int>>separate_chaining;
vector<int>probing;
vector<pair<string,int>>rehashing_need;
int collision_count;
bool isprime(int n){
if(n<=1) return false;
if(n<=3) return true;
if(n%2==0||n%3==0) return false;
for(int i=5;i*i<=n;i=i+6){
    if (n%i == 0 || n%(i+2) == 0){
        return false;
    }
}
return true;
 }
int nextprime(int a){
if(a<=1) return 2;
int x=a;
while(true){
        x++;
    if(isprime(x)){
        break;
    }
}
return x;
}
 ///source:https://cp-algorithms.com/string/string-hashing.html
    int hash1(string s){
    int p= 31;
    int m=1e9+9;
    long long hash_value=0;
    long long p_pow = 1;
    for (char c:s){
        hash_value=(hash_value+(c-'a'+1)*p_pow)%m;
        p_pow=(p_pow*p)%m;
    }
    return hash_value%this->n;
    }
    ///source:http://www.cse.yorku.ca/~oz/hash.html
    ///sbdm
    int hash2(string s){
        long long hashValue = 0;
    const int m = 1e9 + 9;
    for(int i = 0 ; i<11; i++){
        hashValue = ((long long)s[i] + (hashValue << 6) + (hashValue<<16) - hashValue)%m;
    }
    return hashValue%this->n;
}
int hash(string s){
if(this->func==1) return hash1(s);
else return hash2(s);
}
///source:http://www.cse.yorku.ca/~oz/hash.html
int auxhash(string s){
     long long hash = 5381;
    int c;
    for(char c:s){
        hash=(((hash<<5)+hash)+c)%(long long)(1e9+7); /* hash * 33 + c */
    }
    return hash%n;
}
int double_hash(string s,int i){
return (hash(s)+i*auxhash(s))%this->n;
}

int customhash(string s,int i){
return (hash(s) + 59*i*auxhash(s) + 61*i*i)%this->n;///c1=59,c2=61
}
int methodhash(string s, int i){
    if(method ==2)
        return double_hash(s, i);
    else if(method == 3)
        return customhash(s, i);
    return hash(s);
}
void insert_separate_chaining(string s ,int i){
int x=hash(s);
if(separate_chaining[x].size()>0){
    collision_count++;
}
separate_chaining[x].push_back(i);
rehashing_need.push_back({s,i});
if(separate_chaining[x].size()>=list_size){
    rehash(1);
}
}
void insert_proving(string s,int i){
      int x=0;
    while(x<this->n){
        int index = methodhash(s, x);
        if(i>0){
        collision_count++;
        }
        if(probing[index] == -1){
         probing[index] = i;
            return;
        }else{
            x++;
        }
    }
}
void delete_separate_chaining(string s,int i){
 int x=hash(s);
 separate_chaining[x].erase(remove(separate_chaining[x].begin(), separate_chaining[x].end(),i),separate_chaining[x].end());
 tot_deleted++;
 if(tot_deleted==100){
    tot_deleted=0;
    int x=0;
    for(int i=0;i<this->n;i++){
            int y=separate_chaining[i].size();
        x=max(x,y);
    }
    if(0.8*list_size>x){
        rehash(0);
    }
 }
 for(int i=0;i<rehashing_need.size();i++){
    if(rehashing_need[i].first==s&&rehashing_need[i].second==i){
        rehashing_need[i].second=-2;
        break;
    }
 }
}
void delete_proving(string s,int i){
pair<int,int>found=find_proving(s,i);
if(found.first==-1){
    return;
}
else{
    probing[found.first]=-2;
}
}
int findIndex( int key,int value) {
    int index = 0;
    for (auto it = separate_chaining[key].begin(); it !=separate_chaining[key].end(); ++it) {
        if (*it == value) {
            return index;
        }
        index++;
    }
    return -1;
    }
pair<int,int>find_separate_chaining(string s,int i){
 int x=hash(s);
 int y=findIndex(x,i);
 if(y==-1){
    return {-1, 0};}
 else{
    return {x,y+1};
 }
}
pair<int,int>find_proving(string s,int i){
    int x=0;
    while(x<this->n){
        int y=methodhash(s,x);
        if(probing[y]==-1){
            return {-1,0};
        }
        if(probing[y]==i){
            return {y,x+1};
        }
        x++;
    }
}
void rehash(int x){
    if(x!=0){
    this->n=nextprime(this->n*2);}
    else{
        this->n=nextprime(0.5*this->n);
    }
separate_chaining.resize(this->n);
collision_count=0;
this->list_size=this->list_size*2;
for(int i=0;i<rehashing_need.size();i++){
    string a=rehashing_need[i].first;
    int b=rehashing_need[i].second;
    if(b!=-2){
    insert(a,b);
}
}
}
public:

    HashTable(int a,int func,int method){
    this->func=func;
    this->method=method;
    this->n=nextprime(a);
    this->old_n=this->n;
    this->tot_deleted=0;
    separate_chaining.resize(this->n);
    probing.assign(this->n,-1);
    collision_count=0;
    }

   void listsize(int x){
   this->list_size=x;
   }
void insert(string s,int i){
if(method==1){
    insert_separate_chaining(s,i);
}
else{
    insert_proving(s,i);
}
}
void Delete(string s,int i){
if(method==1){
    delete_separate_chaining(s,i);
}
else{
    delete_proving(s,i);
  }
 }
pair<int,int>find(string s,int i){
if(method==1){
    return find_separate_chaining(s,i);
}
else{
    return find_proving(s,i);
}
}
int col(){
return collision_count;}
int get(){
return this->n;}
};
void printResult(const string& name, HashTable& h, vector<pair<string, int>>& vv){
    cout<<name<<endl;
    cout<<"Collisions: "<<h.col()<<endl;
    int probe = 0;
    for(int i = 0; i<1000; i++){
        int r = random(0, vv.size()-1);
        probe += h.find(vv[r].first, vv[r].second) .second;
    }
    cout<<"Avg Probes: "<<probe/1000.0<<endl<<endl;
}
 int main(){
   int n,m;
   cin>>n>>m;
   vector<string>str=generator(n);
     vector<pair<string, int>>checking;
    HashTable h1(n,1,1);
    h1.listsize(m);
    HashTable h2(n,2,1);
    h2.listsize(m);
    HashTable h3(n,1,2);
    HashTable h4(n,2,2);
    HashTable h5(n,1,3);
    HashTable h6(n,2,3);

    int i = 1;
    for(string s: str){
        h1.insert(s, i);
        h2.insert(s, i);
        h3.insert(s, i);
        h4.insert(s, i);
        h5.insert(s, i);
        h6.insert(s, i);
        checking.push_back({s, i++});
        if(i==n-2000){
            break;
        }
    }
   printResult("Chaining method(hash1)", h1,checking);
    printResult("Chaining method(hash2)", h2,checking);
    printResult("Double Hashing(hash1)", h3,checking);
    printResult("Double Hashing(hash2)", h4,checking);
    printResult("Custom Probing(hash1)", h5,checking);
    printResult("Custom Probing(hash2)", h6, checking);
 }
