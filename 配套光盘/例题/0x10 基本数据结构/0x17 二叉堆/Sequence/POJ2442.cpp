// Author: LiRe
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cctype>
#include <cstring>
using namespace std;

struct node{
	int p1, p2, i, j;
	bool flag;
	node(){};
	node(int a, int b, int c, int d, bool f) {
		p1 = a, p2 = b, i = c, j = d, flag = f;
	}
};

int A[103][2003];
int f[2003];
int n, m;

bool operator < (const node& a, const node& b) {
	return (a.i + a.j) > (b.i + b.j);
}

priority_queue<node> pq;

void merge(int k) {
	while(!pq.empty()) pq.pop();
	int qwq[2003], cnt = 0;
	pq.push(node(1, 1, f[1], A[k][1], 0));
	while(!pq.empty()) {
		node fr = pq.top();
		pq.pop();
		qwq[++cnt] = fr.i + fr.j;
		if(fr.p2 < m) pq.push(node(fr.p1, fr.p2 + 1, f[fr.p1], A[k][fr.p2 + 1], 1));
		if(!fr.flag && fr.p1 < m) pq.push(node(fr.p1 + 1, fr.p2, f[fr.p1 + 1], A[k][fr.p2], 0));
		if(cnt == m) break;
	}
	for(int i = 1; i <= m; ++i) f[i] = qwq[i];
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		while(!pq.empty()) pq.pop();
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) 
			for(int j = 1; j <= m; ++j)
				scanf("%d", &A[i][j]);
		for(int i = 1; i <= n; ++i) sort(A[i] + 1, A[i] + 1 + m);
		for(int i = 1; i <= m; ++i) f[i] = A[1][i];
		for(int k = 2; k <= n; ++k) merge(k);
		for(int i = 1; i <= m; ++i) printf("%d ", f[i]);
		cout<<endl;		
	}
	return 0;
}