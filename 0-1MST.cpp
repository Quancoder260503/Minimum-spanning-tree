#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
const int sz=1e5+5;
ll n,k,m,q,T,p,ans,start;
ll dp[sz];
ll edgeid[sz];
ll weight[sz];
ll e[sz];
set<ll>adj[sz];
set<ll>ver;
vector<ll>ed;
int compsize[sz];
int par[sz];
vector<array<ll,3>>val;
ll bfs(int i){
    if(!ver.count(i)) return 0;
    ver.erase(i);
    queue<ll>q;
    q.push(i);
    while(q.size()){
        int t=q.front();
        q.pop();
        vector<ll>add;
        for(auto i:ver){ if(!adj[t].count(i)) add.push_back(i);}
        for(auto v:add){
            q.push(v);
            ver.erase(v);
        }
    } return 1;
}
int main(){
    cin>>n>>m;
    ans=-1;
    for(int i=1;i<=m;i++){
        ll u,v;cin>>u>>v;
        adj[v].insert(u);
        adj[u].insert(v);
    }
   for(int i=1;i<=n;i++) ver.insert(i);
   for(int i=1;i<=n;i++){
       ans+=bfs(i);
   } cout<<ans<<endl;
}