// Author: AKCqhzdy
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;

int n,cnt,a[30],c[30];bool bk,v[30];
char ss[3][30];
bool check(int k)
{
	for(int i=k-1;i>=1;i--)
	{
		if(a[ss[0][i]-'A'+1]!=-1&&a[ss[1][i]-'A'+1]!=-1)
		{
			int d=a[ss[0][i]-'A'+1]+a[ss[1][i]-'A'+1];
			if(a[ss[2][i]-'A'+1]!=-1)
			{
				int dd=a[ss[2][i]-'A'+1];
				if(dd==d%n||dd==(d+1)%n)continue;
				return false;
			}
		}
	}
	return true;
}
void dfs(int k,int w)
{
	if(bk==true)return ;
	if(cnt==n||(k==0&&c[k]==0))
	{
		bk=true;
		for(int i=1;i<n;i++)printf("%d ",a[i]);
		printf("%d\n",a[n]);
		return ;
	}
	if(w==2)
	{
		int x=ss[w][k]-'A'+1;
		int d=a[ss[0][k]-'A'+1]+a[ss[1][k]-'A'+1]+c[k];
		
		if(a[x]==-1)
		{
			if(v[d%n]==true)return ;
			
			a[x]=d%n;c[k-1]=d/n;v[d%n]=true;cnt++;
			if(check(k))dfs(k-1,0);
			a[x]=-1;c[k-1]=0;v[d%n]=false;cnt--;
		}
		else if(a[x]==d%n)
		{
			c[k-1]=d/n;
			dfs(k-1,0);
			c[k-1]=0;
		}
	}
	else
	{
		int x=ss[w][k]-'A'+1;
		if(a[x]==-1)
		{
			for(int i=0;i<n;i++)
			{
				if(v[i]==false)
				{
					a[x]=i;v[i]=true;cnt++;
					if(check(k))dfs(k,w+1);
					a[x]=-1;v[i]=false;cnt--;
				}
			}
		}
		else dfs(k,w+1);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<3;i++)scanf("%s",ss[i]+1);
	memset(a,-1,sizeof(a));
	memset(c,0,sizeof(c));
	memset(v,false,sizeof(v));
	bk=false;cnt=0;dfs(n,0);
	return 0;
}