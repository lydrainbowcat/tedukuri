#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
struct rec{int x,y,z;}a[200010],b[200010];
int n,m,t,i;
double ans;

bool cmp(rec a,rec b)
{
	return a.x<b.x;
}

double dist(rec a,rec b)
{
	return sqrt(1.0*(a.x-b.x)*(a.x-b.x)+1.0*(a.y-b.y)*(a.y-b.y));
}

void merge(int l,int mid,int r)
{
	int i=l,j=mid+1,k;
	for(k=l;k<=r;k++)
		if(j>r||i<=mid&&a[i].y<a[j].y) b[k]=a[i++]; else b[k]=a[j++];
	for(k=l;k<=r;k++) a[k]=b[k];
}

void solve(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1,p=0,x=a[mid].x,i,j;
	solve(l,mid);
	solve(mid+1,r);
	merge(l,mid,r);
	for(i=l;i<=r;i++)
		if(abs(a[i].x-x)<=ans) b[++p]=a[i];
	for(i=1;i<p;i++)
		for(j=i+1;j<=p;j++)
			if(b[j].y-b[i].y<ans)
				{if(b[i].z!=b[j].z) ans=min(ans,dist(b[i],b[j]));}
			else break;
}

int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y),a[i].z=1;
		for(i=n+1,n*=2;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y),a[i].z=2;
		ans=dist(a[1],a[n]);
		sort(a+1,a+n+1,cmp);
		solve(1,n);
		printf("%.3f\n",ans);
	}
	return 0;
}
