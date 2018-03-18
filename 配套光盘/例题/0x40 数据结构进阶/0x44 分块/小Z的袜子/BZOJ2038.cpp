#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int u=50010;
struct rec{int x,y,z;}a[u],b[u];
int c[u],v[u],n,m,t,p,len,i,j,k,l,r;
ll fx[u],fy[u],temp;
bool cmp1(rec a,rec b) {return a.x<b.x;}
bool cmp2(rec a,rec b) {return a.y<b.y;}
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}
void calc(int st,int ed,int dt)
{
	for(int i=st;i<ed;i++)
	{
		temp-=(ll)v[c[i]]*(v[c[i]]-1);
		v[c[i]]+=dt;
		temp+=(ll)v[c[i]]*(v[c[i]]-1);
	}
}
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++) scanf("%d",&c[i]);
	for(i=1;i<=m;i++) scanf("%d%d",&a[i].x,&a[i].y),a[i].z=i;
	sort(a+1,a+m+1,cmp1);
	len=(int)sqrt(n*1.0),p=n/len+(n%len!=0);
	for(i=0,j=1;i<p;i++)
	{
		for(t=0;j<=m&&a[j].x>i*len&&a[j].x<=(i+1)*len;j++) b[++t]=a[j];
		sort(b+1,b+t+1,cmp2);
		l=b[1].x,r=b[1].x-1,temp=0;
		memset(v,0,sizeof(v));
		for(k=1;k<=t;k++)
		{
			if(l<b[k].x) calc(l,b[k].x,-1);
			else if(l>b[k].x) calc(b[k].x,l,1);
			if(r<b[k].y) calc(r+1,b[k].y+1,1);
			else if(r>b[k].y) calc(b[k].y+1,r+1,-1);
			fx[b[k].z]=temp,fy[b[k].z]=b[k].y-b[k].x+1;
			l=b[k].x,r=b[k].y;
		}
	}
	for(i=1;i<=m;i++)
	{
		if(!fy[i]) {puts("0/1"); continue;}
		fy[i]=fy[i]*(fy[i]-1);
		temp=gcd(fx[i],fy[i]);
		printf("%lld/%lld\n",fx[i]/temp,fy[i]/temp);
	}
	return 0;
}
