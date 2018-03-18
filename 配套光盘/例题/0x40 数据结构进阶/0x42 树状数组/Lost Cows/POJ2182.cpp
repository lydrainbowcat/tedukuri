#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[10000],c[10000],h[10000],n;

int ask(int x)
{
	int ans=0;
	for(;x;x-=x&-x) ans+=c[x];
	return ans;
}

void add(int x,int y)
{
	for(;x<=n;x+=x&-x) c[x]+=y;
}

int query(int x)
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(ask(mid)<x) l=mid+1; else r=mid;
	}
	return l;
}

int main()
{
	cin>>n;
	for(int i=2;i<=n;i++) scanf("%d",&a[i]);
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++) add(i,1);
	for(int i=n;i;i--)
	{
	    h[i]=query(a[i]+1);
	    add(h[i],-1);
	}
	for(int i=1;i<=n;i++) cout<<h[i]<<endl;
	//system("pause");
}