/*
    Author: wccy
    本程序仅供参考
*/
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
int r,c,t;
char s[10010][80];
int next[10010],len;
inline bool cmp(const int &x,const int &y)
{
	for(int i=1;i<=t;i++)
		if(s[x][i]!=s[y][i])
			return false;
	return true;
}
int main()
{
	scanf("%d%d",&r,&c);
	for(int i=1;i<=r;i++)
		scanf("%s",s[i]+1);
	for(t=1;t<=c;t++)
	{
		bool flag=true;
		for(int i=1;i<=r;i++)
		{
			for(int j=t+1,k=1;j<=c;j++,k++)
			{
				if(s[i][j]!=s[i][k])
				{
					flag=false;
					break;
				}
				if(k==t) k=0;
			}
			if(!flag) break;
		}
		if(flag) break;
	}
	next[1]=0;
	len=0;
	for(int i=2;i<=r;i++)
	{
		while(len>0&&!cmp(i,len+1)) len=next[len];
		if(cmp(i,len+1)) len++;
		next[i]=len;
	}
	printf("%d\n",t*(r-next[r]));
	return 0;
}