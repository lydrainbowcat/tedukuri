#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int u=1000010,inf=1<<30;
int a[u][2],v[u],l[u],r[u],c[u][2],d[u][2],q[2],n,m,tot,ans,root,i,z;

void insert(int &p,int dep,int k)
{
	if(!p) {p=k; c[p][0]=d[p][0]=a[k][0]; c[p][1]=d[p][1]=a[k][1]; return;}
	if(a[k][dep&1]<a[p][dep&1]) insert(l[p],dep+1,k); else insert(r[p],dep+1,k);
	c[p][0]=min(c[p][0],a[k][0]),d[p][0]=max(d[p][0],a[k][0]);
	c[p][1]=min(c[p][1],a[k][1]),d[p][1]=max(d[p][1],a[k][1]);
}

inline int dis(int k)
{
	return abs(a[k][0]-q[0])+abs(a[k][1]-q[1]);
}
inline int dis(int k,int dep)
{
	return min(abs(c[k][dep]-q[dep]),abs(d[k][dep]-q[dep]))+max(c[k][dep^1]-q[dep^1],0)+max(q[dep^1]-d[k][dep^1],0);
}

void ask(int p,int dep)
{
	if(!p) return;
	v[p]=tot;
	if(dis(ans)>dis(p)) ans=p;
	if(q[dep&1]<a[p][dep&1])
	{
		ask(l[p],dep+1);
		if(v[r[p]]!=tot&&dis(r[p],dep&1)<dis(ans)) ask(r[p],dep+1);
	}
	else{
		ask(r[p],dep+1);
		if(v[l[p]]!=tot&&dis(l[p],dep&1)<dis(ans)) ask(l[p],dep+1);
	}
}

int main()
{
	freopen("angel.in","r",stdin);
	freopen("angel.out","w",stdout);
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i][0],&a[i][1]);
		insert(root,1,i);
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&z,&q[0],&q[1]);
		if(z==1) a[++n][0]=q[0],a[n][1]=q[1],insert(root,1,n);
		else ans=1,tot++,ask(root,1),printf("%d\n",dis(ans));
	}
	//system("pause");
	return 0;
}
