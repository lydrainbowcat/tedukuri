#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[210],n,m,t,i,j,k;
double p[210],f[205][205][405],ans;
int main()
{
	freopen("guard.in","r",stdin);
	freopen("guard.out","w",stdout); 
	cin>>n>>m>>t;
	for(i=1;i<=n;i++) scanf("%lf",&p[i]),p[i]/=100;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	if(t>n) t=n;
	f[0][0][t+200]=1;
	for(i=0;i<n;i++)
		for(j=0;j<=n;j++)
			for(k=-n;k<=n;k++)
			{
				if(a[i+1]==-1)
				{
					f[i+1][j][k+200]+=f[i][j][k+200]*(1-p[i+1]);
					f[i+1][j+1][k-1+200]+=f[i][j][k+200]*p[i+1];
				}
				else{
					f[i+1][j+1][min(k+a[i+1],n)+200]+=f[i][j][k+200]*p[i+1];
					f[i+1][j][k+200]+=f[i][j][k+200]*(1-p[i+1]);
				}
			}
	for(j=m;j<=n;j++)
		for(k=0;k<=n;k++)
			ans+=f[n][j][k+200];
	printf("%.6f\n",ans);
	fclose(stdin);
	fclose(stdout); 
	return 0;
}
