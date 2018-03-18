#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int u=30000,w=200000;
int head[u],ver[w],edge[w],next[w],tot;
int dfn[u],low[u],st[u],ins[u],num,t;
int e[u],go[u],h[u],c[u],scc;
int d[u],f[u],v[u],du[u],q[u];
int n,m,s,P,p,i,j,x,y,z,l,r;

void add(int x,int y,int z)
{
	ver[++tot]=y; edge[tot]=z; next[tot]=head[x]; head[x]=tot;
}

inline void addscc(int x,int y)
{
	e[++scc]=y; go[scc]=h[x]; h[x]=scc; c[y]=x;
}

void tarjan(int x)
{
	v[x]=1;
	dfn[x]=low[x]=++num;
	st[++p]=x; ins[x]=1;
	for(int i=head[x];i;i=next[i])
		if(!v[ver[i]])
		{
			tarjan(ver[i]);
			low[x]=min(low[x],low[ver[i]]);
		}
		else if(ins[ver[i]])
			low[x]=min(low[x],dfn[ver[i]]);
		if(dfn[x]==low[x])
		{
			++t; int y;
			do{
				y=st[p]; p--; ins[y]=0;
				addscc(t,y);
			}while(x!=y);
		}
}

void up(int x)
{
	while(x>1)
		if(d[f[x]]<d[f[x>>1]])
		{
			swap(f[x],f[x>>1]);
			swap(v[f[x]],v[f[x>>1]]);
			x>>=1;
		}
		else break;
}

void down(int x,int y)
{
	int z=x*2;
	while(z<=y)
	{
		if(z<y&&d[f[z]]>d[f[z+1]]) z++;
		if(d[f[x]]>d[f[z]])
		{
			swap(f[x],f[z]);
			swap(v[f[x]],v[f[z]]);
			x=z; z=x*2;
		}
		else break;
	}
}

void heapdijk(int s)
{
	p=0;
	for(i=h[s];i;i=go[i])
	{
		f[++p]=e[i]; v[e[i]]=p;
		up(p);
	}
	while(p)
	{
		x=f[1]; v[x]=0;
		f[1]=f[p]; v[f[1]]=1; p--;
		down(1,p);
		for(i=head[x];i;i=next[i])
			if(c[ver[i]]==s)
			{
				if(d[ver[i]]>d[x]+edge[i])
				{
					d[ver[i]]=d[x]+edge[i];
					up(v[ver[i]]);
				}
			}
			else{
				d[ver[i]]=min(d[ver[i]],d[x]+edge[i]);
				du[c[ver[i]]]--;
				if(!du[c[ver[i]]]) q[++r]=c[ver[i]];
			}
	}
}

int main()
{
	cin>>n>>m>>P>>s;
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	for(i=1;i<=n;i++)
		if(!v[i]) tarjan(i);
	for(i=1;i<=P;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		du[c[y]]++;
	}
	memset(v,0,sizeof(v));
	memset(d,0x3f,sizeof(d));
	d[s]=0;
	l=1; r=0; 
	for(i=1;i<=t;i++)
		if(!du[i]) {q[++r]=i;}
	while(l<=r)
	{
		heapdijk(q[l]);
		l++;
	}
	for(i=1;i<=n;i++)
		if(d[i]>100000000) printf("NO PATH\n");
		else printf("%d\n",d[i]); 
	return 0;
}