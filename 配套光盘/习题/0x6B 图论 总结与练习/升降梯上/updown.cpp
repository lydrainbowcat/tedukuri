#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct rec{int x,y;};
int d[1010][21],c[21],v[1010][21],n,m,i,j,k; 

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

int main()
{
	freopen("updown.in","r",stdin);
	freopen("updown.out","w",stdout); 
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
	return 0; 
}
