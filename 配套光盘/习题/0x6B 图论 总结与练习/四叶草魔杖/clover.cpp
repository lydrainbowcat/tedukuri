#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[20],d[20][20],g[20],b[65536],c[20],f[65536],v[20],s[65536],n,m,i,j,k,l,x,y,z,t,p,q;

int prim()
{
	memset(v,0,sizeof(v));
	memset(g,0x3f,sizeof(g));
	g[c[1]]=0;
	int i,j,temp,k,ans=0;
	for(i=1;i<=m;i++)
	{
		temp=0x3fffffff;
		for(j=1;j<=m;j++)
			if(!v[c[j]]&&g[c[j]]<temp) temp=g[c[j]],k=c[j];
		if(temp==0x3f3f3f3f) return -1;
		ans+=temp;
		v[k]=1;
		for(j=1;j<=m;j++)
			if(!v[c[j]]&&g[c[j]]>d[k][c[j]]) g[c[j]]=d[k][c[j]];
	}
	return ans;
}

int main()
{
	freopen("clover.in","r",stdin);
	freopen("clover.out","w",stdout); 
	while(cin>>n>>m)
	{
		for(i=1;i<=n;i++) scanf("%d",&a[i]);
		memset(d,0x3f,sizeof(d));
		for(i=1;i<=n;i++) d[i][i]=0;
		for(i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z),x++,y++;
			d[x][y]=d[y][x]=z;
		}
		for(k=1;k<=n;k++)
			for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
		memset(f,0x3f,sizeof(f));
		f[0]=0; t=(1<<n)-1;
		for(i=1;i<=n;i++)
			if(!a[i]) t^=1<<i-1;
		for(p=i=0;i<1<<n;i++)
		{
			for(j=0;j<n;j++)
				if((i>>j&1)&&!a[j+1]) break;
			if(j<n) continue;
			b[i]=0;
			for(m=j=0;j<n;j++)
				if(i>>j&1) b[i]+=a[j+1],c[++m]=j+1;
			if(b[i]) continue;
			b[i]=prim();
			s[++p]=i;
		}
		for(q=2;q<=p;q++)
		{
			i=s[q];
			k=b[i];
			if(k==-1) continue;
			for(l=1;l<=p;l++)
			{
				j=s[l];
				if(!(i&j)) f[i|j]=min(f[i|j],f[j]+k);
			}
		}
		if(f[t]==0x3f3f3f3f) puts("Impossible");
		else cout<<f[t]<<endl;
	}
	return 0;
}
