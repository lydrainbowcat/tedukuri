#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int f[100010],d[100010],a[110],c[110],n,m,x,y,ans;
int main()
{
	while(cin>>n>>m&&n!=0)
	{
		for(int i=1;i<=m;i++) f[i]=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>c[i];
		f[0]=1;
		for(int i=1;i<=n;i++)
		{
			x=a[i],y=c[i];
			for(int j=0;j<=m;j++) d[j]=0;
			for(int j=0;j<=m-x;j++)
				if(f[j]==1&&d[j]<y&&f[j+x]==0)
					f[j+x]=1,d[j+x]=d[j]+1;
		}
		ans=0;
		for(int i=1;i<=m;i++)
			if(f[i]==1) ans++;
		cout<<ans<<endl;
	}
}