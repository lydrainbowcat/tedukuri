#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
struct rec{double x;int to,e;}a[210],b[210];
int c[110][2],f[210],n,i,j,k,x,y,z,data;
double len,ans,x1,y1,x2,y2;

int cmp(const void *a,const void *b)
{
	return ((rec *)a)->x>((rec *)b)->x?1:-1;
}

int main()
{
	while(cin>>n&&n)
	{
		for(i=1;i<=n;i++) 
		{
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			a[i*2-1].x=x1; a[i*2-1].to=i; a[i*2-1].e=1;
			a[i*2].x=x2; a[i*2].to=i; a[i*2].e=-1;
			b[i*2-1].x=y1; b[i*2-1].to=i; b[i*2-1].e=0;
			b[i*2].x=y2; b[i*2].to=i; b[i*2].e=1;
		}
		qsort(b+1,2*n,sizeof(b[1]),cmp);
		qsort(a+1,2*n,sizeof(a[1]),cmp);
		for(i=1;i<=2*n;i++) c[b[i].to][b[i].e]=i;
		memset(f,0,sizeof(f));
		for(ans=0,i=1;i<2*n;i++)
		{
			j=a[i].to; x=c[j][0]; y=c[j][1]; z=a[i].e;
			for(k=x;k<y;k++) f[k]+=z;
			for(len=0,k=1;k<2*n;k++) if(f[k]) len+=b[k+1].x-b[k].x;
			ans+=len*(a[i+1].x-a[i].x);
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n",++data,ans);
	}
	return 0;
}