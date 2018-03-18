#include<iostream>
#include<cstdio>
using namespace std;
long long n,i,j,ans;
int main()
{
	while(cin>>n)
	{
		ans=n;
		for(i=2;i*i<=n;i++)
			if(n%i==0)
			{
				j=0;
				while(n%i==0) n/=i,j++;
				ans/=i;
				ans*=i*j+i-j;
			}
		if(n>1) ans/=n,ans*=n+n-1;
		cout<<ans<<endl;
	}
	return 0;
}