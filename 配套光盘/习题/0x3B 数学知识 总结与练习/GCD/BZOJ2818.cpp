#include<iostream>
using namespace std;
int p[10000010],f[10000010];
int n,i,j,m;
long long ans;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++) p[i]=i;
	for(i=2;i<=n;i++)
		if(p[i]==i)
		{
			for(j=i;j<=n;j+=i) p[j]=p[j]/i*(i-1);
			m++; f[i]=f[i-1]+1;
		}
		else f[i]=f[i-1];
	for(i=2;i<=n;i++) ans+=p[i]*f[n/i];
	ans=ans*2+f[n];
	cout<<ans<<endl;
	return 0;
}