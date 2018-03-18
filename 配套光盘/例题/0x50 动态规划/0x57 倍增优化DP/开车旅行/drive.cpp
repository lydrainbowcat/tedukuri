#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cmath>
#include<cstdlib>
using namespace std;
const int u=100010;
long long a[u][18][2],b[u][18][2],ansA,ansB,A,B;
int f[u][18][2],ans,n,m,t,i,j,k,h[u],g[u],go[u][2],x0,l,x,y;
struct rec{int x,y;};
set<rec> s;
set<rec>::iterator it,lt,rt;

bool operator <(rec a,rec b)
{
	return a.y<b.y;
}
bool cmp(int a,int b)
{
	return abs(h[a]-h[i])<abs(h[b]-h[i])||abs(h[a]-h[i])==abs(h[b]-h[i])&&h[a]<h[b];
}

void solve(int s,int x0,long long &A,long long &B)
{
	A=B=k=0;
	for(int i=t;i>=0;i--)
	  if(f[s][i][k]&&a[s][i][k]+b[s][i][k]<=x0)
	  {
			x0-=a[s][i][k]+b[s][i][k];
			A+=a[s][i][k],B+=b[s][i][k];
			if(i==0) k^=1;
			s=f[s][i][k];
		}
}

int main()
{
	cin>>n;
	for(i=1;i<=n;i++) scanf("%d",&h[i]);
	for(i=n;i;i--)
	{
		rec New; New.x=i,New.y=h[i];
		s.insert(New);
		it=s.find(New);
		lt=it,rt=it,m=0;
		if(lt!=s.begin()) lt--,g[++m]=lt->x;
		if(lt!=s.begin()) lt--,g[++m]=lt->x;
		if(rt++,rt!=s.end())
		{
			g[++m]=rt->x;
			if(rt++,rt!=s.end()) g[++m]=rt->x;
		}
		sort(g+1,g+m+1,cmp);
		if(m) go[i][0]=g[1];
		if(m>1) go[i][1]=g[2];
	}
	for(i=1;i<=n;i++)
	{
		if(go[i][1]) f[i][0][0]=go[i][1],a[i][0][0]=abs(h[go[i][1]]-h[i]),b[i][0][0]=0;
		if(go[i][0]) f[i][0][1]=go[i][0],a[i][0][1]=0,b[i][0][1]=abs(h[go[i][0]]-h[i]);
	}
	t=(int)(log(n*1.0)/log(2.0)+0.001);
	for(i=1;i<=t;i++)
	  for(j=1;j<=n;j++)
	    for(k=0;k<=1;k++)
			{
				if(i==1) l=k^1; else l=k;
				if(f[j][i-1][k]) f[j][i][k]=f[f[j][i-1][k]][i-1][l];
				if(f[j][i][k])
				{
					a[j][i][k]=a[j][i-1][k]+a[f[j][i-1][k]][i-1][l];
					b[j][i][k]=b[j][i-1][k]+b[f[j][i-1][k]][i-1][l];
				}
			}
	cin>>x0;
	ansA=1,ansB=0;
	for(i=1;i<=n;i++)
	{
		solve(i,x0,A,B);
		if(!B) A=1;
		if(A*ansB<ansA*B||A*ansB==ansA*B&&h[i]>h[ans]) ansA=A,ansB=B,ans=i;
	}
	cout<<ans<<endl;
	cin>>m;
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		solve(x,y,A,B);
		printf("%lld %lld\n",A,B);
	}
	return 0;
}