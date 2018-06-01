#include<iostream>
#include<cstdio>
using namespace std;
const int inf=-0x3fffffff;
struct tree{int l,r,sum,dat,dl,dr;}t[2000010];
int a[500010],n,m,i,x,y,z;

void ini(tree &a,int temp)
{
	a.dat=a.sum=a.dl=a.dr=temp;
}

void calc(int num)
{
	t[num].sum=t[num*2].sum+t[num*2+1].sum;
	t[num].dl=max(t[num*2].dl,t[num*2].sum+t[num*2+1].dl);
	t[num].dr=max(t[num*2+1].dr,t[num*2+1].sum+t[num*2].dr);
	t[num].dat=max(max(t[num*2].dat,t[num*2+1].dat),t[num*2].dr+t[num*2+1].dl);
}

void build(int num,int l,int r)
{
	t[num].l=l; t[num].r=r;
	ini(t[num],a[l]);
	if(l==r)return;
	int mid=(l+r)>>1;
	build(num*2,l,mid);
	build(num*2+1,mid+1,r);
	calc(num);
}

tree ask(int num)
{
	if(x<=t[num].l&&y>=t[num].r) return t[num];
	int mid=(t[num].l+t[num].r)>>1;
	tree a,b,c;
	ini(a,inf); ini(b,inf);
	c.sum=0;
	if(x<=mid)
	{
		a=ask(num*2);
		c.sum+=a.sum;
	}
	if(y>mid) 
	{
		b=ask(num*2+1);
		c.sum+=b.sum;
	}
	c.dat=max(max(a.dat,b.dat),a.dr+b.dl);
	c.dl=max(a.dl,b.dl+a.sum);
	if(x>mid) c.dl=max(c.dl,b.dl);
	c.dr=max(b.dr,b.sum+a.dr);
	if(y<=mid) c.dr=max(c.dr,a.dr);
	return c;
}

void change(int num)
{
	if(t[num].l==t[num].r) 
		{ini(t[num],y); return;}
	int mid=(t[num].l+t[num].r)>>1;
	if(x<=mid)change(num*2);else change(num*2+1);
	calc(num);
}

int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	build(1,1,n);
	for(i=0;i<m;i++)
	{
		scanf("%d%d%d",&z,&x,&y);
		if(z==1) {
			if (x>y) swap(x,y);
			printf("%d\n",ask(1).dat);
		} else change(1);
	}
	return 0;
}
