#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=1e7+5;
const int inf=1e7+5;
int n,m,src,cnt,ans;
int a[sz];
int timer;
int dp[sz];
int d[sz];
int parent[sz];
int compsize[sz];
vector<pair<int,int>>adj[sz];
void init(int n){
	for (int i = 1; i <= n; i++){
		   parent[i] = i;
		   compsize[i] = 1;
	  }
}
int find(int a){
	   if (a == parent[a]) return a;
	   return parent[a] = find(parent[a]);
}
void unite(int a, int b){
	  int roota = find(a), rootb = find(b);
	  if (roota == rootb) return ;
	  if (compsize[roota] > compsize[rootb]) swap(roota, rootb);
	  parent[roota] = rootb;
	  compsize[rootb] += compsize[roota];
}
int main(){
      cin>>n;
      int mx = 0;
      for(int i=1;i<=n;i++){
           int x;cin>>x; 
           a[x]++, d[x]=x;
           mx = max(mx,x);
      }
      for(int i=mx-1;i>=0;i--){
          if(!a[i]) d[i]=d[i+1];
      }
      for(int i=1;i<=mx;i++){
           if(!a[i]) continue;
           for(int j=i;j<=mx;j+=i){
                int l = (i==j)? i+1:j;
                int rr = min(i+j-1,mx);
                //cout<<l<<' '<<rr<<' '<<d[l]<<' '<<i<<endl; 
                if(rr >= d[l]) adj[d[l]%i].push_back({d[l],i});
           }    
      }
      init(mx);
      for(int i=0;i<=mx;i++){
           for(int j=0;j<adj[i].size();j++){
                pair<int,int>x=adj[i][j];
                int u=x.first;
                int v=x.second;
                if(find(u)==find(v)) continue;
                unite(u,v);
                ans+=i;
            }
      }
      cout<<ans<<endl;  
} 
