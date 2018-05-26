// Author: LiRe
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
struct node{
	long long w, h;
	node(){};
	node(long long a, long long b) {
		w = a, h = b;
	}
};

bool operator < (const node& a, const node& b) {
	return a.w == b.w ? a.h > b.h : a.w > b.w;
}

long long n, k, t, ans, tmp, ta;
priority_queue<node> pq;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>k;
	for(int i = 1; i <= n; ++i) {
		cin>>t;
		pq.push(node(t, 1));
	}
	while((pq.size() - 1) % (k - 1) != 0) 
		pq.push(node(0, 1));
	while(pq.size() >= k) {
		ta = 0; tmp = -1;
		for(int i = 1; i <= k; ++i) {
			ta += pq.top().w; 
			tmp = max(tmp, pq.top().h);
			pq.pop();
		}
		pq.push(node(ta, tmp + 1));
		ans += ta;
	}
	cout<<ans<<endl<<pq.top().h - 1<<endl;
	return 0;
}