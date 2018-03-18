#include<iostream>
#include<cstdio>
using namespace std;
int a[100010],d[100010],s[100010],f[100010],q[100010],n,i,j,l,r;
int main()
{
	cin>>n;
	for(i=n;i;i--) scanf("%d",&a[i]);
	for(i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	l=1;
	for(i=1,j=0;i<=n;i++)
	{
		while(l<=r&&s[i]-s[q[l]]>=f[q[l]]) j=q[l++];
		f[i]=s[i]-s[j];
		d[i]=d[j]+1;
		while(l<=r&&f[i]<=f[q[r]]-s[i]+s[q[r]]) r--;
		q[++r]=i;
	}
	cout<<d[n]<<endl;
	return 0;
}