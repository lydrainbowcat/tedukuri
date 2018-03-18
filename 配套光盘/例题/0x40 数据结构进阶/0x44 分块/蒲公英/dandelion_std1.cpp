#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int u=40010;
int c[40][40][u],f[40][40],d[40][40],a[u],b[u],fa[u],fb[u],st[40],ed[40];
int n,m,t,l,tot,i,j,k,x,y,ans,L,R,cnt,num;

void prework()
{
	t=(int)pow(n*1.0,1.0/3);
	if(t) l=n/t;
	for(i=1;i<=t;i++) st[i]=(i-1)*l+1,ed[i]=i*l;
	if(ed[t]<n) st[t+1]=ed[t]+1,ed[++t]=n;
	memcpy(fa,a,sizeof(a));
	sort(fa+1,fa+n+1);
	for(i=1;i<=n;i++)
		if(i==1||fa[i]!=fa[i-1]) fb[++tot]=fa[i];
	for(i=1;i<=n;i++) b[i]=lower_bound(fb+1,fb+tot+1,a[i])-fb;
	for(i=1;i<=t;i++)
		for(j=i;j<=t;j++)
		{
			for(k=st[i];k<=ed[j];k++) c[i][j][b[k]]++;
			for(k=1;k<=tot;k++)
				if(c[i][j][k]>f[i][j]||c[i][j][k]==f[i][j]&&k<d[i][j])
					f[i][j]=c[i][j][k],d[i][j]=k;
		}
}

inline void update(int i)
{
	c[L][R][b[i]]++;
	if(c[L][R][b[i]]>cnt||c[L][R][b[i]]==cnt&&b[i]<num) cnt=c[L][R][b[i]],num=b[i];
}

int solve(int x,int y)
{
	int i,l,r;
	if(x>y) swap(x,y);
	for(i=1;i<=t;i++) if(x<=ed[i]) {l=i; break;}
	for(i=t;i;i--) if(y>=st[i]) {r=i; break;}
	if(l+1<=r-1) L=l+1,R=r-1; else L=R=0;
	cnt=f[L][R],num=d[L][R];
	if(l==r)
	{
		for(i=x;i<=y;i++) update(i);
		for(i=x;i<=y;i++) c[L][R][b[i]]--;
	}
	else{
		for(i=x;i<=ed[l];i++) update(i);
		for(i=st[r];i<=y;i++) update(i);
		for(i=x;i<=ed[l];i++) c[L][R][b[i]]--;
		for(i=st[r];i<=y;i++) c[L][R][b[i]]--;
	}
	return fb[num];
}

int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	prework();
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		ans=solve((x+ans-1)%n+1,(y+ans-1)%n+1);
		printf("%d\n",ans);
	}
	return 0;
}
