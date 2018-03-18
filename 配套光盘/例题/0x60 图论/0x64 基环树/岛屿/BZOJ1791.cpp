#include<iostream>
#include<cstdio>
using namespace std;
const int u=1000010;
int ver[2*u],edge[2*u],next[2*u],head[u],du[u],c[u],v[u],q[2*u];
long long f[u],d[u],a[2*u],b[2*u],ans;
int n,m,tot,t,i,x,y;

void add(int x,int y,int z)
{
	ver[++tot]=y; edge[tot]=z; next[tot]=head[x]; head[x]=tot; du[y]++;
}

void bfs(int s,int t)
{
	int l,r,i;
	q[l=r=1]=s; c[s]=t;
	while(l<=r)
	{
		for(i=head[q[l]];i;i=next[i])
			if(!c[ver[i]]) {q[++r]=ver[i]; c[ver[i]]=t;}
		l++;
	}
}

void topsort()
{
	int l=1,r=0,i,x,y;
	for(i=1;i<=n;i++)
		if(du[i]==1) q[++r]=i;
	while(l<=r)
	{
		for(i=head[x=q[l]];i;i=next[i])
			if(du[y=ver[i]]>1)
			{
				d[c[x]]=max(d[c[x]],f[x]+f[y]+edge[i]);
				f[y]=max(f[y],f[x]+edge[i]);
				if((--du[y])==1) q[++r]=y;
			}
		l++;
	}
}

void dp(int t,int x)
{
	int m=0,i,l=0,r,y=x;
	do{
		a[++m]=f[y]; du[y]=1;
		for(i=head[y];i;i=next[i])
			if(du[ver[i]]>1)
				{y=ver[i]; b[m+1]=b[m]+edge[i]; break;}
	}while(i);
	if(m==2)
	{
		for(i=head[y];i;i=next[i])
			if(ver[i]==x) {l=max(l,edge[i]);}
		d[t]=max(d[t],f[x]+f[y]+l);
		return;
	}
	for(i=head[y];i;i=next[i])
		if(ver[i]==x) {b[m+1]=b[m]+edge[i]; break;}
	for(i=1;i<m;i++) {a[m+i]=a[i]; b[m+i]=b[m+1]+b[i];}
	q[l=r=1]=1;
	for(i=2;i<2*m;i++)
	{
		while(l<=r&&i-q[l]>=m) l++;
		d[t]=max(d[t],a[i]+a[q[l]]+b[i]-b[q[l]]);
		while(l<=r&&a[q[r]]+b[i]-b[q[r]]<=a[i]) r--;
		q[++r]=i;
	}
}

int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		add(i,x,y); add(x,i,y);
	}
	for(i=1;i<=n;i++)
		if(!c[i]) bfs(i,++t);
	topsort();
	for(i=1;i<=n;i++)
		if(du[i]>1&&!v[c[i]])
		{
			v[c[i]]=1;
			dp(c[i],i);
			ans+=d[c[i]];
		}
	cout<<ans<<endl;
	return 0;
}