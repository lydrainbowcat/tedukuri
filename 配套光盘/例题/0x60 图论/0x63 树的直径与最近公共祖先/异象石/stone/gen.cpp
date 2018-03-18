#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int fa[100010],cnt,v[100010],n,m,x,y;


int get(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}

int main()
{
	freopen("stone.in","w",stdout);
	srand((unsigned)time(0));
	cin>>n>>m;
	cout<<n<<endl;
	//for(int i=1;i<n;i++) printf("%d %d %d\n",i,i+1,rand()*rand()%100000);
	//for(int i=1;i<n;i++) printf("%d %d %d\n",i,n,rand()*rand()%1000000);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<n;i++)
	{
		do{x=rand()*rand()%n+1,y=rand()*rand()%n+1;}while(get(x)==get(y));
		fa[get(x)]=get(y);
		printf("%d %d %d\n",x,y,rand()*rand()%1000000000+1);
	}
	cout<<m<<endl;
	for(int i=1;i<=m/2;i++)
	{
		int k=rand()%5;
		if(k<3)
		{
			if(cnt==n) k=4;
			else{
			do{x=rand()*rand()%n+1;}while(v[x]);
			v[x]=1,cnt++;
			printf("+ %d\n",x);}
		}
		if(k==3)
		{
			if(!cnt) k=4;
			else{
			do{x=rand()*rand()%n+1;}while(!v[x]);
			v[x]=0,cnt--;
			printf("- %d\n",x);}
		}
		if(k==4)
		{
			puts("?");
		}
	}
	for(int i=m/2+1;i<=m;i++)
	{
		int k=rand()%5;
		if(k==0)
		{
			if(cnt==n) k=4;
			else{
			do{x=rand()*rand()%n+1;}while(v[x]);
			v[x]=1,cnt++;
			printf("+ %d\n",x);}
		}
		if(k==1||k==2)
		{
			if(!cnt) k=4;
			else{
			do{x=rand()*rand()%n+1;}while(!v[x]);
			v[x]=0,cnt--;
			printf("- %d\n",x);}
		}
		if(k>2)
		{
			puts("?");
		}
	}
}
