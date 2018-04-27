/**
 * @Author:      H S-J
 * @DateTime:    2018-04-18 20:10:21
 * @Description: 
 */
#include <iostream>
#include <cstring>
using namespace std;
#define MST(a, b) memset(a, b, sizeof(a));
#define CLR(a) MST(a, 0);
#define rep(x, y, z) for (int x = y; x < z; ++x)
const int INF = 0x3f3f3f3f;
int dp[101][77][77];
int sg[101];
int n, m, idx;
int s[77]; //合法摆放的集合
int cnt0[77]; //合法摆放方案的具体摆放个数, 即二进制下1的个数
int get_one(int x) {
	int cnt = 0;
	while(x) x &= (x-1), ++cnt;
	return cnt;
}
bool ok(int x) {
	// 相邻两个P之间要有两个H
	if(x & (x << 1)) return false;
	if(x & (x << 2)) return false;
	return true;
}
void init() {
	idx = 0;
	int end = 1 << m;
	rep(i, 0, end) if(ok(i)) {
		// s保存合法方案的集合
		s[idx] = i;
		// cnt0保存合法方案的摆放个数, 二进制位1的个数
		cnt0[idx++] = get_one(i);
	}
}
bool valid(int i, int x) {
	if(sg[i] & x) return false;
	return true;
}
int solve() {
	int ans = 0;
	MST(dp, -1);
	dp[0][0][0] = 0;
	rep(j, 0, idx) if(valid(1, s[j])) {
		dp[1][j][0] = cnt0[j];
		// 考虑n==1情况
		ans = max(ans, dp[1][j][0]);
	}
	rep(i, 2, n+1) {
		// valid()函数判断, 第i行, 用方案s[j]是否合法
		rep(j, 0, idx) if(valid(i, s[j])) {
			// i行跟i-1行的方案, 满足, 互相炸不到对方
			rep(k, 0, idx) if(valid(i-1, s[k]) && (s[j]&s[k])==0) {
				int last = 0;
				// i-2行同上
				rep(l, 0, idx) if(dp[i-1][k][l] != -1 && (s[l]&s[j])==0 && valid(i-2, s[l])) {
					last = max(last, dp[i-1][k][l]);
				}
				dp[i][j][k] = max(dp[i][j][k], last + cnt0[j]);
				if(i == n) ans = max(ans, dp[i][j][k]);
			}
		}
	}
	return ans;
}
int main(int argc, char const *argv[]) {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n+1) rep(j, 0, m) {
		char tmp; cin >> tmp;
		if(tmp == 'H') sg[i] |= (1 << (m-1-j));
	}
	init();
	cout << solve() << endl;
	return 0;
}