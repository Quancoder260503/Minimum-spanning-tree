#include<bits/stdc++.h>
using namespace std;
const int sz=1e3+1;
typedef long long ll;
int l,r,mod,n,q,m,k;
int cnt;
vector<array<ll,4>>edge;
int compsz[sz][sz*10];
int par[sz][sz*10];
int ans[300001];
void init(int n,int k){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            par[i][j]=i;
            compsz[i][j]=1;
        }
    }
}
int find(int x,int t){
    if(x==par[x][t]) return x;
    else return find(par[x][t],t);
}
void unite(int x,int y,int t){
     x=find(x,t); y=find(y,t);
     if(x==y) return;
     if(compsz[x][t]<compsz[y][t]) swap(x,y);
     compsz[x][t]+=compsz[y][t];
     par[y][t]=x;
}
int main(){
      cin>>n>>m>>k;
      init(n,k);
      for (int i=1;i<=m;i++){
           int u,v;ll w;cin>>u>>v>>w;
           edge.push_back({w,u,v,i});
      }
      sort(edge.rbegin(),edge.rend());
      for(auto e: edge){
           int high=k;
           int low=1;
           while (high>low){
                int mid=(high+low)/2;
                if(find(e[2],mid)!=find(e[1],mid)) high=mid;
                else low=mid+1; 
           }
           if(find(e[1],low)==find(e[2],low)) continue;
           unite(e[1],e[2],low);
           ans[e[3]]=low;
      }
      for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
}