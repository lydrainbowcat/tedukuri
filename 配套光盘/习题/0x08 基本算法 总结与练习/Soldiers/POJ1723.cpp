#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
using namespace std;
int a[10010],b[10010],n,i,x,y,ans;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	sort(b+1,b+n+1);
	y=b[n+1>>1];
	sort(a+1,a+n+1);
	for(i=1;i<=n;i++) a[i]-=i;
	sort(a+1,a+n+1);
	x=a[n+1>>1]; 
	for(i=1;i<=n;i++) ans+=abs(a[i]-x)+abs(b[i]-y);
	cout<<ans<<endl; 
	return 0;
}