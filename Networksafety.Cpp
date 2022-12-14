#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=5e5+10;
const int sz1=1e6+1;
const int inf=1e9 + 7;
const int mod = 1e9 + 7;
int n,m,k,w;
long long a[sz];
long long pw2[sz];
int compsize[sz];
int parent[sz];
vector<array<long long,3>>edge;
int find(int u){
     if(u == parent[u]) return u;
     return find(parent[u]);
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return;
     if(compsize[u] > compsize[v]) swap(u,v);
     parent[u] = v;
     compsize[v] += compsize[u];
}
int main(){
      scanf("%d%d%d",&n,&m,&k);
      for(int i = 1;i <= n; i++){
          scanf("%lld", a + i);
      }
      for(int i = 1; i <= m; i++){
            int u,v; scanf("%d%d",&u,&v);
            edge.push_back({a[u]^a[v],u,v});
      }
      pw2[0] = 1;
      long long ans = 0;
      for(int i = 1; i <= n; i++){
          compsize[i] = 1;
          parent[i] = i;
          pw2[i] = pw2[i - 1]%mod*2%mod;
      }
     set<long long>dis;
     sort(edge.begin(),edge.end());
     for(int i = 0, j = 0; i < edge.size(); i = j){
           set<int>vis;
           int compsz = 0;
           int nocomp = 0;
           dis.insert(edge[i][0]);
           while(edge[i][0] == edge[j][0]){
                 int u,v; u = edge[j][1]; v = edge[j][2];
                 j++;
                 if(find(u) == find(v)) continue;
                 unite(u,v);
                 vis.insert(u);
                 vis.insert(v);
           }
           for(auto it = vis.begin(); it != vis.end(); it++){
                 int v = (*it);
                 if(parent[v] == v){
                     compsz+=compsize[v];
                     nocomp++;
                 }
                 parent[v] = v;
                 compsize[v] = 1;
   
           }
           int com = n - compsz  + nocomp;
           ans = (ans + pw2[com])%mod;       
      }
      if(n > 300000 or k > 30){
            int re = ((1ll)*pw2[k]%mod - dis.size()%mod)%mod;
            ans = (ans + re%mod*pw2[n]%mod)%mod;
            cout<<ans<<endl; 
            return 0;
      }
      int re = ((1ll)*(1<<k)%mod - dis.size()%mod)%mod;
      ans = (ans + re%mod*pw2[n]%mod)%mod;
      cout<<ans<<endl; 
}
