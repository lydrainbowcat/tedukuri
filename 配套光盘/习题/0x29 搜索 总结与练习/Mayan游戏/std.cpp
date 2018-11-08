// Author: AKCqhzdy
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;

int n,cnt,len[10],a[10][10];bool bk;
struct ansnode{int x,y,z;}as[10];

bool del[10][10];
void change(int x,int y,int z)
{
	if(len[x+z]>=y)swap(a[x+z][y],a[x][y]);
	else 
	{
		a[x+z][++len[x+z]]=a[x][y];
		for(int i=y;i<=len[x];i++)swap(a[x][i],a[x][i+1]);
		a[x][len[x]]=0;len[x]--;
	}
	memset(del,false,sizeof(del));
	bool qwq=true;
	while(qwq)
	{
		qwq=false;
		for(int i=1;i<=5;i++)
			for(int j=1;j<=len[i];j++)
			{
				if(i<=3)
				{
					if(a[i][j]==a[i+1][j]&&a[i+1][j]==a[i+2][j])
					{
						del[i][j]=true, del[i+1][j]=true, del[i+2][j]=true;
						qwq=true;
					}
				}
				if(len[i]-j>=2)
				{
					if(a[i][j]==a[i][j+1]&&a[i][j+1]==a[i][j+2])
					{
						del[i][j]=true, del[i][j+1]=true, del[i][j+2]=true;
						qwq=true;
					}
				}
			}
		for(int i=1;i<=5;i++)
		{
			int tp=0;
			for(int j=1;j<=len[i];j++)
				if(del[i][j]==false)a[i][++tp]=a[i][j];
				else cnt--;
			for(int j=tp+1;j<=len[i];j++)a[i][j]=0;
			len[i]=tp;
		}
		memset(del,false,sizeof(del));
	}
}
map<int,bool>mp;
bool myhash(int k)
{
	int d=k;
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=len[i];j++)d=d*11+a[i][j];
		d=d*11;
	}
	if(mp[d]==true)return true;
	else {mp[d]=true;return false;}
}
void dfs(int k)
{
	if(bk==true)return ;
	if(cnt==0&&k==n+1)
	{
		for(int i=1;i<=n;i++)printf("%d %d %d\n",as[i].x-1,as[i].y-1,as[i].z);
		bk=true;return ;
	}
	if(cnt==0||k==n+1)return ;
	
	int tlen[10],t[10][10],tcnt;
	tcnt=cnt;
	memcpy(tlen,len,sizeof(tlen));
	memcpy(t,a,sizeof(t));
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=len[i];j++)
		{
			if(i!=5)
			{
				change(i,j,1);
				as[k].x=i, as[k].y=j, as[k].z=1;
				if(!myhash(k))
					dfs(k+1);
				as[k].x=0, as[k].y=0, as[k].z=0;
				
				cnt=tcnt;
				memcpy(len,tlen,sizeof(len));
				memcpy(a,t,sizeof(a));
			}
			if(i!=1)
			{
				change(i,j,-1);
				as[k].x=i, as[k].y=j, as[k].z=-1;
				if(!myhash(k))
					dfs(k+1);
				as[k].x=0, as[k].y=0, as[k].z=0;
				
				cnt=tcnt;
				memcpy(len,tlen,sizeof(len));
				memcpy(a,t,sizeof(a));
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	memset(len,0,sizeof(len));
	for(int i=1;i<=5;i++)
	{
		while(scanf("%d",&a[i][++len[i]])!=EOF){if(a[i][len[i]]==0)break;}
		len[i]--;cnt+=len[i];
	}
	bk=false;dfs(1);
	if(bk==false)printf("-1\n");
	return 0;
}