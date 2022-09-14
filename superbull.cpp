#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2001;
int n,m;
ll a[sz];
int cnt=0;
vector<pair<ll,pair<int,int>>>edge;
struct DSU{
    vector<int>e;
    DSU(int n) {e=vector<int>(n+1,-1);}
    int get(int x){
        if (e[x]<0) return x;
        else return get(e[x]);
    }
    bool unite(int a,int b){
        a=get(a); b=get(b);
        if (a==b) return false;
        if(e[a]>e[b]) swap(a,b);
        e[a]+=e[b]; e[b]=a;return 1;
     }
};
int main(){
   cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    } for (int i=1;i<=n;i++){
        for (int j=i+1;j<=n;j++){
             ll x=a[i]^a[j];
             edge.push_back({-x,{i,j}});
        }
    }   
    sort(edge.begin(),edge.end());
    ll ans=0; DSU dsu(n);
    for (auto a:edge){
        if (dsu.unite(a.second.first,a.second.second)){
            ans+=a.first;
            cnt++;
        } if (cnt==n-1){
            cout <<-ans;
            exit(0);
        }
    }
}