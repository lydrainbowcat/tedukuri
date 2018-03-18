#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long a[1000010],f[1000010],sum,ans;
int n,i;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	sum/=n;
	for(i=1;i<=n;i++) a[i]-=sum;
	for(i=1;i<=n;i++) f[i]=f[i-1]+a[i];
	sort(f+1,f+n+1);
	for(i=1;i<=n;i++) ans+=abs(f[i]-f[(n+1)/2]);
	cout<<ans<<endl;
	return 0;
}