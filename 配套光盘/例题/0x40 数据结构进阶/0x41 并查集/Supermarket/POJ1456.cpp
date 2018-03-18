#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int SIZE=10010;
int fa[SIZE];
struct item{int p,d;}a[SIZE];

int get(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}

bool cmp(item a,item b)
{
	return a.p>b.p;
}

int main()
{
	int n;
	while(cin>>n)
	{
		int m=0,ans=0;
		for(int i=1;i<=n;i++)
		{
		    scanf("%d%d",&a[i].p,&a[i].d);
		    m=max(m,a[i].d);
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=m;i++) fa[i]=i;
		for(int i=1;i<=n;i++)
		{
			int day=get(a[i].d);
			if(day==0) continue;
			ans+=a[i].p;
			fa[day]=get(day-1);
		}
		cout<<ans<<endl;
	}
	system("pause");
}