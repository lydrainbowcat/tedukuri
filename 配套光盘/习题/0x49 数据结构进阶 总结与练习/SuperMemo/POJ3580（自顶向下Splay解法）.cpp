#include<iostream>
#include<cstdio>
using namespace std;
struct{int l,r,size,dat,bit,add,rev;}a[200010];
int L[200010],R[200010],n,m,tot,root,i,x,y,z;
char str[10];

void spreadadd(int x,int y)
{
	if(!x||!y) return;
	a[x].add+=y; a[x].dat+=y; a[x].bit+=y;
}

void spreadrev(int x)
{
	if(!a[x].rev) return;
	swap(a[x].l,a[x].r);
	if(a[x].l) a[a[x].l].rev^=1;
	if(a[x].r) a[a[x].r].rev^=1;
}

void spread(int x)
{
	spreadadd(a[x].l,a[x].add); 
	spreadadd(a[x].r,a[x].add);
	spreadrev(x);
	a[x].add=a[x].rev=0;	
}

inline void update(int x)
{
	a[x].size=a[a[x].l].size+a[a[x].r].size+1;
	a[x].bit=min(a[x].dat,min(a[a[x].l].bit,a[a[x].r].bit));
}

void turnleft(int &x)
{
	int y=a[x].r; a[x].r=a[y].l; a[y].l=x;
	update(x); update(y);	x=y;
}

void turnright(int &x)
{
	int y=a[x].l; a[x].l=a[y].r; a[y].r=x;
	update(x); update(y);	x=y;
}

void splay(int &x,int y)
{
	if(!x) return;
	L[0]=R[0]=0;
	while(1)
	{
		spread(x),spread(a[x].l),spread(a[x].r);
		int temp=a[a[x].l].size+1;
		if(y==temp||(y<temp&&!a[x].l)||(y>temp&&!a[x].r)) break;
		if(y<temp)
		{
			if(a[a[x].l].l&&y<=a[a[a[x].l].l].size) {turnright(x); if(!a[x].l) break;}
			R[++R[0]]=x; x=a[x].l;
		}
		else
		{
			y-=temp;
			int temp=a[a[a[x].r].l].size+1;
			if(a[a[x].r].r&&y>temp) {y-=temp; turnleft(x); if(!a[x].r) break;}
			L[++L[0]]=x; x=a[x].r;
		}
	}
	L[++L[0]]=a[x].l; R[++R[0]]=a[x].r;
	for(int i=L[0]-1;i>0;i--) {a[L[i]].r=L[i+1]; update(L[i]);}
	for(int i=R[0]-1;i>0;i--) {a[R[i]].l=R[i+1]; update(R[i]);}
	a[x].l=L[1]; a[x].r=R[1]; update(x);
}

void ADD(int x,int y,int z)
{
	splay(root,y+1);
	splay(a[root].l,x-1);
	spreadadd(a[a[root].l].r,z);
}

void INSERT(int x,int y)
{
	splay(root,x);
	a[++tot].dat=y; a[tot].r=a[root].r; a[root].r=tot;
	update(tot); update(root);
}

void DELETE(int x)
{
	splay(root,x);
	splay(a[root].r,1);
	a[a[root].r].l=a[root].l; root=a[root].r;
	update(root);
}

void REVERSE(int x,int y)
{
	splay(root,y+1);
	splay(a[root].l,x-1);
	a[a[a[root].l].r].rev^=1;
}

void REVOLVE(int x,int y,int z)
{
	z%=y-x+1;
	if(!z)return;
	int mid=y-z;
	splay(root,mid);
	splay(a[root].l,x-1);
	splay(a[root].r,y-a[a[root].l].size);
	z=a[root].l;
	a[root].l=a[z].r;
	a[z].r=a[a[root].r].l;
	a[a[root].r].l=0;
	update(z); update(a[root].r); update(root);
	splay(root,1);
	a[root].l=z;
	update(root);
}

void MIN(int x,int y)
{
	splay(root,y+1);
	splay(a[root].l,x-1);
	printf("%d\n",a[a[a[root].l].r].bit);
}

int main()
{ 
	cin>>n;
	a[1].size=1; a[n+2].l=n+1; a[n+2].size=n+2;
	a[1].dat=a[n+2].dat=a[1].bit=a[0].bit=0x3fffffff;
	for(i=2;i<=n+1;i++)
	{
		scanf("%d",&a[i].dat);
		a[i].l=i-1; a[i].size=i;
		a[i].bit=min(a[i-1].bit,a[i].dat);
	}
	a[n+2].bit=a[n+1].bit;
	root=tot=n+2;
	cin>>m;
	for(i=0;i<m;i++)
	{
		scanf("%s",&str);
		if(str[0]=='A') {scanf("%d%d%d",&x,&y,&z); ADD(++x,++y,z);}
		if(str[0]=='I') {scanf("%d%d",&x,&y); INSERT(++x,y);}
		if(str[0]=='D')	{scanf("%d",&x); DELETE(++x);}
		if(str[0]=='M') {scanf("%d%d",&x,&y);	MIN(++x,++y);}		
		if(str[0]=='R'&&str[3]=='E') {scanf("%d%d",&x,&y);	REVERSE(++x,++y);}
		if(str[0]=='R'&&str[3]=='O') {scanf("%d%d%d",&x,&y,&z);	REVOLVE(++x,++y,z);}		
	}
	return 0;
}