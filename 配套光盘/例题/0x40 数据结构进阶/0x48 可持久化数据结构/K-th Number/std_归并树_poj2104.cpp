#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct{int l,r,s,e;}t[400010];
int ver[2000000],a[100010],b[100010],n,m,tot,i,k,x,y,z,l,r,mid;

void merge(int num,int s,int l,int mid,int r)
{
	int i=l,j=mid+1,k;
	for(k=1;k<=r-l+1;k++)
		if(j>r||(i<=mid&&a[i]<=a[j])) {b[k]=a[i]; i++;}
		else{b[k]=a[j]; j++;}
	for(k=1;k<=r-l+1;k++) ver[s+k]=a[l+k-1]=b[k];
	t[num].l=l; t[num].r=r;
	t[num].s=tot+1; t[num].e=tot+r-l+1;
	tot+=r-l+1;
}

void mergesort(int num,int l,int r)
{
	if(l==r)
	{
		ver[++tot]=a[l];
		t[num].l=t[num].r=l;
		t[num].s=t[num].e=tot;
		return;
	}
	int mid=(l+r)>>1;
	if(l<=mid) mergesort(num*2,l,mid);
	if(mid<r) mergesort(num*2+1,mid+1,r);
	merge(num,tot,l,mid,r);
}

int ask(int num)
{
	if(x<=t[num].l&&y>=t[num].r)
	{
		int l=t[num].s,r=t[num].e,mid,temp=l-1;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(ver[mid]<z) {temp=max(temp,mid); l=mid+1;} else r=mid-1;
		}
		return temp-t[num].s+1;
	}
	int temp=0,mid=(t[num].l+t[num].r)>>1;
	if(x<=mid) temp+=ask(num*2);
	if(y>mid) temp+=ask(num*2+1);
	return temp;
}

int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	mergesort(1,1,n);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&k);
		l=1; r=n;
		while(l<r)
		{
			mid=(l+r+1)>>1;
			z=a[mid];
			if(ask(1)>=k) r=mid-1;else l=mid;
		}
		printf("%d\n",a[l]);
	}
	return 0;
}