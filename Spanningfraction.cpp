#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=1e5+1;
int n,m,k;
int cnt=0;
ll ans=0;
int parent[sz];
int compsize[sz];
ld C;
ll X,Y;
vector<array<int,4>>edge;
#experience; when binary search with real number dont assign low= mid +1 like usual;
void init(int n){
	for (int i = 0; i < n; i++){
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
ld cmp(array<int,4>a,array<int,4>b){
    return -a[0]+C*a[1]<-b[0]+C*b[1];
}
ld kruskal(ld p){
    C=p;X=0;Y=0;
    sort(edge.begin(),edge.end(),cmp);
    init(n);
    ld ans=C;int cnt=0;
    for(auto e:edge){
        if (cnt==n-1) break;
        if (find(e[2])!=find(e[3])){
            unite(e[2],e[3]);
            ans=e[0]-C*e[1]+ans;
            cnt++;
            X+=e[0];
            Y+=e[1];
        }
    }
      if (ans<0) return 0;
      else return ans;
}    
ll findgcd(ll x,ll y){
    if (min(x,y)==0) return max(x,y);
    return gcd(max(x,y)%min(x,y),min(x,y));
}
int main(){
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v,x,y;
        cin>>u>>v>>x>>y;
        edge.push_back({x,y,u,v});
    }  int count=0;
       ld high=1e7; ld low=0;
         while (high>low){
           if (count==55) break;
           ld mid=(high+low)/2;
           if (kruskal(mid)){
               low=mid;
               count++;
           } else{
               high=mid;
               count++;
           }
       } kruskal(low);
       ll x=findgcd(X,Y);
       cout<<X/x<<" / "<<Y/x<<endl;
}