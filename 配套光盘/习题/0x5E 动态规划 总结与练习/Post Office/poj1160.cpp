#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
int s[310][310],f[310][40],n,m,a[310];
inline int dist(int x,int y)
{
	if(s[x][y])	return s[x][y];
	int px=x,py=y;
	for(;x<y;++x,--y){s[px][py]+=a[y]-a[x];}
	return s[px][py];
}	
int main()
{
	scanf("%d%d",&n,&m);
	memset(f,0x3f,sizeof f);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]),f[i][1]=dist(1,i);
	for(int i=2;i<=m;++i)
		for(int j=i;j<=n;++j)
			for(int k=i-1;k<j;++k)
				f[j][i]=min(f[j][i],f[k][i-1]+dist(k+1,j));
	printf("%d\n",f[n][m]);
	return 0;
}