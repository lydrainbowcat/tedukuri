// Author: LiRe
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
priority_queue<int> big;
priority_queue<int, vector<int>, greater<int> > small;

int main() {
	int T;
	scanf("%d", &T);
	int id, m, cnt, a, mid;
	while(T--) {
		while(!big.empty()) big.pop();
		while(!small.empty()) small.pop();
		scanf("%d%d", &id, &m);
		cnt = 1, mid = -0x3fffff;
		cout<<id<<" "<<(m + 1 >> 1)<<endl;
		for(int i = 1; i <= m; ++i) {
			scanf("%d", &a);
			if(big.empty()) {
				big.push(a);
				mid = a;
				cout<<a<<" ";
				continue;
			}
			if(a < mid) big.push(a);
			else small.push(a);
			if(((int)big.size() - (int)small.size()) > 1) {
				int t = big.top();
				big.pop();
				small.push(t);
			} else if(((int)small.size() - (int)big.size()) > 1) {
				int t = small.top();
				small.pop();
				big.push(t);
			}
			if(i & 1) {
				++cnt;
				if(big.size() > small.size()) mid = big.top();
				else mid = small.top();
				if(cnt % 10 == 0) cout<<mid<<endl;
				else cout<<mid<<" ";
			} else mid = (small.top() + big.top()) / 2;
		}
		if(cnt % 10 != 0) cout<<endl;
	} 
	return 0; 
}