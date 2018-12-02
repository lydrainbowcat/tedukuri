//Author:XuHt
#include <map>
#include <cstdio>
#include <vector>
#include <iostream>
#define ull unsigned long long
using namespace std;
const int N = 1006, P = 13331;
int m, n, a, b, q;
char s[N][N], qs[N][N];
bool ans[N];
ull num[N][N], qnum[N][N], p[N*N];
map<ull, vector<int> > qans;

ull get() {
	for (int i = 1; i <= a; i++) {
		scanf("%s", qs[i] + 1);
		for (int j = 1; j <= b; j++)
			qnum[i][j] = qnum[i][j-1] * P + qs[i][j];
	}
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
			qnum[i][j] += qnum[i-1][j] * p[n];
	return qnum[a][b];
}

int main() {
	cin >> m >> n >> a >> b;
	p[0] = 1;
	for (int i = 1; i < N * N; i++) p[i] = p[i-1] * P;
	for (int i = 1; i <= m; i++) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= n; j++)
			num[i][j] = num[i][j-1] * P + s[i][j];
	}
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			num[i][j] += num[i-1][j] * p[n];
	cin >> q;
	for (int i = 1; i <= q; i++) qans[get()].push_back(i);
	for (int i = a; i <= m; i++)
		for (int j = b; j <= n; j++) {
			ull k = num[i][j] - num[i-a][j] * p[a*n] - num[i][j-b] * p[b] + num[i-a][j-b] * p[a*n+b];
			if (qans.find(k) != qans.end())
				for (unsigned int i = 0; i < qans[k].size(); i++)
					ans[qans[k][i]] = 1;
		}
	for (int i = 1; i <= q; i++) cout << (ans[i] ? "1" : "0") << endl;
	return 0;
}
