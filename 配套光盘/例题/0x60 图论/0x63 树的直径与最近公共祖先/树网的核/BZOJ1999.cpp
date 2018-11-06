#include<bits/stdc++.h>
using namespace std;
const int SIZE = 500010;
int head[SIZE],ver[SIZE*2],Next[SIZE*2],edge[SIZE*2];
int fa[SIZE],f[SIZE],d[SIZE],a[SIZE]; 
int n,s,m,tot,l,r,x,y,z,temp,ans;
bool v[SIZE];

void add(int x,int y,int z) {
	ver[++tot]=y,Next[tot]=head[x],edge[tot]=z,head[x]=tot;
}

void dfs(int x){
	for(int i=head[x];i;i=Next[i]){
		if(ver[i]!=fa[x]){
			fa[ver[i]]=x;
			d[ver[i]]=d[x]+edge[i];
			dfs(ver[i]);
		}
	}
}

void diameter(){
	dfs(1);
	x=1;
	for(int i=2;i<=n;i++)
		if(d[i]>d[x])x=i;
	d[x]=0;
	memset(fa,0,sizeof(fa));
	dfs(x);
	y=1;
	for(int i=2;i<=n;i++)
		if(d[i]>d[y])y=i;
	while(y!=x){
		v[y]=true;
		a[++m]=y;
		y=fa[y];
	}
	v[x]=1;
	a[++m]=x;
}

void treedp(int x){
	v[x]=true;
	for(int i=head[x];i;i=Next[i]){
		if(!v[ver[i]]){
			treedp(ver[i]);
			f[x]=max(f[x],f[ver[i]]+edge[i]);
		}
	}
}

int main(){
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n-1;i++){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);add(y,x,z);
	}
	diameter();
	for(int i=1;i<=m;i++)treedp(a[i]);
	int j=m;
	ans=0x7fffffff;
	for(int i=1;i<=m;i++)temp=max(temp,f[a[i]]);
	for(int i=m;i>=1;i--){
		while(j>=1&&d[a[j]]-d[a[i]]<=s)j--;
		ans=min(ans,max(temp,max(d[a[i]],d[a[1]]-d[a[j+1]])));
	}
	printf("%d\n",ans);
	return 0;
}
