#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int a[100010],b[100010],n,i;
long long x,y;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<n;i++)
	{
		b[i]=a[i+1]-a[i];
		if(b[i]>0) x+=b[i]; else y-=b[i];
	}
	cout<<max(x,y)<<endl<<abs(x-y)+1<<endl;
}