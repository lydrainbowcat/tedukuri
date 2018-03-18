/*
    Author: wccy
    本程序仅供参考
*/
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,kk;
struct M
{int a[35][35];}f[35],ans;
inline M operator + (const M &x,const M &y)
{
	M res;
	memset(res.a,0,sizeof res.a);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			res.a[i][j]=(x.a[i][j]+y.a[i][j])%m;
	return res;
}
inline M operator * (const M &x,const M &y)
{
	M res;
	memset(res.a,0,sizeof res.a);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				res.a[i][j]=(res.a[i][j]+x.a[i][k]*y.a[k][j]%m)%m;
	return res;
}
inline void init(int x)
{
	int cnt=1;
	for(int i=0;cnt<=x;i++,cnt<<=1)
		f[i+1]=f[i]*f[i];
}
inline M calc(int x)
{
	M res;
	memset(res.a,0,sizeof res.a);
	for(int i=1;i<=n;i++)
		res.a[i][i]=1;
	int cnt=0;
	while(x)
	{
		if(x&1) res=res*f[cnt];
		x>>=1;
		cnt++;
	}
	return res;
}
inline M solve(int x)
{
	if(x==1) return f[0];
	M p=solve(x>>1);
	p=p+p*calc(x>>1);
	if(x&1) p=p+calc(x);
	return p;
}
inline void print(const M &ans)
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d ",ans.a[i][j]);
		printf("\n");
	}
}
int main()
{
	scanf("%d%d%d",&n,&kk,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&f[0].a[i][j]);
	init(kk);

	print(solve(kk));
	return 0;
}