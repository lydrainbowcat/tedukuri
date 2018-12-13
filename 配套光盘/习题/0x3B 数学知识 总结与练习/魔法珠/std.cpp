#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110],f[1010],v[10000],n,i,num,ans;

int SG(int x)
{
	if(f[x]!=-1) return f[x];
	int now=++num,p=0,i;
	for(i=1;i*i<=x;i++)
		if(x%i==0)
		{
			if(i<x) p^=SG(i);
			if(i*i!=x&&i>1&&i<x) p^=SG(x/i);
		}
	for(i=1;i*i<=x;i++)
		if(x%i==0)
		{
			if(i<x) v[p^f[i]]=now;
			if(i*i!=x&&i>1&&i<x) v[p^f[x/i]]=now;
		}
	for(i=0;v[i]==now;i++);
	return f[x]=i;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(cin>>n)
	{
		memset(f,-1,sizeof(f)),ans=0;
		for(i=1;i<=n;i++) cin>>a[i],ans^=SG(a[i]);
		if(ans) cout<<"freda\n"; else cout<<"rainbow\n";
	}
	return 0;
}
