#define FILEIO

#define INPUT "dandelion.in"
#define OUTPUT "dandelion.out"

#include <set>
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cmath>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 40013;
	const int MAXM = 36;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int n, m, a[MAXN], cnt = 0, p, belong[MAXN], t, fim[MAXN];
	set<int> S; map<int, int> M;

	inline void Input(void) {
		n = ScanInt(), m = ScanInt(), p = pow(n, 0.666666666666), t = n / p; if (n % p != 0) t++;
		for (int i = 1; i <= n; i++) S.insert(a[i] = ScanInt());
		foreach(it, S) M[*it] = ++cnt;
		for (int i = 1; i <= n; i++) fim[M[a[i]]] = a[i], a[i] = M[a[i]];
	}

	inline void Update(int t, int v, int &Max, int &pos) {
		if (v == Max && t < pos) pos = t;
		if (v > Max) pos = t, Max = v;
	}

	struct Node {
		int c[MAXN], pos, Max;
		inline void operator +=(const int t) {
			c[t]++;
			Update(t, c[t], Max, pos);
		}
		inline void operator -=(const int t) {
			c[t]--;
		}
	}f[MAXM][MAXM];

	int C[MAXM][MAXN];

	inline void Init(void) {
		for (int i = 1; i <= n; i++) {
			if ((i - 1) % p == 0) belong[i] = belong[i - 1] + 1; else belong[i] = belong[i - 1];
			C[belong[i]][a[i]]++;
		}
		for (int i = 1; i <= t; i++) {
			for (int j = i; j <= t; j++) {
				for (int k = 1; k <= cnt; k++) 
					f[i][j].c[k] = f[i][j - 1].c[k] + C[j][k];
				for (int k = 1; k <= cnt; k++) 
					Update(k, f[i][j].c[k], f[i][j].Max, f[i][j].pos);
			}
		}
	}

	int hash[MAXN];

	inline int Cal(int l, int r) {
		int L = belong[l], R = belong[r];
		if (L == R) {
			int Max = 0, pos = 0;
			for (int i = l; i <= r; i++) {
				hash[a[i]]++;
				Update(a[i], hash[a[i]], Max, pos);
			}
			for (int i = l; i <= r; i++) hash[a[i]]--;
			return fim[pos];
		}
		if (belong[l] == belong[l - 1]) L++;
		if (belong[r] == belong[r + 1]) R--;
		int b = f[L][R].pos, u = f[L][R].Max;
		for (int i = l; belong[i] == belong[i - 1]; i++) f[L][R] += a[i];
		for (int i = r; belong[i] == belong[i + 1]; i--) f[L][R] += a[i];
		int ret = fim[f[L][R].pos];
		for (int i = l; belong[i] == belong[i - 1]; i++) f[L][R] -= a[i];
		for (int i = r; belong[i] == belong[i + 1]; i--) f[L][R] -= a[i];
		f[L][R].pos = b, f[L][R].Max = u;
		return ret;
	}

	inline void solve(void) {
		Input();
		Init();
		int x = 0;
		for (int i = 1; i <= m; i++) {
			int l = ScanInt(), r = ScanInt();
			l = (l + x - 1) % n + 1, r = (r + x - 1) % n + 1;
			if (l > r) swap(l, r);
//			fprintf(stderr, "%d %d\n", l, r);
			printf("%d\n", x = Cal(l, r));
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

