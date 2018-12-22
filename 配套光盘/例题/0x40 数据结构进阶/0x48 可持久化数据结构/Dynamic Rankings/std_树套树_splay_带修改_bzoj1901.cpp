#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int inf=1000000000;
struct tree{int l,r,dat,size;}t[40010],a[1000010];
int L[10010],R[10010],p[40010],b[10010],n,m,tot,i,l,r,k,x,y,z;
char str[2];

inline void update(int x)
{
	a[x].size=a[a[x].l].size+a[a[x].r].size+1;
}

void zag(int &x)
{
	int y=a[x].r; a[x].r=a[y].l; a[y].l=x;
	update(x); update(y); x=y;
}

void zig(int &x)
{
	int y=a[x].l; a[x].l=a[y].r; a[y].r=x;
	update(x); update(y); x=y;
}

void comb(int &x)
{
	L[L[0]+1]=a[x].l; R[R[0]+1]=a[x].r;
	for(int i=L[0];i>0;i--) {a[L[i]].r=L[i+1]; update(L[i]);}
	for(int i=R[0];i>0;i--) {a[R[i]].l=R[i+1]; update(R[i]);}
	a[x].l=L[1]; a[x].r=R[1]; update(x);
}

void get(int &x,int y)
{
	if(!x) return;
	L[0]=R[0]=0;
	while(1)
	{
		if(y==a[x].dat||(y<a[x].dat&&!a[x].l)||(y>a[x].dat&&!a[x].r)) break;
		if(y<a[x].dat)
		{
			if(y<a[a[x].l].dat) {zig(x); if(!a[x].l) break;}
			R[++R[0]]=x; x=a[x].l;
		}
		else{
			if(y>a[a[x].r].dat) {zag(x); if(!a[x].r) break;}
			L[++L[0]]=x; x=a[x].r;
		}
	}
	comb(x);
}

void splay(int &x,int y)
{
	if(!x) return;
	L[0]=R[0]=0;
	while(1)
	{
		int temp=a[a[x].l].size+1;
		if(y==temp||(y<temp&&!a[x].l)||(y>temp&&!a[x].r)) break;
		if(y<temp)
		{
			if(a[a[x].l].l&&y<=a[a[a[x].l].l].size) {zig(x); if(!a[x].l) break;}
			R[++R[0]]=x; x=a[x].l;
		}
		else{
			y-=temp;
			temp=a[a[a[x].r].l].size+1;
			if(a[a[x].r].r&&y>temp) {y-=temp; zag(x); if(!a[x].r) break;}
			L[++L[0]]=x; x=a[x].r;
		}
	}
	comb(x);
}

void ins(int &x,int y)
{
	a[++tot].dat=y; a[tot].size=1;
	get(x,y);
	if(a[x].dat<=y)
	{
		splay(a[x].r,1);
		a[a[x].r].l=tot;
		update(a[x].r); update(x);
	}
	else{
		splay(a[x].l,a[a[x].l].size);
		a[a[x].l].r=tot;
		update(a[x].l); update(x);
	}
}

void del(int &x,int y)
{
	get(x,y);
	splay(a[x].r,1);
	a[a[x].r].l=a[x].l;
	x=a[x].r;
	update(x);
}

void buildsplay(int num)
{
	p[num]=++tot; a[tot].r=tot+1;
	a[tot].dat=-inf; a[tot].size=2;
	a[++tot].dat=inf; a[tot].size=1;
	for(int i=t[num].l;i<=t[num].r;i++) ins(p[num],b[i]);
}

void build(int num,int l,int r)
{
	t[num].l=l; t[num].r=r; t[num].dat=b[l];
	buildsplay(num);
	if(l==r) return;
	int mid=(l+r)>>1;
	build(num*2,l,mid);
	build(num*2+1,mid+1,r);
}

void change(int num)
{
	if(t[num].l==t[num].r)
	{
		z=t[num].dat; t[num].dat=y;
		del(p[num],z);
		ins(p[num],y);
		return;
	}
	int mid=(t[num].l+t[num].r)>>1;
	if(x<=mid) change(num*2); else change(num*2+1);
	del(p[num],z);
	ins(p[num],y);
}

int ask(int num)
{
	if(x<=t[num].l&&y>=t[num].r)
	{
		get(p[num],k);
		splay(a[p[num]].r,1);
		while(a[p[num]].dat==k&&a[a[p[num]].r].dat==k)
		{
			zag(p[num]);
			splay(a[p[num]].r,1);
		}
		if(a[p[num]].dat<=k) return a[a[p[num]].l].size;
		else return a[a[p[num]].l].size-1;
	}
	int mid=(t[num].l+t[num].r)>>1,temp=0;
	if(x<=mid) temp+=ask(num*2);
	if(y>mid) temp+=ask(num*2+1);
	return temp;
}

int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++) scanf("%d",&b[i]);
	build(1,1,n);
	for(i=1;i<=m;i++)
	{
		scanf("%s%d%d",str,&x,&y);
		if(str[0]=='Q')
		{
			scanf("%d",&z);
			l=0; r=inf;
			while(l<r)
			{
				k=(l+r)>>1;
				if(ask(1)<z) l=k+1;else r=k;
			}
			printf("%d\n",l);
		}
		else change(1);
	}
	return 0;
}