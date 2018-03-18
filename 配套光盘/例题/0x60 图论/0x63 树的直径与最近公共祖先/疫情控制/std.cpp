#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int u=50010;
int ver[2*u],edge[2*u],next[2*u],head[u],a[u],b[u],g[u],v[u],fa[u][16],sh[u],on[u];
long long c[u],d[u],f[u],dis[u][16],l,r,mid,sum;
int n,m,t,tot,x,y,z,i;
vector<long long> arv[u];
queue<int> q;
void add(int ycat_l,int ycat_h,int ycat_v)
{
	ver[++tot]=ycat_h,edge[tot]=ycat_v,next[tot]=head[ycat_l],head[ycat_l]=tot;
}

void bfs()
{
	int i,j,x,y;
	v[1]=1;
	for(i=head[1];i;i=next[i])
	{
		q.push(ver[i]),v[ver[i]]=1;
		b[++t]=i,sh[ver[i]]=t;
	}
	while(q.size())
	{
		x=q.front(),q.pop();
		for(i=head[x];i;i=next[i])
		  if(!v[y=ver[i]])
		  {
				q.push(y),v[y]=1;
				fa[y][0]=x,dis[y][0]=edge[i];
				for(j=1;j<16;j++)
				  fa[y][j]=fa[fa[y][j-1]][j-1],dis[y][j]=dis[y][j-1]+dis[fa[y][j-1]][j-1];
			}
	}
}

bool dfs(int x)
{
	v[x]=1;
	if(!sh[x]&&on[x]) return 1;
	bool flag=0;
	for(int i=head[x];i;i=next[i])
	  if(!v[ver[i]])
		{
			flag=1;
			if(!dfs(ver[i])) return 0;
		}
	return flag;
}

bool solve(long long T)
{
	int p,q,i,j;
	for(i=1;i<=t;i++)
	  while(arv[i].size()) arv[i].pop_back();
	memset(v,0,sizeof(v));
	memset(on,0,sizeof(on));
	v[1]=1;
	for(i=1;i<=m;i++)
	{
	  for(g[i]=a[i],d[i]=0,j=15;j>=0;j--)
			if(fa[g[i]][j]&&d[i]+dis[g[i]][j]<=T) d[i]+=dis[g[i]][j],g[i]=fa[g[i]][j];
		on[g[i]]=1;
		if(j=sh[g[i]])
		{
			arv[j].push_back(T-d[i]);
			if(arv[j].size()>1&&T-d[i]>arv[j][arv[j].size()-2]) swap(arv[j][arv[j].size()-1],arv[j][arv[j].size()-2]);
		}
	}
	for(i=1,p=q=0;i<=t;i++)
	{
	  if(!dfs(ver[b[i]]))
			if(arv[i].size()&&arv[i][arv[i].size()-1]<edge[b[i]]*2) arv[i].pop_back(); else f[++q]=edge[b[i]];
	  for(j=0;j<arv[i].size();j++)
	    if(arv[i][j]>=edge[b[i]]) c[++p]=arv[i][j]-edge[b[i]];
	}
	sort(c+1,c+p+1);
	sort(f+1,f+q+1);
	if(p<q) return 0;
	for(i=q,j=p;i;i--,j--)
	  if(c[j]<f[i]) return 0;
	return 1;
}

int main()
{
	cin>>n;
	for(i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z),add(y,x,z),sum+=z;
	}
	cin>>m;
	for(i=1;i<=m;i++) scanf("%d",&a[i]);
	bfs();
	l=0,r=sum+1;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(solve(mid)) r=mid; else l=mid+1;
	}
	if(l>sum) l=-1;
	cout<<l<<endl;
	return 0;
}