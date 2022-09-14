#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<queue>
#include<set>
#include<utility>    
using namespace std;
typedef long long ll;
vector<pair<int,ll>>g[200000];
int n,m;
ll prim(){
    vector<ll>min(n+1,LLONG_MAX);
    vector<bool>visit(n+1,false);
    min[1]=0;
    set<pair<ll,int>>q;
    q.insert({0,1});
    ll weight=0;
    for (int i=1;i<=n;i++){
      if (q.empty()){
            return -1;
      }
      weight+=q.begin()->first;
      int v=q.begin()->second;
      visit[v]=true;
      q.erase(q.begin());
      for (auto u:g[v]){
          if (!visit[u.first] and u.second<min[u.first]){
              q.erase({min[u.first],u.first});
              min[u.first]=u.second;
              q.insert({u.second,u.first});
          }
      }
   } return weight;
} 
int main(){
   cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v,d;
        cin>>u>>v>>d;
        g[u].push_back({v,d});
        g[v].push_back({u,d});
    } ll ans=prim();
    if (ans==-1) cout <<"IMPOSSIBLE";
    else{
        cout <<ans;
    }
}