#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int u=250010,w=500;
struct rec{__int64 d,r; int m,p;}a[u];
__int64 D[u],x0,y0,rad;
int L[u],R[u],q[u],v[u],n,tot,l,r,p,x,y;
bool cmp_d(rec a,rec b){return a.d<b.d;}
bool cmp_m(rec a,rec b){return a.m<b.m;}
int main()
{
	freopen("magnet.in","r",stdin);
	freopen("magnet.out","w",stdout);
	cin>>x0>>y0>>a[0].p>>a[0].r>>n;
	a[0].r*=a[0].r;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d%I64d",&x,&y,&a[i].m,&a[i].p,&a[i].r);
		a[i].r*=a[i].r;
		a[i].d=(x0-x)*(x0-x)+(y0-y)*(y0-y);
	}
	sort(a+1,a+n+1,cmp_d);
	for(int i=1;i<=n;i+=w)
	{
		L[++tot]=i,R[tot]=min(n,i+w-1),D[tot]=a[R[tot]].d;
		sort(a+L[tot],a+R[tot]+1,cmp_m);
	}
	l=r=1,q[1]=0; 
	while(l<=r)
	{
		rad=a[q[l]].r,p=a[q[l]].p,l++;
		for(int i=1;i<=tot;++i)
		{
			if(D[i]>rad)
			{
				for(int j=L[i];j<=R[i];++j)
					if(!v[j]&&a[j].d<=rad&&a[j].m<=p) v[q[++r]=j]=1;
				break;
			}
			while(L[i]<=R[i]&&a[L[i]].m<=p)
			{
				if(!v[L[i]]) q[++r]=L[i];
				++L[i];
			}
		}
	}
	cout<<r-1<<endl;
}
