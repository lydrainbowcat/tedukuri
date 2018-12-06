//Author:XuHt
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 106;
int n, a[N], len, cnt;
bool v[N];

bool dfs(int stick, int cab, int last) {
    if (stick > cnt) return 1;
    if (cab == len) return dfs(stick + 1, 0, 1);
    int fail = 0;
    for (int i = last; i <= n; i++)
        if (!v[i] && cab + a[i] <= len && fail != a[i]) {
            v[i] = 1;
            if (dfs(stick, cab + a[i], i + 1)) return 1;
            fail = a[i];
            v[i] = 0;
            if (!cab || cab + a[i] == len) return 0;
        }
    return 0;
}

int main() {
    while (cin >> n && n) {
        int sum = 0, val = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum += a[i];
            val = max(val, a[i]);
        }
        sort(a + 1, a + n + 1);
        reverse(a + 1, a + n + 1);
        for (len = val; len <= sum; len++) {
            if (sum % len) continue;
            cnt = sum / len;
            memset(v, 0, sizeof(v));
            if (dfs(1, 0, 1)) break;
        }
        cout << len << endl;
    }
    return 0;
}
