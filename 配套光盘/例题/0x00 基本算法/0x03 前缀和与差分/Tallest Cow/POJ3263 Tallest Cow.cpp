//Author:XuHt
#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
map<pair<int, int>, bool> v;
const int N = 10006;
int s[N];

int main() {
    int n, p, h, t;
    cin >> n >> p >> h >> t;
    memset(s, 0, sizeof(s));
    while (t--) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a > b) swap(a, b);
        if (v[make_pair(a, b)]) continue;
        s[a+1]--;
        s[b]++;
        v[make_pair(a, b)] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += s[i];
        printf("%d\n", h + ans);
    }
    return 0;
}
