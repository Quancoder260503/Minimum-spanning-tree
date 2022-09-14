#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;

const int sz=2002*2002;
const int sz1=2001;
ll parent[sz];
ll compsize[sz];
int n,m,A,B;
ll res=0;
ll a[sz1];
ll b[sz1];
exp: try not to store the large value(1e5 etc ) in the edge and building spanning tree on a grid , we dont need to assume the node in the grid order (follow spanning tree order)
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
int mul(int x,int y){
    return x*(m+1)+y;
}
int main(){
    cin>>A>>B>>n>>m;
    for (int i = 0; i < n ; i++){
        cin>>a[i];
    } for (int i= 0 ; i < m; i++){
        cin>>b[i];
    }
    sort(a,a+n+1);
    sort(b,b+m+1);
    for (int i=0;i<n;i++){
        a[i]=a[i+1]-a[i];
    } a[n]=A-a[n];
      for (int j=0;j<m;j++){
          b[j]=b[j+1]-b[j];
     } b[m]=B-b[m];
    int hi=0,vi=0;
    sort(a,a+n+1);
    sort(b,b+m+1);
    init ((n+1)*(m+1));
    while(hi<m+1 or vi<n+1){
        if (hi==m+1 or (vi<n+1 and a[vi]<b[hi])){
             for (int i=0;i<m;i++){
                    if (find(mul(vi,i))==find(mul(vi,i+1))) continue;
                    unite(mul(vi,i),mul(vi,i+1));
                    res+=a[vi];
             } vi++;
        } else{
            for(int i=0;i<n;i++){
                if (find(mul(i+1,hi))==find(mul(i,hi))) continue;
                unite(mul(i+1,hi),mul(i,hi));
                res+=b[hi];
            } hi++;
        }
    } cout <<res;
}