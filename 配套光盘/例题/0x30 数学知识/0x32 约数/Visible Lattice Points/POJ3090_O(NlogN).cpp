#include<cstdio>
int f[1010],n,t,i,j;
int main()
{
	n=1000;
	for(i=1;i<=n;i++) f[i]=i;
	for(i=2;i<=n;i++)
		if(f[i]==i)
			for(j=i;j<=n;j+=i)
				f[j]=f[j]/i*(i-1);
	f[1]=0;
	for(i=2;i<=n;i++) f[i]+=f[i-1];
	scanf("%d",&t);
	for(i=1;i<=t;i++)
	{
		scanf("%d",&n);
		printf("%d %d %d\n",i,n,f[n]*2+3);
	}
	return 0;
}