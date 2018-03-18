#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int inf=0x3fffffff;
int a[3000],b[3000],head[110],ver[20010],edge[20010],next[20010],q[110],d[110];
int n,m,s,t,i,j,tot,maxflow,ans;

void add(int x,int y,int z)
{
	ver[++tot]=y;
	edge[tot]=z;
	next[tot]=head[x];
	head[x]=tot;
	ver[++tot]=x;
	edge[tot]=0;
	next[tot]=head[y];
	head[y]=tot;
}

bool bfs()
{
	memset(d,0,sizeof(d));
	int l,r;
	l=r=1; q[1]=s; d[s]=1;
	while(l<=r)
	{
		for(int i=head[q[l]];i;i=next[i])
			if(edge[i] && !d[ver[i]])
			{
				q[++r]=ver[i];
				d[ver[i]]=d[q[l]]+1;
				if(ver[i]==t) return 1;
			}
		l++;
	}
	return 0;
}

int dinic(int x,int f)
{
	if(x==t) return f;
	int temp=f,k;
	for(int i=head[x];i;i=next[i])
		if(edge[i] && temp && d[ver[i]]==d[x]+1)
		{
			k=dinic(ver[i],min(temp,edge[i]));
			if(!k) d[ver[i]]=0;
			edge[i]-=k;
			edge[i^1]+=k;
			temp-=k;			
		}
	return f-temp;
}

int main()
{
	while(cin>>n>>m)
	{
		char str[100];
		for(i=0;i<m;i++)
		{
			scanf("%s",&str);
			for(a[i]=0,j=1;str[j]!=',';j++) a[i]=a[i]*10+str[j]-'0';
			for(b[i]=0,j++;str[j]!=')';j++) b[i]=b[i]*10+str[j]-'0';
		}
		ans=inf;
		for(s=0;s<2;s++)
			for(t=0;t<n;t++)
				if(s!=t)
				{
					memset(head,0,sizeof(head));
					tot=1; maxflow=0;
					for(i=0;i<n;i++) 
						if(i==s||i==t) add(i,i+n,inf);else add(i,i+n,1);
					for(i=0;i<m;i++)
					{
						add(a[i]+n,b[i],inf);
						add(b[i]+n,a[i],inf);
					}
					while(bfs())
						while(j=dinic(s,inf)) maxflow+=j;
					ans=min(ans,maxflow);
				}
		if(n<=1||ans==inf) ans=n;
		cout<<ans<<endl;
	}
}