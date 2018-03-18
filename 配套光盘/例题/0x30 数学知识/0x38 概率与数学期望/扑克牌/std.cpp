#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
double f[15][15][15][15][5][5],ans;
bool v[15][15][15][15][5][5];
int C,D,H,S,t,T;

double dp(int a,int b,int c,int d,int p,int q)
{
	if(v[a][b][c][d][p][q]) return f[a][b][c][d][p][q];
	v[a][b][c][d][p][q]=1;
	double& ans=f[a][b][c][d][p][q]; ans=0;
	int x=a,y=b,z=c,w=d;
	if(p==1) x++; if(p==2) y++; if(p==3) z++; if(p==4) w++;
	if(q==1) x++; if(q==2) y++; if(q==3) z++; if(q==4) w++;
	if(x>=C&&y>=D&&z>=H&&w>=S) return 0;
	int cnt=54-x-y-z-w;
	if(cnt<=0) return ans=1e10;
	if(a<13) ans+=dp(a+1,b,c,d,p,q)*(13-a)/cnt;
	if(b<13) ans+=dp(a,b+1,c,d,p,q)*(13-b)/cnt;
	if(c<13) ans+=dp(a,b,c+1,d,p,q)*(13-c)/cnt;
	if(d<13) ans+=dp(a,b,c,d+1,p,q)*(13-d)/cnt;
	if(p==0)
	{
		double temp=dp(a,b,c,d,1,q);
		temp=min(temp,dp(a,b,c,d,2,q));
		temp=min(temp,dp(a,b,c,d,3,q));
		temp=min(temp,dp(a,b,c,d,4,q));
		ans+=temp/cnt;
	}
	if(q==0)
	{
		double temp=dp(a,b,c,d,p,1);
		temp=min(temp,dp(a,b,c,d,p,2));
		temp=min(temp,dp(a,b,c,d,p,3));
		temp=min(temp,dp(a,b,c,d,p,4));
		ans+=temp/cnt;
	}
	return ++ans;
}

int main()
{
	cin>>C>>D>>H>>S;
	ans=dp(0,0,0,0,0,0);
	if(ans>100) puts("-1.000"); else printf("%.3f\n",ans); 
	return 0;
}
