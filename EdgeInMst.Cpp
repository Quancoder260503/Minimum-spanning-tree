#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> info; 
const int N = 5e5 + 5;
int up[21][N + 1],dp[N + 1],par[N + 1];
int a[N + 1];
int n,m,q;
vector<pair<int,int>>tadj[N + 1];
vector<pair<int,int>>adj[N + 1]; 
int trs,dsz,psz;
vector<array<int,4>>edges;
int cnt; 
bool vis[N + 1],use[N + 1],brid[N + 1]; 
long long ds[21][N + 1];
int st[N + 1],low[N + 1];
int comp[N + 1];
int fa[N + 1];
map<int,int>mp[N + 1];
pair<int,int>ans[N + 1];
int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]);
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return;
     if(comp[u] > comp[v]) swap(u,v); 
     comp[v] += comp[u]; 
     fa[u] = v;
}
void dfs(int u,int p){
    a[u] = low[u] = ++dsz;
    for(int i = 0; i < tadj[u].size(); i++){
        auto x = tadj[u][i];
        int v = x.first;
        if(v == p) continue;
        if(!a[v]){
            dfs(v,u);
            low[u] = min(low[u] , low[v]);
            if(low[v] > a[u] and mp[u][v] == 1) brid[x.second] = 1; 
        }
        else low[u] = min(a[v] , low[u]);
    }
}
void calc(vector<array<int,4>>&edges){
      dsz = 0; 
      for(int i = 0; i < edges.size(); i++){
          int u = find(edges[i][2]); int v = find(edges[i][3]); 
          mp[u][v] = 0; mp[v][u] = 0;
          tadj[u].clear(); tadj[v].clear(); 
          a[u] = a[v] = low[u] = low[v] = 0; 
      }
      for(int i = 0; i < edges.size(); i++){
          int u = find(edges[i][2]); int v = find(edges[i][3]);
          if(u == v) continue;
          use[edges[i][1]] = 1; 
          tadj[u].push_back({v,edges[i][1]});
          tadj[v].push_back({u,edges[i][1]}); 
          mp[v][u]++; mp[u][v]++;
      }
      for(int i = 0; i < edges.size(); i++){
           int u = find(edges[i][2]);
           if(!a[u]) dfs(u,0); 
      }
      for(int i = 0; i < edges.size(); i++) unite(edges[i][2],edges[i][3]); 
}
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 1; i <= n; i++) fa[i] = i, comp[i] = 1;
     for(int i = 0; i < m; i++){
         int u,v,w; scanf("%d%d%d",&u,&v,&w);
         edges.push_back({w,i,u,v}); 
     }
     sort(edges.begin(),edges.end()); 
     vector<array<int,4>>weight;
     for(int i = 0; i < m; i++){
          if(!weight.empty() and weight.back()[0] == edges[i][0]){
               weight.push_back(edges[i]); 
          }
          else{
             calc(weight);
             weight = {edges[i]};
          }
     }
     calc(weight);
     for(int i = 0; i < m; i++){
          if(brid[i]){
               printf("any \n");
               continue;
          }
          if(use[i]){
               printf("at least one \n");
               continue; 
          }
          printf("none \n");
     }
     return 0;
}
