#include<iostream>
#include<cstdio>
using namespace std;
long long a[500010],f[500010],s[500010],h[500010];
int q[500010];
int t,n,m,i,j,l,r;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(i=1;i<=n;i++) scanf("%d",&a[i]);
		for(i=1;i<=n;i++) s[i]=s[i-1]+a[i];
		l=1; r=0;
		for(i=1;i<=n;i++)
		{
			h[i-1]=f[i-1]-s[i-1]+(i-1)*a[i];
			if(i>=2*m)
			{
				j=i-m;
				while(l<r&&(h[j]-h[q[r]])*(a[q[r]+1]-a[q[r-1]+1])<=(h[q[r]]-h[q[r-1]])*(a[j+1]-a[q[r]+1])) r--;
				q[++r]=j;
				while(l<r&&h[q[l+1]]-h[q[l]]<=i*(a[q[l+1]+1]-a[q[l]+1])) l++;
				f[i]=f[q[l]]+s[i]-s[q[l]]-a[q[l]+1]*(i-q[l]);
			}
			else f[i]=f[i-1]+a[i]-a[1];
		}
		
		cout<<f[n]<<endl;
	}
	return 0;
}