#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=5e5+1;
const int inf=1e6+1;
int n,q,m,t;
int par0[sz];
int par1[sz];
int cnt[sz];
bool ans[sz];
struct node{
    int v,u,id,w;
}  edge[sz],query[sz];
int cmp(node a,node b){
    if(a.w==b.w) return a.id<b.id;
    else return a.w<b.w;
}
int cmp1(node a,node b){
     return a.w<b.w;
}
void init(int n){
    for(int i=1;i<=n;i++){
        par0[i]=par1[i]=i;
    }
}
int find0(int x){
    if(par0[x]==x) return x;
    return find0(par0[x]);
}
int find1(int x){
    if(cnt[x]!=t){
        cnt[x]=t,par1[x]=par0[x];
    }
    if(par1[x]==x) return x;
    else{
        par1[x]=find1(par1[x]);
        return par1[x];
    }
}
int main(){
     cin>>n>>m;
     init(n);
     for(int i=1;i<=m;i++){
         cin>>edge[i].u>>edge[i].v>>edge[i].w;
     }
     cin>>q; 
     int queries=0;
     for(int i=0;i<q;i++){
         int k;cin>>k;
         for(int j=0;j<k;j++){
              queries++; int v;cin>>v;
              query[queries]=edge[v];
              query[queries].id=i+1;
         }
     }
     sort(query+1,query+queries+1,cmp);
     sort(edge+1,edge+m+1,cmp1);
     int pos=1;
      for(int i=1,j=1;i<=queries;i=pos){
         while(j<=m and edge[j].w<query[i].w){
             int x=find0(edge[j].u);
             int y=find0(edge[j].v);
             if(x!=y) par0[y]=x;
             j++;
         }
         while(pos<=queries and query[i].w==query[pos].w){
              if(pos==i || query[pos].id!=query[pos-1].id) t++;
              int x=find1(query[pos].u);
              int y=find1(query[pos].v);
              if(x!=y) par1[y]=x;
              else ans[query[pos].id]=1;
              pos++;
         }
     }
      for(int i=1;i<=q;i++){
          if(!ans[i]) cout<<"YES"<<endl;
          else cout<<"NO"<<endl;
      }
}