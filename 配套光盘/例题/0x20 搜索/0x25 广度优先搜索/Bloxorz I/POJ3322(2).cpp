#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct poi{
	int x,y,z;
	poi(){}
	poi(int x_,int y_,int z_) {x=x_,y=y_,z=z_;}
};
//0:立着，1:竖着躺，上半部分在(x,y)，2:横着躺，左半部分(x,y) 
const int dx[3][4]={{-2,0,1,0},{-1,0,2,0},{-1,0,1,0}};
const int dy[3][4]={{0,-2,0,1},{0,-1,0,1},{0,-1,0,2}};
const int dz[3][4]={{1,2,1,2},{0,1,0,1},{2,0,2,0}};
char a[510][510];
int n,m;
int d[510][510][3];
queue<poi> q;

bool in(int x,int y) {
	return x>=1&&x<=n&&y>=1&&y<=m;
}

bool valid(int x,int y,int z) {
	if(!in(x,y)||a[x][y]=='#') return 0;
	if(z==1&&(!in(x+1,y)||a[x+1][y]=='#')) return 0;
	if(z==2&&(!in(x,y+1)||a[x][y+1]=='#')) return 0;
	if(z==0&&a[x][y]=='E') return 0;
	return 1;
}

int bfs(int sx,int sy,int sz,int ex,int ey) {
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<3;k++)
				d[i][j][k]=-1;
	d[sx][sy][sz]=0;
	while(q.size()) q.pop();
	q.push(poi(sx,sy,sz));
	while(q.size()) {
		poi now=q.front(); q.pop();
		//cout<<now.x<<' '<<now.y<<' '<<now.z<<endl;
		for(int i=0;i<4;i++) {
			poi next=poi(now.x+dx[now.z][i],now.y+dy[now.z][i],dz[now.z][i]);
			if(!valid(next.x,next.y,next.z)) continue;
			if(d[next.x][next.y][next.z]==-1) {
				d[next.x][next.y][next.z]=d[now.x][now.y][now.z]+1;
				q.push(next);
				if(next.x==ex&&next.y==ey&&next.z==0) return d[next.x][next.y][next.z];
			}
		}
	}
	return -1;
}
// +1 两段性、单调性，第一次终点入队时，最优解 

int main() {
	while(cin>>n>>m&&n) {
		for(int i=1;i<=n;i++)
			scanf("%s",a[i]+1);
		int sx,sy,sz,ex,ey;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(a[i][j]=='X') {
					sx=i,sy=j,sz=0,a[i][j]='.';
					if(i<n&&a[i+1][j]=='X') sz=1,a[i+1][j]='.';
					if(j<m&&a[i][j+1]=='X') sz=2,a[i][j+1]='.';
				}
				else if(a[i][j]=='O') ex=i,ey=j,a[i][j]='.';
		int ans=bfs(sx,sy,sz,ex,ey);
		if(ans==-1) puts("Impossible"); else cout<<ans<<endl;
	}
}