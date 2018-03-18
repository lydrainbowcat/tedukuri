#include<iostream>
#include<cstdio>
using namespace std;
const char tar[5][5]={
{'1','1','1','1','1'},
{'0','1','1','1','1'},
{'0','0','*','1','1'},
{'0','0','0','0','1'},
{'0','0','0','0','0'}};
const int dx[8]={-2,-2,-1,-1,1,1,2,2},dy[8]={-1,1,-2,2,-2,2,-1,1};
char a[5][5];
int t,i,ID;

int calc(int &x,int &y)
{
	int i,j,k=0;
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
		{
			if(a[i][j]=='*') x=i,y=j;
			if(a[i][j]!=tar[i][j]) k++;
		}
	return k;
}

bool dfs(int step)
{
	int rest,x,y,i,j,k;
	rest=calc(x,y);
	if(step+rest-1>ID) return 0;
	if(!rest) return 1;
	for(k=0;k<8;k++)
	{
		i=x+dx[k],j=y+dy[k];
		if(i<0||j<0||i>4||j>4) continue;
		swap(a[x][y],a[i][j]);
		if(dfs(step+1)) return 1;
		swap(a[x][y],a[i][j]);
	}
	return 0;
}

int main()
{
	cin>>t;
	while(t--)
	{
		for(i=0;i<5;i++) scanf("%s",a[i]);
		for(ID=1;ID<=15;ID++)
			if(dfs(0)) break;
		if(ID>15) puts("-1"); else cout<<ID<<endl;
	}
	return 0;
}