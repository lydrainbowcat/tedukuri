#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int a[100010],b[100010],d[1280][1280],c[100010];
int st[100010],ed[100010],s[100010],e[100010],v[100010],q[100010];
int n,t,tot,m,i;

int calc(int k,int x,int y)
{
	if(x>y) return 0;
	int l,r,mid;
	l=st[k],r=ed[k];
	while(l<r)
	{
		mid=(l+r+1)>>1;
		if(b[mid]<x) l=mid; else r=mid-1;
	}
	if(b[l]>=x) l--;
	x=l;
	l=st[k],r=ed[k];
	while(l<r)
	{
		mid=(l+r+1)>>1;
		if(b[mid]>y) r=mid-1; else l=mid;
	}
	if(b[l]>y) l--;
	y=l;
	return y-x;
}

void solve()
{
	int p,l,r,i,j,k,now,x,y,cnt;
	for(i=1;i<=n;i++) c[a[i]]++;
	for(i=1;i<=t;i++) st[i]=tot+1,tot+=c[i],ed[i]=tot;
	memset(c,0,sizeof(c));
	for(i=1;i<=n;i++) b[st[a[i]]+c[a[i]]]=i,c[a[i]]++;
	p=(int)sqrt(n)*4,l=n/p;
	for(i=1;i<=p;i++) s[i]=(i-1)*l+1,e[i]=i*l;
	if(e[p]<n) p++,s[p]=e[p-1]+1,e[p]=n;
	for(i=1;i<=p;i++)
	{
		memset(c,0,sizeof(c)); now=0;
		for(j=i;j<=p;j++)
		{
			for(k=s[j];k<=e[j];k++)
			{
				c[a[k]]++;
				if(c[a[k]]>1&&(c[a[k]]&1)) now--;
				else if((c[a[k]]&1)==0) now++;
			}
			d[i][j]=now;
		}
	}
	for(now=0,i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		x=(x+now)%n+1,y=(y+now)%n+1;
		if(x>y) swap(x,y); 
		for(j=1;j<=p;j++) if(x<=e[j]) {l=j; break;}
		for(j=p;j;j--) if(y>=s[j]) {r=j; break;}
		now=d[l+1][r-1];
		if(l==r)
		{
			for(j=x;j<=y;j++)
				if(v[a[j]]!=i) v[a[j]]=i,c[a[j]]=1;
				else{
					c[a[j]]++;
					if(c[a[j]]&1) now--; else now++;
				}
		}
		else{
			cnt=0;
			for(j=x;j<=e[l];j++)
				if(v[a[j]]!=i) v[a[j]]=i,c[a[j]]=1,q[++cnt]=a[j]; else c[a[j]]++;
			for(j=s[r];j<=y;j++)
				if(v[a[j]]!=i) v[a[j]]=i,c[a[j]]=1,q[++cnt]=a[j]; else c[a[j]]++;
			for(j=1;j<=cnt;j++)
			{
				k=calc(q[j],s[l+1],e[r-1]);
				if(k==0) {if(c[q[j]]&1) now+=0; else now++;}
				else if((k&1)&&(c[q[j]]&1)) now++;
				else if((k&1)==0&&(c[q[j]]&1)) now--;
			}
		}
		printf("%d\n",now);
	}
}

int main()
{ 
	cin>>n>>t>>m;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	solve();
	return 0;
}