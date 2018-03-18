#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n, c[1000010];
vector<int> a,b;

int ask(int x)
{
	int y=0;
	for(;x;x-=x&-x) y+=c[x];
	return y;
}

void add(int x)
{
	for(;x<=n*n-1;x+=x&-x) c[x]++;
}

long long calc(vector<int> a)
{
	long long ans=0;
	memset(c,0,sizeof(c));
	for(int i=a.size()-1;i>=0;i--)
	{
		ans+=ask(a[i]);
		add(a[i]);
	}
	return ans;
}

int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout); 
	while(cin>>n)
	{
		a.clear();
		b.clear();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				int x;
				scanf("%d",&x);
				if(x) a.push_back(x);
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				int x;
				scanf("%d",&x);
				if(x) b.push_back(x);
			}
		puts(calc(a)-calc(b)&1 ? "NIE" : "TAK");
	}
}
