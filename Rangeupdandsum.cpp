#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n,x,k,i,j,w,q;
ll a[sz];
struct node{
    ll val;
    ll lzadd;
    ll lzset;
    node(){};
};
node tree[sz<<2];
void push(int p){
    tree[p].val=tree[2*p+1].val+tree[2*p].val;
}
void pushdown(int p,int l,int mid,int r){
    if(tree[p].lzset!=0){
        tree[2*p+1].lzset=tree[2*p].lzset=tree[p].lzset;
        tree[2*p].val=(mid-l+1)*tree[p].lzset;
        tree[2*p+1].val=(r-mid)*tree[p].lzset;
        tree[2*p].lzadd=tree[2*p+1].lzadd=0;
        tree[p].lzset=0;
    } else if(tree[p].lzadd!=0){
        if(tree[2*p].lzset==0) tree[2*p].lzadd+=tree[p].lzadd;
        else{
            tree[2*p].lzset+=tree[p].lzadd;
            tree[2*p].lzadd=0;
        }
        if(tree[2*p+1].lzset==0) tree[2*p+1].lzadd+=tree[p].lzadd;
        else{
            tree[2*p+1].lzset+=tree[p].lzadd;
            tree[2*p+1].lzadd=0;
        } tree[2*p].val+=tree[p].lzadd*(mid-l+1);
          tree[2*p+1].val+=tree[p].lzadd*(r-mid);
          tree[p].lzadd=0;
    } return;
}
void build(int l=1,int r=n,int node=1){
    tree[node].lzadd=tree[node].lzset=0;
    if(l==r){
        tree[node].val=a[l];
        return;
    }else{
        int mid=(l+r)>>1;
        build(l,mid,node*2);
        build(mid+1,r,node*2+1);
        push(node);
        return;
    }
}
void add(ll x,int L,int R,int l=1,int r=n,int node=1){
    if(l>R or L>r) return;
    if(L<=l and r<=R){
        tree[node].val+=(r-l+1)*x;
        if(tree[node].lzset==0) tree[node].lzadd+=x;
        else tree[node].lzset+=x;
        return;
    }
        int mid=(l+r)>>1;
        pushdown(node,l,mid,r);
        add(x,L,R,l,mid,node*2);
        add(x,L,R,mid+1,r,node*2+1);
        push(node);
        return;
}
void setval(ll x,int L,int R,int l=1,int r=n,int node=1){
    if(l>R or L>r) return;
    if(L<=l and r<=R){
        tree[node].val=(r-l+1)*x;
        tree[node].lzadd=0;
        tree[node].lzset=x;
        return;
    }
        int mid=(l+r)>>1;
        pushdown(node,l,mid,r);
        setval(x,L,R,l,mid,node*2);
        setval(x,L,R,mid+1,r,node*2+1);
        push(node);
        return;
}
ll query(int L,int R,int l=1,int r=n,int node=1){
    if(l>R or L>r) return 0;
    if(L<=l and r<=R) return tree[node].val;
    int mid=(l+r)>>1;
    pushdown(node,l,mid,r);
    return query(L,R,l,mid,2*node)+query(L,R,mid+1,r,2*node+1);
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build();
    for(int i=1;i<=q;i++){
        ll u,v,t,x; cin>>t;
        if(t==1){
            cin>>u>>v>>x;
            add(x,u,v);
        } if(t==2){
            cin>>u>>v>>x;
            setval(x,u,v);
        } if(t==3){
            cin>>u>>v;
            ll res=query(u,v);
            cout<<res<<endl;
        }
    }
}