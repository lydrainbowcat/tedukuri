// Author: Rose_max
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
const int ptm[11][11]={
{0,0,0,0,0,0,0,0,0,0},
{0,6,6,6,6,6,6,6,6,6},
{0,6,7,7,7,7,7,7,7,6},
{0,6,7,8,8,8,8,8,7,6},
{0,6,7,8,9,9,9,8,7,6},
{0,6,7,8,9,10,9,8,7,6},
{0,6,7,8,9,9,9,8,7,6},
{0,6,7,8,8,8,8,8,7,6},
{0,6,7,7,7,7,7,7,7,6},
{0,6,6,6,6,6,6,6,6,6}
};
int bin[25],sum,ans;
int mp[15][15];
int row[15],col[15],po[15];
int G(int x,int y){return (x-1)/3*3+(y-1)/3+1;}
void dfs(int k,int pt)
{
	if(k==sum+1)
	{
		ans=max(ans,pt);
		return ;
	}
	int u,v,s=999999999,gu;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			if(!mp[i][j])
			{
				int tmp=row[i]&col[j]&po[G(i,j)],ret=0;
				if(tmp==0)return ;
				for(int k=1;k<=9;k++)if(tmp&bin[k])ret++;
				if(ret<s)u=i,v=j,s=ret,gu=tmp;
			}
	if(ptm[u][v]<=7)
	{
		for(int i=1;i<=9;i++)
			if(gu&bin[i])
			{
				mp[u][v]=i;row[u]^=bin[i];col[v]^=bin[i];po[G(u,v)]^=bin[i];
				dfs(k+1,pt+i*ptm[u][v]);
				mp[u][v]=0;row[u]|=bin[i];col[v]|=bin[i];po[G(u,v)]|=bin[i];
			}
	}
	else
	{
		for(int i=9;i>=1;i--)
			if(gu&bin[i])
			{
				mp[u][v]=i;row[u]^=bin[i];col[v]^=bin[i];po[G(u,v)]^=bin[i];
				dfs(k+1,pt+i*ptm[u][v]);
				mp[u][v]=0;row[u]|=bin[i];col[v]|=bin[i];po[G(u,v)]|=bin[i];
			}
	}
}
int main()
{
	bin[1]=1;for(int i=2;i<=20;i++)bin[i]=bin[i-1]<<1;
	for(int i=1;i<=9;i++)for(int j=1;j<=9;j++)scanf("%d",&mp[i][j]);
	for(int i=1;i<=9;i++)row[i]=col[i]=po[i]=(1<<9)-1;
	bool bk=false;int p=0;
	for(int i=1;i<=9;i++)for(int j=1;j<=9;j++)
	{
		if(mp[i][j])
		{
			if(row[i]&bin[mp[i][j]])row[i]^=bin[mp[i][j]];
			else {bk=true;break;}
			if(col[j]&bin[mp[i][j]])col[j]^=bin[mp[i][j]];
			else {bk=true;break;}
			int tmp=G(i,j);
			if(po[tmp]&bin[mp[i][j]])po[tmp]^=bin[mp[i][j]];
			else {bk=true;break;}
			p+=mp[i][j]*ptm[i][j];
		}
		else sum++;
	}
	if(bk){printf("-1\n");return 0;}
	ans=-1;
	dfs(1,0);
	if(ans==-1)printf("-1\n");
	else printf("%d\n",ans+p);
	return 0;
}