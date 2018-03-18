#include<iostream>
#include<cstdio>
using namespace std;
int ap[2010],bp[2010],as[2010],bs[2010],q[2010],f[2010][2010],n,m,w,i,j,l,r,p;
int main()
{
	cin>>n>>m>>w;
	for(i=1;i<=n;i++) scanf("%d%d%d%d",&ap[i],&bp[i],&as[i],&bs[i]);
	for(i=0;i<=n;i++)
		for(j=0;j<=m;j++) f[i][j]=-0x3fffffff;
	f[0][0]=0;
	for(i=1;i<=n;i++)
	{
		p=max(i-w-1,0);
		for(j=0;j<=m;j++) f[i][j]=f[i-1][j];
		q[l=r=1]=0;
		for(j=1;j<=m;j++)
		{
			while(l<=r&&q[l]<j-as[i]) l++;
			f[i][j]=max(f[i][j],f[p][q[l]]-(j-q[l])*ap[i]);
			while(l<=r&&f[p][q[r]]+q[r]*ap[i]<f[p][j]+j*ap[i]) r--;
			q[++r]=j;
		}
		q[l=r=1]=m;
		for(j=m-1;j>=0;j--)
		{
			while(l<=r&&q[l]>j+bs[i]) l++;
			f[i][j]=max(f[i][j],f[p][q[l]]+(q[l]-j)*bp[i]);
			while(l<=r&&f[p][q[r]]+q[r]*bp[i]<f[p][j]+j*bp[i]) r--;
			q[++r]=j;
		}
	}
	cout<<f[n][0]<<endl;
	return 0;
}