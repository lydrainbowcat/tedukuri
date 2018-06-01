#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int u=200010;
struct rec{int x,y;}a[u],f[3];
long long dis[u];
int ver[2*u],edge[2*u],Next[2*u],head[u],d[u],s[u],v[u];
queue<int> q;
int n,m,tot,t,i,j,k,x,y,z,ans,MIN;

bool cmp(rec a,rec b)
{
	return dis[a.x]<dis[b.x];
}

void add(int x,int y,int z)
{
	ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}

void size(int x)
{
	s[x]=1,v[x]=1;
	for(int i=head[x];i;i=Next[i])
		if(!v[ver[i]])
		{
			size(ver[i]);
			s[x]+=s[ver[i]];
		}
	v[x]=0;
}
 
void center(int y)
{
	int temp=s[x]-s[y];
	v[y]=1;
	for(int i=head[y];i;i=Next[i])
		if(!v[ver[i]])
		{
			center(ver[i]);
			temp=max(temp,s[ver[i]]);
		}
	if(temp<MIN) MIN=temp,z=y;
	v[y]=0;
}

void treedp(int x)
{
	v[x]=1;
	a[++t].x=x,a[t].y=y;
	for(int i=head[x];i;i=Next[i])
		if(!v[ver[i]])
		{
			d[ver[i]]=d[x]+1;
			dis[ver[i]]=dis[x]+edge[i];
			treedp(ver[i]);
		}
	v[x]=0;
}

int main()
{
	cin>>n>>m;
	for(i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x+1,y+1,z),add(y+1,x+1,z);
	}
	ans=n+1;
	q.push(1);
	while(q.size())
	{
		x=q.front(),q.pop();
		MIN=n;
		size(x);
		center(x);
		v[x=z]=1,t=0;
		for(i=head[x];i;i=Next[i])
			if(!v[y=ver[i]])
			{
				d[y]=1,dis[y]=edge[i];
				treedp(y);
				q.push(y);
			}
		sort(a+1,a+t+1,cmp);
		for(i=1;i<=t;i++)
			if(dis[a[i].x]==m) ans=min(ans,d[a[i].x]);
		for(i=1,j=k=t;i<=t;i++)
		{ 
			if(i==1||dis[a[i].x]>dis[a[i-1].x])
			{
				j=k,f[1].x=f[2].x=n+1;
				while(j>i&&dis[a[j].x]+dis[a[i].x]>m) j--;
				if(j<=i) break; else k=j;
				if(dis[a[j].x]+dis[a[i].x]!=m) continue;
				for(;k>i&&dis[a[j].x]==dis[a[k].x];k--)
					if(d[a[k].x]<f[1].x)
					{
						if(f[1].y!=a[k].y) f[2]=f[1];
						f[1].x=d[a[k].x],f[1].y=a[k].y;
					}
					else if(d[a[k].x]<f[2].x&&a[k].y!=f[1].y)
						f[2].x=d[a[k].x],f[2].y=a[k].y;
			}
			if(a[i].y!=f[1].y) ans=min(ans,d[a[i].x]+f[1].x); else ans=min(ans,d[a[i].x]+f[2].x);
		}
	}
	if(ans>n) ans=-1;
	cout<<ans<<endl;
	return 0;
}