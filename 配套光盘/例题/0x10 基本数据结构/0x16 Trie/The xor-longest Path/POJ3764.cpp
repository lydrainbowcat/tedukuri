#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int u=100010;
int ver[2*u],edge[2*u],next[2*u],head[u],v[u],val[u*32],a[u*32][2],f[u];
int n,tot,i,ans,x,y,z;

void add(int x,int y,int z)
{
	ver[++tot]=y; edge[tot]=z; next[tot]=head[x]; head[x]=tot;
}

void dfs(int x)
{
	v[x]=1;
	for(int i=head[x];i;i=next[i])
		if(!v[ver[i]])
		{
			f[ver[i]]=f[x]^edge[i];
			dfs(ver[i]);
		}
}

void ins(int x,int y,int temp)
{
	if(y<0) {val[x]=temp; return;}
	int z=(temp>>y)&1;
	if(!a[x][z]) a[x][z]=++tot;
	ins(a[x][z],y-1,temp);
} 

int get(int x,int y,int temp)
{
	if(y<0) return val[x];
	int z=(temp>>y)&1;
	if(a[x][z^1]) return get(a[x][z^1],y-1,temp);
	else return get(a[x][z],y-1,temp);
}

int main()
{
	while(cin>>n)
	{
		memset(head,0,sizeof(head));
		memset(f,0,sizeof(f));
		memset(v,0,sizeof(v));
		tot=0;
		for(i=1;i<n;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			x++,y++;
			add(x,y,z); add(y,x,z);
		}
		dfs(1); tot=1; ans=0;
		memset(a,0,sizeof(a));
		ins(1,30,0);
		for(i=1;i<=n;i++)
		{
			ans=max(ans,f[i]^get(1,30,f[i]));
			ins(1,30,f[i]);
		}
		cout<<ans<<endl;
	}
	return 0;
}