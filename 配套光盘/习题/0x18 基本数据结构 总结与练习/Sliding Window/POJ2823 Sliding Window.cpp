//Author:XuHt
//C++ AC only
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1000006, INF = 0x3f3f3f3f;
int maxa[N], maxt[N], maxl = 0, maxr = 1, ansmax[N];
int mina[N], mint[N], minl = 0, minr = 1, ansmin[N];

int main() {
	int n, k;
	cin >> n >> k;
	maxa[0] = INF;
	mina[0] = -INF;
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		while (maxt[maxl] <= i - k && maxl < maxr) maxl++;
		while (mint[minl] <= i - k && minl < minr) minl++;
		while (maxa[maxr-1] <= a && maxl < maxr) maxr--;
		while (mina[minr-1] >= a && minl < minr) minr--;
		maxa[maxr] = mina[minr] = a;
		maxt[maxr++] = mint[minr++] = i;
		ansmax[i] = maxa[maxl];
		ansmin[i] = mina[minl];
	}
	for (int i = k; i < n; i++) printf("%d ", ansmin[i]);
	printf("%d\n", ansmin[n]);
	for (int i = k; i < n; i++) printf("%d ", ansmax[i]);
	printf("%d\n", ansmax[n]);
	return 0;
}
