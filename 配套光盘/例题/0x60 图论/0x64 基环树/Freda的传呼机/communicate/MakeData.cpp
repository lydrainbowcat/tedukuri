#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<vector>
#include<queue> 
using namespace std;
const int u=10010,w=80010;
struct rec{
	int x,y;
	rec(int p,int q):x(p),y(q){}
};
int ver[w],edge[w],next[w],head[u],fa[u],a[u],len[u],d[u],f[u][16],dis[u],dist[u],v[u],g[u],del[w];
vector<int> c[u];
int n,m,tot,t,cnt,i,j,x,y,z,num,now;

char s[100],in[100],out[100];
int T,Data[11]={0,10,100,1000,5000,5000,10000,50000,100000,200000,200000};
 
void file()
{
	memset(s,0,sizeof(s));
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	strcat(s,"communicate");
	sprintf(s+strlen(s),"%d.",T);
	strcat(in,s),strcat(in,"in");
	strcat(out,s),strcat(out,"out");
}

int get(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]); 
} 

void random()
{
	int n=10000,m=n,q=10000;
	cout<<n<<' '<<m-(T<=8)<<' '<<q<<endl;
	for(i=1;i<=n;i++) fa[i]=i; 
	for(i=1;i<m;i++)
	{
		do{x=rand()%n+1; y=rand()%n+1;}while(get(x)==get(y));
		printf("%d %d %d\n",x,y,rand()%32767+1);
		fa[get(y)]=get(x); 
	}
	do{x=rand()%n+1; y=rand()%n+1;}while(x==y);
	if(T>8) printf("%d %d %d\n",x,y,rand()%32767+1);
	for(i=1;i<=q;i++) printf("%d %d\n",rand()%n+1,rand()%n+1); 
}

void add(int x,int y,int z)
{
	ver[++tot]=y,edge[tot]=z,next[tot]=head[x],head[x]=tot;
}

void circle(int x,int e)
{
	int i,j,y=x; x=ver[e]; 
	len[++cnt]=edge[e],c[y].push_back(cnt),g[y]=cnt; 
	del[e]=del[e^1]=1,add(x,y,0),add(y,x,0);
	for(i=fa[y];(y=ver[i^1])!=x;i=fa[y])
	{ 
		c[y].push_back(cnt),len[cnt]+=edge[i],g[y]=cnt; 
		del[i]=del[i^1]=1,add(x,y,0),add(y,x,0); 
	}
	len[cnt]+=edge[i],c[x].push_back(cnt);
}

void dfs(int x)
{
	v[x]=++num;
	for(int i=head[x];i;i=next[i])
		if(i<=now)
			if(!v[ver[i]])
			{
				fa[ver[i]]=i;
				dis[ver[i]]=dis[x]+edge[i];
				dfs(ver[i]); 
			}
			else if(fa[x]!=(i^1)&&v[ver[i]]<v[x]) circle(x,i);
}

void bfs()
{
	queue<int> q; 
	memset(v,0,sizeof(v)); 
	q.push(1); v[1]=1; d[1]=1; 
	while(q.size())
	{
		x=q.front(); q.pop();
		for(i=head[x];i;i=next[i])
			if(!del[i]&&!v[y=ver[i]])
			{
				d[y]=d[x]+1; f[y][0]=x;
				for(j=1;j<15;j++) f[y][j]=f[f[y][j-1]][j-1];
				q.push(y); v[y]=1;
			}
	}
}

void spfa()
{
	memset(dist,0x3f,sizeof(dist));
	memset(v,0,sizeof(v)); 
	queue<int> q;
	q.push(1); dist[1]=0; v[1]=1;
	while(q.size())
	{
		x=q.front(); q.pop(); v[x]=0; 
		for(i=head[x];i;i=next[i])
			if(dist[ver[i]]>dist[x]+edge[i])
			{
				dist[ver[i]]=dist[x]+edge[i];
				if(!v[ver[i]]) q.push(ver[i]),v[ver[i]]=1; 
			} 
	}
} 

int lca(int x,int y)
{
	if(d[x]<d[y]) swap(x,y);
	int i,p=x,q=y;
	for(i=14;i>=0;i--)
		if(d[f[x][i]]>=d[y]) x=f[x][i];
	if(x==y) return dist[p]-dist[q];
	for(i=14;i>=0;i--)
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	if(g[x]&&g[x]==g[y])
	{
		i=abs(dis[y]-dis[x]); 
		return dist[p]-dist[x]+dist[q]-dist[y]+min(i,len[g[x]]-i);
	}
	else return dist[p]+dist[q]-2*dist[f[x][0]]; 
}

void stdf()
{
	memset(head,0,sizeof(head));
	memset(fa,0,sizeof(fa));
	memset(len,0,sizeof(len));
	memset(a,0,sizeof(a)); 
	memset(d,0,sizeof(d));
	memset(f,0,sizeof(f));
	memset(dis,0,sizeof(dis));
	memset(v,0,sizeof(v));
	memset(g,0,sizeof(g));
	memset(del,0,sizeof(del));
	for(i=0;i<u;i++) c[i].clear(); 
	tot=cnt=num=now=0; 
	cin>>n>>m>>t;
	for(tot=i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	spfa(); 
	now=tot;
	dfs(1);
	bfs();
	for(i=1;i<=t;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
	}
}

int main()
{
	srand((unsigned)time(0));
	for(T=3;T<=18;T++)
	{
		file();
		freopen(in,"w",stdout);
		random();
		fclose(stdout);
		freopen(in,"r",stdin);
		freopen(out,"w",stdout);
		stdf();
		fclose(stdin);
		fclose(stdout);
	}
	return 0;
}
