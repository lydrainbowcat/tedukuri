#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

FILE   *in = freopen ("reserve.in", "r", stdin);
FILE   *out = freopen ("reserve.out", "w", stdout);

const int maxn = 50000 + 10;

struct T {
    int     time;
    int     index;
    bool    flag;
}       A[2 * maxn];

bool operator < (const T & B, const T & C) {
    if (B.time != C.time)        return B.time < C.time;
    else if (B.index == C.index) return B.flag;
    else if (B.flag != C.flag)   return B.flag;
    else                         return B.index < C.index;
}

int     W[maxn];
int     Free[maxn];

int main () {
    int     n;
    scanf ("%d", &n);
    for (int i = 0; i < n; ++i) {
	scanf ("%d %d", &A[2 * i].time, &A[2 * i + 1].time);
	A[2*i].index = A[2*i + 1].index = i;
	A[2*i].flag = true;
	A[2*i + 1].flag = false;
    }
    sort (&A[0], &A[2*n]);

    int     number = 0;
    int     m = 0;
    for (int i = 0; i < 2 * n; ++i)
	if (!A[i].flag)
	    Free[m++] = W[A[i].index];
	else {
	    if (m == 0) W[A[i].index] = ++number;
	    else        W[A[i].index] = Free[--m];
	}
    printf ("%d\n", number);
    for (int i = 0; i < n; ++i)
	printf ("%d\n", W[i]);
    return 0;
}