#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int u=12100;
int trie[u*32][2],rpos[u*32]={-1},h[u],a[u],b[80][u];
int n,m,tot,t,l,i,j,k,p,x,y,ans;

void insert(int last,int now,int k)
{
	int i,j,p;
	h[k]=p=++tot,rpos[p]=k;;
	for(i=30;i>=0;i--)
	{
		j=(now>>i)&1;
		trie[p][j^1]=trie[last][j^1];
		trie[p][j]=++tot;
		p=tot,rpos[p]=k;
		last=trie[last][j];
	}
}

int ask(int l,int r,int x)
{
	int i,j,p,ans=0;
	p=h[r];
	for(i=30;i>=0;i--)
	{
		j=((x>>i)&1)^1;
		if(rpos[trie[p][j]]>=l) ans|=1<<i; else j^=1;
		p=trie[p][j];
	}
	return ans;
}

int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]^=a[i-1];
	}
	t=(int)sqrt(m);
	l=n/t+(n%t!=0);
	insert(h[0],a[0],0);
	for(i=1;i<=n;i++) insert(h[i-1],a[i],i);
	for(i=0;i<t;i++)
		for(j=i*l+1;j<=n;j++)
			b[i][j]=max(b[i][j-1],ask(i*l,j-1,a[j]));
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		x=(x+ans%n)%n+1,y=(y+ans%n)%n+1;
		if(x>y) swap(x,y); x--;
		p=x/l+(x%l!=0);
		ans=p*l<y?b[p][y]:0;
		for(j=x,p=min(p*l,y);j<=p;j++)
			ans=max(ans,ask(x,y,a[j]));
		printf("%d\n",ans);
	}
	return 0;
}