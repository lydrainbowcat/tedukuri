#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[20][20],c[20][20];
long long f[70],d[70][70],e[70][70][70];
char b[20][20],s[100],ch;
int n,m,t,q,p,i,j;
long long ans;

void readln()
{
	cin>>n>>m>>t>>q;
	for(i=1;i<=n;i++)
	{
		scanf("%s",s+1); 
		for(j=1;j<=m;j++)
		{
			ch=s[j]; 
			a[i][j]=ch-'0'+1;
		}
	}		
	for(i=1;i<=q;i++) scanf("%s",&b[i]);
}

inline int num(int i,int j)
{
	return (i-1)*m+j;
}

void mulself(long long a[70][70],long long b[70][70])
{
	long long c[70][70],i,j,k;
	memset(c,0,sizeof(c));
	for(i=1;i<=p;i++)
		for(k=1;k<=p;k++)
			if(a[i][k])
				for(j=1;j<=p;j++)
					c[i][j]+=a[i][k]*b[k][j];
	memcpy(a,c,sizeof(c));
} 

void makematrix()
{
	int i,j,k,x,y;
	p=n*m+1;
	for(k=1;k<=60;k++)
	{
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{
				x=a[i][j]; y=c[i][j];
				if(b[x][y]>='0'&&b[x][y]<='9')
				{
					e[k][p][num(i,j)]=b[x][y]-'0';
					e[k][num(i,j)][num(i,j)]=1;
				}
				else if(b[x][y]=='N'&&i>1) e[k][num(i,j)][num(i-1,j)]=1;
				else if(b[x][y]=='W'&&j>1) e[k][num(i,j)][num(i,j-1)]=1;
				else if(b[x][y]=='S'&&i<n) e[k][num(i,j)][num(i+1,j)]=1;
				else if(b[x][y]=='E'&&j<m) e[k][num(i,j)][num(i,j+1)]=1;
				c[i][j]=(y+1)%strlen(b[x]);
			}
		e[k][p][p]=1;
	}
	memcpy(d,e[1],sizeof(e[1]));
	for(k=2;k<=60;k++) mulself(d,e[k]);
}

void mul(long long a[70],long long b[70][70])
{
	long long c[70],i,j;
	memset(c,0,sizeof(c));
	for(i=1;i<=p;i++)
		for(j=1;j<=p;j++)
			c[i]+=a[j]*b[j][i];
	memcpy(f,c,sizeof(c));
}

void solve()
{
	f[p]=1;
	for(i=t/60;i;i>>=1)
	{
		if(i&1) mul(f,d);
		mulself(d,d);
	}
	for(i=1;i<=t%60;i++)
		mul(f,e[i]);
	for(i=1;i<p;i++) ans=max(ans,f[i]);
}

int main()
{
	readln();
	makematrix();
	solve();
	cout<<ans<<endl;
	return 0;
}