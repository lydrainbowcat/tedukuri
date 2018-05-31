#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cmath>
#include<cstdlib>
using namespace std;
const int u=100010;
int h[u], g[3], n, m, p;
struct rec{int x,y;};
set<rec> s;
set<rec>::iterator it,lt,rt;

bool operator <(rec a,rec b)
{
	return a.y<b.y;
}
bool cmp(int a,int b,int i)
{
	return abs(h[a]-h[i])<abs(h[b]-h[i])||abs(h[a]-h[i])==abs(h[b]-h[i])&&h[a]<h[b];
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&h[i]);
	for(int i=1;i<=n;i++)
	{
		rec pr; pr.x=i, pr.y=h[i];
		s.insert(pr);
		it=s.find(pr);
		
		lt=it, rt=it, m=0;
		if(lt!=s.begin()) lt--,g[++m]=lt->x;
		if(rt++,rt!=s.end()) g[++m]=rt->x;
		
		if (i>=2) {
			if (m<2 || cmp(g[1], g[2], i)) p=g[1]; else p=g[2];
			printf("%d %d\n", abs(h[i]-h[p]), p);
		}
	}
	return 0;
}
