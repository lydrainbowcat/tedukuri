/*
    Author: wccy
    本程序仅供参考
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

#define N 60000

using namespace std;

struct TREE
{
	int u,l,r;
}T[N<<2];

int n,m,ans;
int cov[N<<2],mx[N<<2],lt[N<<2],rt[N<<2];
//0-区间没人，1-区间人满，-1-区间不确定 

inline void push_up(int u)
{
	if(cov[u<<1]==0&&cov[u<<1|1]==0) cov[u]=0;
	else if(cov[u<<1]==1&&cov[u<<1|1]==1) cov[u]=1;
	else cov[u]=-1;
	
	lt[u]=lt[u<<1]; rt[u]=rt[u<<1|1];
	if(lt[u<<1]==T[u<<1].r-T[u<<1].l+1) lt[u]+=lt[u<<1|1];
	if(rt[u<<1|1]==T[u<<1|1].r-T[u<<1|1].l+1) rt[u]+=rt[u<<1]; 
	mx[u]=max(max(mx[u<<1],mx[u<<1|1]),rt[u<<1]+lt[u<<1|1]);
}

inline void push_down(int u)
{
	cov[u<<1]=cov[u<<1|1]=cov[u]; 
	if(cov[u]==0)
	{
		mx[u<<1]=rt[u<<1]=lt[u<<1]=T[u<<1].r-T[u<<1].l+1;
		mx[u<<1|1]=rt[u<<1|1]=lt[u<<1|1]=T[u<<1|1].r-T[u<<1|1].l+1;
	}
	else mx[u<<1]=rt[u<<1]=lt[u<<1]=mx[u<<1|1]=rt[u<<1|1]=lt[u<<1|1]=0;
	cov[u]=-1;
}

void create(int u,int l,int r)
{
	T[u].l=l; T[u].r=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	create(u<<1,l,mid); create(u<<1|1,mid+1,r);
}

void updata(int u,int L,int R,int bz)
{
	if(L<=T[u].l&&T[u].r<=R)
	{
		cov[u]=bz;
		if(bz==1) mx[u]=rt[u]=lt[u]=0;
		else mx[u]=rt[u]=lt[u]=T[u].r-T[u].l+1;
		return;
	}
	if(cov[u]!=-1) push_down(u);
	int mid=(T[u].l+T[u].r)>>1;
	if(R<=mid) updata(u<<1,L,R,bz);
	else if(L>=mid+1) updata(u<<1|1,L,R,bz);
	else updata(u<<1,L,mid,bz),updata(u<<1|1,mid+1,R,bz);
	push_up(u);
}

void query(int u,int b)
{
	if(mx[u]<b) return;
	if(lt[u]>=b) {ans=T[u].l;return;}
	else
	{
		query(u<<1,b);
		if(ans!=0) return;
		if(rt[u<<1]+lt[u<<1|1]>=b) {ans=T[u<<1].r-rt[u<<1]+1;return;}
		query(u<<1|1,b);
	}
}

void read()
{
	create(1,1,n);
	cov[1]=0; mx[1]=lt[1]=rt[1]=n;

	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d",&a);
		if(a==1)
		{
			scanf("%d",&b);
			ans=0;
			query(1,b);
			printf("%d\n",ans);
			if(ans) updata(1,ans,ans+b-1,1);
		}
		else
		{
			scanf("%d%d",&b,&c);
			updata(1,b,b+c-1,0);
		}
		//for(int j=1;j<=n*4;j++) printf("%d     %d     %d    %d    %d    %d   %d\n",j,T[j].l,T[j].r,cov[j],mx[j],lt[j],rt[j]);
		//system("pause");
	}
}

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF) read();
	return 0;
}