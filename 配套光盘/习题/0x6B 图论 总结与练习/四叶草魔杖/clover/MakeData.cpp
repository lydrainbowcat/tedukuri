#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<iomanip>
#include<cmath>
using namespace std;
char Str[100],in[100],out[100];
long long T;
void file()
{
	memset(Str,0,sizeof(Str));
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	strcat(Str,"clover");
	sprintf(Str+strlen(Str),"%d.",T);
	strcat(in,Str),strcat(in,"in");
	strcat(out,Str),strcat(out,"out");
}

void random()
{
	int n,m,i,j,k,x,y; 
	int v[20][20];
	if(T<=5) n=rand()%7+2; else if(T<=8) n=rand()%8+9; else n=16;
	m=rand()%(n*(n-1)/2);
	cout<<n<<' '<<m<<endl;
	for(i=1,j=k=0;i<n;i++)
	{
		j=(rand()&1?1:-1)*rand()%1000;
		k+=j;
		cout<<j<<' '; 
	}
	cout<<-k<<endl;
	memset(v,0,sizeof(v));
	for(i=1;i<=m;i++)
	{
		do{x=rand()%n;y=rand()%n;}while(x==y||v[x][y]);
		v[x][y]=v[y][x]=1;
		cout<<x<<' '<<y<<' '<<rand()%1000<<endl;
	}
}

int a[20],d[20][20],g[20],b[65536],c[20],f[65536],v[20],s[65536],n,m,i,j,k,l,x,y,z,t,p,q;
int prim()
{
	memset(v,0,sizeof(v));
	memset(g,0x3f,sizeof(g));
	g[c[1]]=0;
	int i,j,temp,k,ans=0;
	for(i=1;i<=m;i++)
	{
		temp=0x3fffffff;
		for(j=1;j<=m;j++)
			if(!v[c[j]]&&g[c[j]]<temp) temp=g[c[j]],k=c[j];
		if(temp==0x3f3f3f3f) return -1;
		ans+=temp;
		v[k]=1;
		for(j=1;j<=m;j++)
			if(!v[c[j]]&&g[c[j]]>d[k][c[j]]) g[c[j]]=d[k][c[j]];
	}
	return ans;
}
void stdf()
{
	cin>>n>>m;
		for(i=1;i<=n;i++) scanf("%d",&a[i]);
		memset(d,0x3f,sizeof(d));
		for(i=1;i<=n;i++) d[i][i]=0;
		for(i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z),x++,y++;
			d[x][y]=d[y][x]=z;
		}
		for(k=1;k<=n;k++)
			for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
		memset(f,0x3f,sizeof(f));
		f[0]=0; t=(1<<n)-1;
		for(i=1;i<=n;i++)
			if(!a[i]) t^=1<<i-1;
		for(p=i=0;i<1<<n;i++)
		{
			for(j=0;j<n;j++)
				if((i>>j&1)&&!a[j+1]) break;
			if(j<n) continue;
			b[i]=0;
			for(m=j=0;j<n;j++)
				if(i>>j&1) b[i]+=a[j+1],c[++m]=j+1;
			if(b[i]) continue;
			b[i]=prim();
			s[++p]=i;
		}
		for(q=2;q<=p;q++)
		{
			i=s[q];
			k=b[i];
			if(k==-1) continue;
			for(l=1;l<=p;l++)
			{
				j=s[l];
				if(!(i&j)) f[i|j]=min(f[i|j],f[j]+k);
			}
		}
		if(f[t]==0x3f3f3f3f) puts("Impossible");
		else cout<<f[t]<<endl;
}
int main()
{
	srand((unsigned)time(0));
	for(T=1;T<=10;T++)
	{
		file();
		freopen(in,"w",stdout);
		random();
		fclose(stdout);
		freopen(in,"r",stdin);
		freopen(out,"w",stdout);
		stdf();
		fclose(stdin);
		fclose(stdout);
	}
	return 0;
}
