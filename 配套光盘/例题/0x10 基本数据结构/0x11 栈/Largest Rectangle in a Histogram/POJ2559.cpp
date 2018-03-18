#include<iostream>
#include<cstdio>
#include<cstring> 
#include<algorithm>
using namespace std;
int n,p;
int a[100010];
int s[100010],w[100010];
long long ans;

int main()
{
	while(cin>>n&&n)
	{
		ans=0; p=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		a[n+1]=0;
		for(int i=1;i<=n+1;i++)
		{
			if(a[i]>s[p]) s[++p]=a[i],w[p]=1;
			else{
				int width=0;
				while(s[p]>a[i])
				{
					width+=w[p];
					ans=max(ans,(long long)width*s[p]);
					p--;
				}
				s[++p]=a[i],w[p]=width+1;
			}
		}
		cout<<ans<<endl;
	}
}