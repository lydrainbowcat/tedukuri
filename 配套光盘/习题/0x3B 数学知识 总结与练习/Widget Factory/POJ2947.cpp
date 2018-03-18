#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[310],b[310],c[310][310],n,m,t,i,j,k,l,x,y;
char s[5],e[5];

int calc(char s[5])
{
	if(s[0]=='M') return 1;
	if(s[0]=='T'&&s[1]=='U') return 2;
	if(s[0]=='W') return 3;
	if(s[0]=='T'&&s[1]=='H') return 4;
	if(s[0]=='F') return 5;
	if(s[0]=='S'&&s[1]=='A') return 6;
	return 7;
}

void solve()
{
	i=j=1;
	while(i<=m&&j<=n)
	{
		for(l=i;l<=m;l++) if(c[l][j]) break;
		if(l>m) {j++; continue;}
		for(k=j;k<=n;k++) swap(c[i][k],c[l][k]);
		swap(b[i],b[l]);
		x=c[i][j];
		for(k=i+1;k<=m;k++)
		{
			y=c[k][j];
			for(l=j;l<=n;l++)
				c[k][l]=(c[k][l]*x-c[i][l]*y)%7;
			b[k]=(b[k]*x-b[i]*y)%7;
		}
		i++,j++;
	}
	for(k=i;k<=m;k++)
		if(b[k]) {puts("Inconsistent data."); return;}
	if(i!=j||j<=n) {puts("Multiple solutions."); return;}
	for(i--,j--;i;i--,j--)
	{
		for(l=0,k=j+1;k<=n;k++) l+=c[i][k]*a[k];
		for(k=3;k<=9;k++)
			if((c[i][j]*k%7+7)%7==((b[i]-l)%7+7)%7) a[i]=k;
	}
	for(i=1;i<n;i++) printf("%d ",a[i]);
	cout<<a[i]<<endl;
}

int main()
{
	while(cin>>n>>m&&n)
	{
		memset(c,0,sizeof(c)); 
		for(i=1;i<=m;i++)
		{
			scanf("%d%s%s",&t,s,e);
			b[i]=calc(e)-calc(s)+1;
			for(j=1;j<=t;j++)
			{
				scanf("%d",&x);
				c[i][x]++;
			}
			for(j=1;j<=n;j++) c[i][j]%=7;
		}
		solve();
	}
	return 0;
}