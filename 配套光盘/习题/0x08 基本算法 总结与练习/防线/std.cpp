#include<iostream>
#include<cstdio>
using namespace std;
int s[200010],e[200010],d[200010],t,n,i,now,ans;
unsigned int l,r,mid;

int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(i=1;i<=n;i++) scanf("%d%d%d",&s[i],&e[i],&d[i]);
		l=0,r=0x7fffffff;
		while(l<r)
		{
			mid=(l+r)>>1;
			for(now=0,i=1;i<=n;i++)
				if(mid>=s[i])
				{
					if(mid<e[i])
						now+=(mid-s[i])/d[i]+1;
					else now+=(e[i]-s[i])/d[i]+1;
				}
			if(now&1) r=mid; else l=mid+1;
		}
		for(ans=0,i=1;i<=n;i++)
			if(l>=s[i]&&l<=e[i]&&(l-s[i])%d[i]==0) ans++;
		if(ans&1) cout<<l<<' '<<ans<<endl; else puts("There's no weakness.");
	}
	return 0;
}