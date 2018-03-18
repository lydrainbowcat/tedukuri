#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<queue>
using namespace std;
struct rec{int x,y;};
int d[1010][21],c[21],v[1010][21],n,m,i,j,k; 
char s[100],in[100],out[100];
long long T,Data[11]={0,10,10,10,100,100,1000,1000,1000,1000,1000},Data2[11]={0,3,5,5,10,10,15,15,20,20,20};

void file()
{
	memset(s,0,sizeof(s));
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	strcat(s,"updown");
	sprintf(s+strlen(s),"%d.",T);
	strcat(in,s),strcat(in,"in");
	strcat(out,s),strcat(out,"out");
}

void random()
{
	n=Data[T],m=Data2[T];
	cout<<Data[T]<<' '<<Data2[T]<<endl;
	j=-min(n,100); 
	for(i=m;i;i--)
	{
		do{k=(j+rand()%min(n,50))%(n-i+1);}while(k<=j);
		if(j<0&&k>0) k=0; 
		cout<<k<<' '; j=k;
	} 
}

void spfa()
{
	memset(d,0x3f,sizeof(d));
	queue<rec> q;
	q.push((rec){1,j}); d[1][j]=0,v[1][j]=1;
	while(q.size())
	{
		v[i=q.front().x][j=q.front().y]=0,q.pop();
		for(k=1;k<=m;k++)
			if(i+c[k]>0&&i+c[k]<=n&&d[i+c[k]][k]>d[i][j]+abs(j-k)+2*abs(c[k]))
			{
				d[i+c[k]][k]=d[i][j]+abs(j-k)+2*abs(c[k]);
				if(!v[i+c[k]][k]) q.push((rec){i+c[k],k}),v[i+c[k]][k]=1;
			}
	}
}
void stdf()
{
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		scanf("%d",&c[i]);
		if(!c[i]) j=i;
	}
	spfa();
	for(i=1;i<=m;i++)
		d[n][1]=min(d[n][1],d[n][i]);
	cout<<(d[n][1]==0x3f3f3f3f?-1:d[n][1])<<endl;
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
