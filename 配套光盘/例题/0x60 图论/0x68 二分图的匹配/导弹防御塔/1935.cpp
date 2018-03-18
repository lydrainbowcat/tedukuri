#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
struct rec{int x,y;}a[60],b[60];
struct{int x; double y;}c[2510];
int v[2510],ver[50*2510],next[50*2510],head[60],f[2510];
int n,m,t2,V,t,cnt,tot,i,j;
double t1,l,r,mid;

double dist(rec a,rec b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)*1.0+(a.y-b.y)*(a.y-b.y)*1.0);
}

void add(int x,int y)
{
	ver[++tot]=y,next[tot]=head[x],head[x]=tot;
}

bool dfs(int x)
{
	for(int i=head[x];i;i=next[i])
		if(!v[ver[i]])
		{
			v[ver[i]]=1;
			if(!f[ver[i]]||dfs(f[ver[i]]))
			{f[ver[i]]=x; return 1;}
		}
	return 0;
}

int main()
{
	while(cin>>n>>m>>t1>>t2>>V)
	{
		t1/=60;
		for(i=1;i<=m;i++) scanf("%d%d",&a[i].x,&a[i].y);
		for(i=1;i<=n;i++) scanf("%d%d",&b[i].x,&b[i].y);
		t=m*n;
		for(i=1;i<=m;i++)
			for(j=1;j<=n;j++)
				c[(i-1)*n+j].x=j,c[(i-1)*n+j].y=(i-1)*(t1+t2)+t1;
		l=t1,r=cnt*(t1+t2)+30000;
		while(l+1e-8<r)
		{
			mid=(l+r)/2;
			memset(head,0,sizeof(head)); tot=0;
			memset(f,0,sizeof(f));
			for(i=1;i<=m;i++)
				for(j=1;j<=t;j++)
					if(c[j].y+dist(a[i],b[c[j].x])/V<=mid) add(i,j);
			for(i=1;i<=m;i++)
			{
				for(j=1;j<=t;j++) v[j]=0;
				if(!dfs(i)) break;
			}
			if(i>m) r=mid; else l=mid;
		}
		printf("%.6f\n",l);
	}
	return 0;
}
