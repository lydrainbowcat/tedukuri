#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int a[110],b[110],c[110],d[110],link[110],ans[110],va[110],vb[110],n,i,j,k;
double la[110],lb[110],f[110][110],temp;

bool km(int x)
{
	va[x]=1;
	for(int i=1;i<=n;i++)
		if(!vb[i]&&fabs(la[x]+lb[i]-f[x][i])<1e-10)
		{
			vb[i]=1;
			if(!link[i]||km(link[i])) {link[i]=x; return 1;}
		}
	return 0;
}

int main()
{
	cin>>n;
	for(i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	for(i=1;i<=n;i++) scanf("%d%d",&c[i],&d[i]);
	for(i=1;i<=n;i++) la[i]=-1e12;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
			f[i][j]=-sqrt((a[i]-c[j])*(a[i]-c[j])*1.0+(b[i]-d[j])*(b[i]-d[j])*1.0);
			la[i]=max(la[i],f[i][j]);
		}
	for(i=1;i<=n;i++)
		while(1)
		{
			memset(va,0,sizeof(va));
			memset(vb,0,sizeof(vb));
			if(km(i)) break;
			temp=1e12;
			for(j=1;j<=n;j++)
				if(va[j])
					for(k=1;k<=n;k++)
						if(!vb[k]) temp=min(temp,la[j]+lb[k]-f[j][k]);
			for(j=1;j<=n;j++)
			{
				if(va[j]) la[j]-=temp;
				if(vb[j]) lb[j]+=temp;
			}
		}
	for(i=1;i<=n;i++) ans[link[i]]=i;
	for(i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}