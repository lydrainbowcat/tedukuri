#include<iostream>
#include<cstring>
using namespace std;
const int dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
int a[9][9],v[9][9],f[6],n,ID;

int left()
{
	int i,j,temp=0;
	memset(f,0,sizeof(f));
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(!f[a[i][j]]&&v[i][j]!=1)
			{f[a[i][j]]=1; temp++;}
	return temp;
}

void dfs(int x,int y,int c)
{
	v[x][y]=1;
	for(int i=0;i<4;i++)
	{
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<1||ny<1||nx>n||ny>n||v[nx][ny]==1)continue;
		v[nx][ny]=2;
		if(a[nx][ny]==c)dfs(nx,ny,c);
	}
}

int fill(int c)
{
	int temp=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]==c&&v[i][j]==2)
			{
				++temp;
				dfs(i,j,c);
			}
	return temp;
}

bool IDAstar(int dep)
{
	int g=left();
	if(dep+g>ID)return 0;
	if(!g)return 1;
	int rec[9][9];		
	for(int i=0;i<=5;i++)
	{	
		memcpy(rec,v,sizeof(v));
		if(fill(i)&&IDAstar(dep+1))return 1;
		memcpy(v,rec,sizeof(v));
	}
	return 0;
}

int main()
{
	while(cin>>n&&n)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)cin>>a[i][j];
		memset(v,0,sizeof(v));
		dfs(1,1,a[1][1]);
		for(ID=0;;ID++)
			if(IDAstar(0))break;
		cout<<ID<<endl;
	}
	return 0;
}