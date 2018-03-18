#include<stdio.h>
int n,m,zc,ss,u;
int a[100020];
int s[1000020];
char z[1000020];
int main()
{
	freopen("taiko.in","r",stdin);
	freopen("taiko.out","w",stdout);
	for(;~scanf("%d",&n);)
	{
		m=1<<n-1;
		for(int i=0;i<m;i++)
			a[i]=0;
		s[ss++]=ss=0;
		zc=n+m*2;
		for(;ss;)
		{
			u=s[--ss];
			z[--zc]=u%2+'0';
			u/=2;
			for(int w;a[u]<2;)
			{
				w=2*u+a[u]++;
				s[ss++]=w;
				u=w%m;
			}
		}
		for(;zc;)
			z[--zc]='0';
		z[m*2]=0;
		printf("%d %s\n",1<<n,z);
	}
}
