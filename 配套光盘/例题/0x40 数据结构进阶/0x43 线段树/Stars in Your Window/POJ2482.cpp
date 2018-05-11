#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int u=20010;
struct rec{unsigned int x,l,r; int c;}a[u];
struct{int p,l,r,dat,add;}t[u*4];
unsigned int b[u],c[u],x,y,w,h;
int n,m,p,i,ans,z;

bool cmp(rec a,rec b)
{
	return a.x<b.x||a.x==b.x&&a.c<b.c;
}

void build(int p,int l,int r)
{
	t[p].l=l,t[p].r=r,t[p].dat=t[p].add=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
}

void spread(int p)
{
	if(t[p].add)
	{
		t[p*2].dat+=t[p].add,t[p*2].add+=t[p].add;
		t[p*2+1].dat+=t[p].add,t[p*2+1].add+=t[p].add;
		t[p].add=0;
	}
}

void change(int p,int l,int r,int c)
{
	if(l<=t[p].l&&r>=t[p].r)
	{
		t[p].dat+=c,t[p].add+=c;
		return;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)>>1;
	if(l<=mid) change(p*2,l,r,c);
	if(r>mid) change(p*2+1,l,r,c);
	t[p].dat=max(t[p*2].dat,t[p*2+1].dat);
}

int main()
{
	while(cin>>n>>w>>h)
	{
		for(m=p=0,i=1;i<=n;i++)
		{
			scanf("%u%u%d",&x,&y,&z);
			a[i].l=a[n+i].l=y,a[i].r=a[n+i].r=y+h-1;
			a[i].x=x,a[n+i].x=x+w,a[i].c=z,a[n+i].c=-z;
			b[++m]=y,b[++m]=y+h-1;
		}
		sort(b+1,b+m+1);
		for(i=1;i<=m;i++)
			if(i==1||b[i]!=b[i-1]) c[++p]=b[i];
		for(n*=2,i=1;i<=n;i++)
		{
			a[i].l=lower_bound(c+1,c+p+1,a[i].l)-c;
			a[i].r=lower_bound(c+1,c+p+1,a[i].r)-c;
		}
		sort(a+1,a+n+1,cmp);
		build(1,1,p);
		for(ans=0,i=1;i<=n;i++)
		{
			change(1,a[i].l,a[i].r,a[i].c);
			ans=max(ans,t[1].dat);
		}
		cout<<ans<<endl;
	}
	return 0;
}
