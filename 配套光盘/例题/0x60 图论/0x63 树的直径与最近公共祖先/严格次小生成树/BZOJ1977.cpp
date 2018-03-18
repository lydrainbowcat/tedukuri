#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int u=100010,w=600010;
struct rec{int x,y,z;}a[w];
struct sol{int fa,a,b;}f[u][20],temp;
int ver[w],edge[w],next[w],head[u],d[u],fa[u],out[w],v[u];
int n,m,tot,t,i,ans,x,y,z;
long long mst;
queue<int> q;

bool cmp(rec a,rec b) {return a.z<b.z;}
void add(int x,int y,int z)
{
	ver[++tot]=y; edge[tot]=z; next[tot]=head[x]; head[x]=tot;
}

int get(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}
void kruskal()
{
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x=get(a[i].x),y=get(a[i].y),z=a[i].z;
		if(x!=y)
		{
			mst+=z,fa[y]=x;
			add(a[i].x,a[i].y,z),add(a[i].y,a[i].x,z);
		}
		else out[i]=1;
	}
}

inline sol ini(int x,int y,int z)
{
	sol f;
	f.fa=x,f.a=y,f.b=z;
	return f;
}
inline void calc(sol &f,int x)
{
	if(x>f.a) f.b=f.a,f.a=x;
	if(x>f.b&&x<f.a) f.b=x;
}
inline sol update(sol a,sol b)
{
	sol f=b;
	calc(f,a.a),calc(f,a.b);
	return f;
}

void bfs()
{
	int i,j,x,y,z;
	for(i=1;i<=n;i++)
		for(j=0;j<=t;j++) f[i][j]=ini(-1,-1,-1);
	q.push(1); v[1]=1;
	while(q.size())
	{
		x=q.front(); q.pop();
		for(i=head[x];i;i=next[i])
			if(!v[y=ver[i]])
			{
				q.push(y); v[y]=1;
				d[y]=d[x]+1;
				f[y][0]=ini(x,edge[i],-1);
				for(j=1;j<=t;j++)
				{
					z=f[y][j-1].fa;
					if(z==-1) break;
					f[y][j]=update(f[y][j-1],f[z][j-1]);
				}
			}
	}
}

sol ask(int x,int y)
{
	sol temp=ini(-1,-1,-1);
	int i;
	if(d[x]<d[y]) swap(x,y);
	for(i=t;i>=0;i--)
		if(d[x]-(1<<i)>=d[y])
		{
			temp=update(temp,f[x][i]);
			x=f[x][i].fa;
		}
	if(x==y) return temp;
	for(i=t;i>=0;i--)
		if(f[x][i].fa!=f[y][i].fa)
		{
			temp=update(temp,f[x][i]);
			temp=update(temp,f[y][i]);
			x=f[x][i].fa,y=f[y][i].fa;
		}
	temp=update(temp,f[x][0]);
	temp=update(temp,f[y][0]);
	return temp;
}

int main()
{
	cin>>n>>m;
	t=(int)(log(n)/log(2));
	for(i=1;i<=m;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	sort(a+1,a+m+1,cmp);
	kruskal();
	bfs();
	ans=0x7fffffff;
	for(i=1;i<=m;i++)
		if(out[i])
		{
			temp=ask(a[i].x,a[i].y);
			if(a[i].z==temp.a&&temp.b!=-1) ans=min(ans,a[i].z-temp.b);
			if(a[i].z>temp.a) ans=min(ans,a[i].z-temp.a);
		}
	cout<<mst+ans<<endl;
	return 0;
}
