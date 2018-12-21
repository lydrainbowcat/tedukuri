#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int SIZE=100010;
struct SegmentTree{
	int l,r;
	long long sum,add;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define sum(x) tree[x].sum
	#define add(x) tree[x].add
}tree[SIZE*4];
int a[SIZE],n,m;

void build(int p,int l,int r)//No.p, [l,r]
{
	l(p)=l,r(p)=r;
	if(l==r) { sum(p)=a[l]; return; }
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	sum(p)=sum(p*2)+sum(p*2+1);
}

void spread(int p)
{
	if(add(p))
	{
		sum(p*2)+=add(p)*(r(p*2)-l(p*2)+1);
		sum(p*2+1)+=add(p)*(r(p*2+1)-l(p*2+1)+1);
		add(p*2)+=add(p);
		add(p*2+1)+=add(p);
		add(p)=0;
	}
}

void change(int p,int l,int r,int z)
{
	if(l<=l(p)&&r>=r(p))
	{
		sum(p)+=(long long)z*(r(p)-l(p)+1);
		add(p)+=z;
		return;
	}
	spread(p);
	int mid=(l(p)+r(p))/2;
	if(l<=mid) change(p*2,l,r,z);
    if(r>mid) change(p*2+1,l,r,z);
	sum(p)=sum(p*2)+sum(p*2+1);
}

long long ask(int p,int l,int r)
{
	if(l<=l(p)&&r>=r(p)) return sum(p);
	spread(p);
    int mid=(l(p)+r(p))/2;
	long long ans=0;
    if(l<=mid) ans+=ask(p*2,l,r);
    if(r>mid) ans+=ask(p*2+1,l,r);
    return ans;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	while(m--)
	{
		char op[2]; int x,y,z;
		scanf("%s%d%d",op,&x,&y);
		if(op[0]=='C')
		{
			scanf("%d",&z);
			change(1,x,y,z);
		}
		else printf("%I64d\n",ask(1,x,y));
	}
}