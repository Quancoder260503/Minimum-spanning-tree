#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+5;
ll n,k,m,q,T,p,start,cnt;
int compsz[sz];
int par[sz];
vector<ll>to1;
bool vis[sz];
bool a[sz];
vector<array<ll,2>>deg;
vector<array<ll,2>>ans;
vector<array<ll,2>>edge;
vector<ll>adj[sz];
void dfs(int v);
void init(int n){
    for(int i=1;i<=n;i++){
        compsz[i]=1;
        par[i]=i;
    }
}
int find(int x){
    if(x==par[x]) return x;
    else return find(par[x]);
}
void unite(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return;
    if(compsz[x]<compsz[y]) swap(x,y);
    compsz[x]+=compsz[y];
    par[y]=x;
}
void dfs(int u){
    if(u==1) return;
    vis[u]=1;
    for(auto v:adj[u]) if(!vis[v]) dfs(v);
}
int main(){
    cin>>n>>m>>q;
    init(n);
    for(int i=1;i<=m;i++){
        ll u,v;cin>>u>>v;
        edge.push_back({u,v});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            cnt++;
            dfs(i);
        }
    }
    if(cnt>q or adj[1].size()<q){cout<<"NO";exit(0);}
    for(auto e:edge){
        if(find(e[0])==find(e[1])) continue;
        if(e[1]==1 or e[0]==1) continue;
        unite(e[0],e[1]);
    }
    for(auto x:adj[1]){
        int anc=find(x);
        if(a[anc]) continue;
        a[anc]=1;
        deg.push_back({compsz[find(x)],x});
    }
    init(n);
    sort(deg.rbegin(),deg.rend());
    cnt=0;
    for(auto v:deg){
        if(v[0]!=1) continue;
        cnt++;
        unite(1,v[1]);
        ans.push_back({1,v[1]});
    }
    for(auto v:deg){
        if(cnt==q) break;
        if(find(v[0])==find(v[1])) continue; 
        cnt++;
        unite(v[1],1);
        ans.push_back({v[1],1});
    }
    for(auto v:adj[1]){
        if(cnt==q) break;
        if(find(v)==find(1)) continue;
        cnt++;
        unite(v,1);
        ans.push_back({v,1});
    }
    for(auto e:edge){
        if(find(e[0])==find(e[1])) continue;
        if(e[1]==1 or e[0]==1) continue;
        unite(e[0],e[1]);
        ans.push_back({e[0],e[1]});
    }
      cout<<"YES"<<endl;
      for(auto a:ans) cout<<a[0]<<" "<<a[1]<<endl;
}