#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<bitset>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<queue>
#include<iomanip>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef pair<ll,ll> pll;

#define X first
#define Y second

const int MaxN=100010;

int n,m,p;
int d[MaxN];
ll a[MaxN],s[MaxN];
ll F[2][MaxN];
int head,tail,Q[MaxN];

ld det(ld x1,ld y1,ld x2,ld y2,ld x3,ld y3)
{
	return x1*y2-x2*y1+x2*y3-x3*y2+x3*y1-x1*y3;
}

int main()
{
	cin>>n>>m>>p;
	for (int i=2;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		d[i]=d[i-1]+x;
	}
	for (int i=1;i<=m;++i)
	{
		int h,t;
		scanf("%d%d",&h,&t);
		a[i]=t-d[h];
	}
	sort(a+1,a+m+1);
	for (int i=1;i<=m;++i)
		s[i]=s[i-1]+a[i];
	for (int i=1;i<=m;++i)
		F[1][i]=a[i]*i-s[i];
	for (int k=2;k<=p;++k)
	{
		int x=k&1;
		int y=x^1;
		Q[head=tail=1]=0;
		for (int i=1;i<=m;++i)
		{
			while (head<tail)
			{
				if (det(i,F[y][i]+s[i],Q[tail],F[y][Q[tail]]+s[Q[tail]],Q[tail-1],F[y][Q[tail-1]]+s[Q[tail-1]])<0) break;
				--tail;
			}
			Q[++tail]=i;
			while (head<tail)
			{
				if ((F[y][Q[head+1]]+s[Q[head+1]])-(F[y][Q[head]]+s[Q[head]])>=a[i]*(Q[head+1]-Q[head])) break;
				++head;
			}
			F[x][i]=F[y][Q[head]]+a[i]*(i-Q[head])-s[i]+s[Q[head]];
		}
	}
	cout<<F[p&1][m]<<endl;
	return 0;
}
