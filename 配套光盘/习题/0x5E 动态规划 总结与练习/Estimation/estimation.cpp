#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <cstring>
#include <algorithm>
using namespace std;
 
int arr[2010];
int dist[2010][2010]; // precompute costs per segments
 
int dp[2010][2010]; // stores dp values
int main() {
        int n, maxk;
        while (cin >> n >> maxk && n) {
                maxk = min(maxk, n); // in case k > n
                memset(dp, 127, sizeof(dp)); // fill dp with approximately 2 ^ 31 - 1
                int inf = dp[0][0];
                for (int i = 0; i < n; i++) {
                        cin >> arr[i];
                }
                for (int i = 0; i < n; i++) {
                        priority_queue<int> lower;
                        priority_queue<int, vector<int>, greater<int> > upper; // maintain lower and upper halves of the median
                        int sumdif = 0; // sum of upper - sum of lower
                        int cnt = 0;
                        for (int j = i; j < n; j++) {
                                if (lower.empty() || arr[j] <= lower.top()) {
                                        lower.push(arr[j]);
                                        sumdif -= arr[j];
                                } else {
                                        upper.push(arr[j]);
                                        sumdif += arr[j];
                                }
                                cnt++;
                                int lhalf = cnt / 2, uhalf = cnt - lhalf; // lhalf = floor(cnt / 2), uhalf = ceiling(cnt / 2)
                                if (lower.size() > lhalf) {
                                        upper.push(lower.top());
                                        sumdif += lower.top() * 2;
                                        lower.pop();
                                }
                                if (upper.size() > uhalf) {
                                        lower.push(upper.top());
                                        sumdif -= upper.top() * 2;
                                        upper.pop();
                                }
                                while (lower.size() && upper.size() && upper.top() < lower.top()) { // swap values from lower and upper until balanced out
                                        int t = lower.top(); lower.pop();
                                        int u = upper.top(); upper.pop();
                                        lower.push(u);
                                        sumdif -= u * 2;
                                        upper.push(t);
                                        sumdif += t * 2;
                                }
                                int curd = sumdif;
                                if (upper.size() > lower.size()) { // if the size of the segment is odd, do not include the median in the sum
                                        curd -= upper.top();
                                }
                                dist[i][j + 1] = abs(curd);
                        }
                }
                dp[0][0] = 0; // finally calculate dp values
                for (int i = 0; i < maxk; i++) {
                        for (int j = 0; j < n; j++) {
                                if (dp[i][j] == inf) continue;
                                for (int k = j + 1; k <= n; k++) {
                                        dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + dist[j][k]); // attempt to add segment from j to k
                                }
                        }
                }
                cout << dp[maxk][n] << endl;
        }
}