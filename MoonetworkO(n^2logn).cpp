#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
int n,k;
int cnt=0;
ll ans=0;
vector<pair<int,int>>cor;
ll parent[sz];
ll compsize[sz];
vector<pair<ll,pair<int,int>>>edge;
void init(int n){
	for (int i = 1; i <= n; i++){
		parent[i] = i;
		compsize[i] = 1;
	}
}
int find(int a){
	if (a == parent[a]) return a;
	else return parent[a] = find(parent[a]);
}
void unite(int a, int b){
	int roota = find(a), rootb = find(b);
	if (roota == rootb) return ;
	if (compsize[roota] > compsize[rootb]) swap(roota, rootb);
	parent[roota] = rootb;
	compsize[rootb] += compsize[roota];
}
void kruskal(int n ){
    init(n);
    sort(edge.begin(),edge.end());
    for (auto a:edge){
         if (cnt==n-1) break;
         ll w=a.first; int u=a.second.first; int v=a.second.second;
         if(find(u)==find(v)) continue;
         unite(u,v);
         ans+=w;
         cnt++;
    }
}
ll sqr(ll x,ll y){
    return (x-y)*(x-y);
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        int u,v;
        cin>>u>>v;
        cor.push_back({u,v});
    } 
    for (int i=0;i<n;i++){
        for (int j=i+1;j<n;j++){
            ll x=sqr(cor[i].first,cor[j].first)+sqr(cor[i].second,cor[j].second);
            edge.push_back({x,{i,j}});
        }
    }
       kruskal(n);
       cout <<ans;
}   
