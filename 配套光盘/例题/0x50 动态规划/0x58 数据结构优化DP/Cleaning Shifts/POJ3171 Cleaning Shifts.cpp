#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=4e5,INF=0x3f3f3f3f,root=1;
struct Node{
	int l,r,val;
	bool operator <(Node another)const{
		return r<another.r;
	}
}tr[MAXN],a[MAXN];
int f[MAXN];
void build(int p,int l,int r){
	tr[p].l=l,tr[p].r=r;
	if(l==r){
		tr[p].val=f[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build((p<<1)|1,mid+1,r);
	tr[p].val=min(tr[p<<1].val,tr[(p<<1)|1].val);
}
int query(int p,int ll,int rr){
	int l=tr[p].l,r=tr[p].r;
	if(l>=ll&&r<=rr){
		return tr[p].val;
	}
	int mid=(l+r)>>1;
	int ans=INF;
	if(ll<=mid)ans=min(ans,query(p<<1,ll,rr));
	if(rr>mid)ans=min(ans,query((p<<1)|1,ll,rr));
	return ans;
}
void change(int p,int x,int val){
	int l=tr[p].l,r=tr[p].r;
	if(l==r){
		tr[p].val=val;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)change(p<<1,x,val);
	else if(x>mid)change((p<<1)|1,x,val);
	tr[p].val=min(tr[p<<1].val,tr[(p<<1)|1].val);
}
int main(){
	int n,l,r;
	scanf("%d%d%d",&n,&l,&r);
	l+=2,r+=2;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].val);
		a[i].l+=2,a[i].r+=2;
	}
	sort(a+1,a+1+n);
	memset(f,0x3f,sizeof(f));
	f[l-1]=0;
	build(root,l-1,r);
	int ans=INF;
	for(int i=1;i<=n;i++){
		f[a[i].r]=min(f[a[i].r],query(root,a[i].l-1,a[i].r)+a[i].val);
		change(root,a[i].r,f[a[i].r]);
		if(a[i].r>=r){
			ans=min(ans,f[a[i].r]);
		}
	}
	if(ans==INF)printf("-1\n");
	else printf("%d\n",ans);
	return 0;
}
