#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int d[210][210],mx[210],my[210],hx[210],hy[210],la[210],lb[210],link[210];
char a[210][210];
bool va[210],vb[210];
int n,m,p,h,temp,ans,i,j;

bool dfs(int x)
{
	va[x]=1;
	for(int y=1;y<=h;y++)
		if(!vb[y])
			if(!(la[x]+lb[y]-d[x][y]))
			{
				vb[y]=1;
				if(!link[y]||dfs(link[y]))
				{link[y]=x; return 1;}
			}
			else temp=min(temp,la[x]+lb[y]-d[x][y]);
	return 0;
}

int abso(int x)
{
	return x>0?x:-x;
}

int main()
{
	while(cin>>n>>m&&n)
	{
		for(i=0;i<n;i++)scanf("%s",a[i]);
		p=h=ans=0;
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
			{
				if(a[i][j]=='m'){mx[++p]=i; my[p]=j;}
				if(a[i][j]=='H'){hx[++h]=i; hy[h]=j;}
			}
		for(i=1;i<=p;i++){la[i]=-0x3fffffff; lb[i]=link[i]=0;}
		for(i=1;i<=p;i++)
			for(j=1;j<=h;j++)
				{
					d[i][j]=-abso(mx[i]-hx[j])-abso(my[i]-hy[j]);
					la[i]=max(la[i],d[i][j]);
				}
		for(i=1;i<=p;i++)
			while(1)
			{
				memset(va,0,sizeof(va));
				memset(vb,0,sizeof(vb));
				temp=0x3fffffff;
				if(dfs(i))break;
				for(j=1;j<=p;j++)
				{
					if(va[j])la[j]-=temp;
					if(vb[j])lb[j]+=temp;
				}
			}
		for(i=1;i<=h;i++) ans+=d[link[i]][i];
		cout<<-ans<<endl;
	}
	return 0;
}