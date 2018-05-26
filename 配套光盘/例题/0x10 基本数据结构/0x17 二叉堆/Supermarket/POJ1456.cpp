// Author: LiRe
#include <cstdio>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
typedef long long LL;

inline void read(int& x) {
	x = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
} 

struct node{
	int pro, dat;
}th[10003];

bool cmp(node a, node b) {
	return a.dat < b.dat;
}

priority_queue<node> pq;

bool operator < (const node& a, const node& b) {
	return a.pro > b.pro;
}

int main() {
	int n;
	while(cin>>n) {
		for(int i = 1; i <= n; ++i) read(th[i].pro), read(th[i].dat);
		sort(th + 1, th + n + 1, cmp);
		for(int i = 1; i <= n; ++i) {
			if(pq.empty()) pq.push(th[i]);
			else if(pq.size() < th[i].dat) pq.push(th[i]);
			else if(pq.top().pro < th[i].pro) {
				pq.pop();
				pq.push(th[i]);
			}
		}
		LL ans = 0;
		while(!pq.empty()) {
			ans += pq.top().pro;
			pq.pop();
		}
		cout<<ans<<endl;
	}
	return 0;
}