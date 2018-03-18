#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef unsigned long long ull;
ull fa[1010][1010],fb[1010],ver[1000010],now,top,pc,ppc;
int a[1010][1010],head[1000010],next[1000010],n,m,q,tot,r,c,i,j,k;
char b[1010][1010];

void hash(ull now)
{
	int x=now%999983;
	ver[++tot]=now; next[tot]=head[x]; head[x]=tot;
}

bool ask(ull now)
{
	int x,i;
	x=now%999983;
	for(i=head[x];i;i=next[i])
		if(ver[i]==now) return 1;
	return 0;
}

int main()
{
	cin>>n>>m>>r>>c;
	for(i=1;i<=n;i++) scanf("%s",b[i]+1);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++) a[i][j]=b[i][j]-'0';
	cin>>q;
	if(r>n||c>m) {for(i=1;i<=q;i++) puts("0"); return 0;}
	for(pc=i=1;i<=c;i++) pc*=131;
	for(ppc=i=1;i<=r;i++) ppc*=pc;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=c;j++) fa[i][c]=fa[i][c]*131+a[i][j];
		for(j=c+1;j<=m;j++) fa[i][j]=fa[i][j-1]*131-a[i][j-c]*pc+a[i][j];
	}
	for(j=1;j<=m;j++)
		for(i=1;i<=r;i++) fb[j]=fb[j]*pc+a[i][j];
	for(j=1;j<=c;j++) top=top*131+fb[j];
	for(j=c;j<=m;j++)
	{
		now=top; hash(now);
		for(i=r+1;i<=n;i++) now=now*pc-fa[i-r][j]*ppc+fa[i][j],hash(now);
		top=top*131-fb[j+1-c]*pc+fb[j+1];
	}
	for(k=1;k<=q;k++)
	{
		for(i=1;i<=r;i++) scanf("%s",b[i]+1);
		now=0;
		for(i=1;i<=r;i++)
			for(j=1;j<=c;j++) now=now*131+b[i][j]-'0';
		if(ask(now)) puts("1"); else puts("0");
	}
	return 0;
}