#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
int n;
int s[10][10];
int f[20][10][10][10][10];
double ave;
inline int calc(int a,int b,int c,int d)
{return (s[c][d]-s[a-1][d]-s[c][b-1]+s[a-1][b-1])*(s[c][d]-s[a-1][d]-s[c][b-1]+s[a-1][b-1]);}
int main()
{
	memset(f,0x3f,sizeof f);
	scanf("%d",&n);
	for(int i=1;i<=8;i++)
		for(int j=1;j<=8;j++)
		{
			int x;
			scanf("%d",&x);
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+x;
		}
	for(int x1=1;x1<=8;x1++)
			for(int y1=1;y1<=8;y1++)
				for(int x2=x1;x2<=8;x2++)
					for(int y2=y1;y2<=8;y2++)
						f[0][x1][y1][x2][y2]=calc(x1,y1,x2,y2);
	for(int t=1;t<n;t++)
		for(int x1=1;x1<=8;x1++)
			for(int y1=1;y1<=8;y1++)
				for(int x2=x1+1;x2<=8;x2++)
					for(int y2=y1+1;y2<=8;y2++)
					{
						for(int i=x1;i<x2;i++)
							f[t][x1][y1][x2][y2]=min(f[t][x1][y1][x2][y2],min(f[t-1][x1][y1][i][y2]+calc(i+1,y1,x2,y2),f[t-1][i+1][y1][x2][y2]+calc(x1,y1,i,y2)));
						for(int i=y1;i<y2;i++)
							f[t][x1][y1][x2][y2]=min(f[t][x1][y1][x2][y2],min(f[t-1][x1][y1][x2][i]+calc(x1,i+1,x2,y2),f[t-1][x1][i+1][x2][y2]+calc(x1,y1,x2,i)));
					}
	ave=double(s[8][8])/n;
	double ans=((double)(f[n-1][1][1][8][8]-2*ave*s[8][8]))/n+ave*ave;
	printf("%.3lf\n",sqrt(ans));
	return 0;
}