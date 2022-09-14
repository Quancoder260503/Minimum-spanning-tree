#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
const int sz=2e5+5;
const int sz1=sz*sz;
ll n,k,m,q,T,ans,p;
ll a[sz];
ll  par[sz];
ll compsize[sz];
bool on[sz];
vector<array<ll,2>>dis;
vector<array<ll,3>>edge;
void init(int n){
    for(int i=1;i<=n;i++){
        par[i]=i;
        compsize[i]=1;
    }
}
ll find(int x){
    if(x==par[x]) return x;
    else return x=find(par[x]);
}
void unite(int x,int y){
    x=find(x); y=find(y);
    if(x==y) return;
    if(compsize[x]<compsize[y]) swap(x,y);
    compsize[x]+=compsize[y];
    par[y]=x;
}
void solve(){
    cin>>n>>p;
    ans=0;
    init(n); dis.clear();
    for(int i=1;i<=n;i++) a[i]=0;
    for(int i=1;i<=n;i++){
        cin>>a[i]; 
        dis.push_back({a[i],i});
    } 
    sort(dis.begin(),dis.end());
    for(auto v:dis){
        ll at=v[0]; ll j=v[1]+1;
        while (at<=a[j] and j<=n){
            if(a[j]%at!=0) break;
            if(a[j]%at==0){
                if(find(v[1])==find(j)) break;
                unite(v[1],j);
                ans+=min(p,v[0]);
            };
            j++;
        }
        j=v[1]-1;
        while(at<=a[j] and j>0){
            if(a[j]%at!=0) break;
            if(a[j]%at==0){
                if(find(v[1])==find(j)) break;
                unite(v[1],j);
                ans+=min(p,v[0]);
            }
            j--;
         }
     }  
     for(int i=1;i<=n;i++){
         if(i<n){
             if(find(i)!=find(i+1)){
                 unite(i,i+1);
                 ans+=p;
             }
         }
         if(i>1){
             if(find(i)!=find(i-1)){
                 unite(i,i-1);
                 ans+=p;
             }
         }
     }
     cout<<ans<<endl;
}
int main(){  
    int t;cin>>t;   
    while(t--){
        solve();
    }
}