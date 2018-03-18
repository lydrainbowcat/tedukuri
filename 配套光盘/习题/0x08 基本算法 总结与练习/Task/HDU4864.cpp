#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;
const int u = 100010;
int n, m, cnt, x, y;
vector<int> a[110], b[110];
multiset<pair<int, int> > s;
multiset<pair<int, int> >::iterator it;
long long ans;

int main()
{
    while(cin>>n>>m)
    {
        for (int i = 0; i <= 100; i++)
        {
            a[i].clear();
            b[i].clear();
        }
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &x, &y);
            a[y].push_back(x);
        }
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &x, &y);
            b[y].push_back(x);
        }
        cnt = ans = 0;
        s.clear();
        for (int i = 0; i <= 100; i++)
        {
            for (int j = 0; j < b[i].size(); j++)
                s.insert(make_pair(b[i][j], 500 * b[i][j] + 2 * i));
            sort(a[i].begin(), a[i].end());
            for (int j = 0; j < a[i].size(); j++)
            {
                it = s.upper_bound(make_pair(a[i][j], 1 << 30));
                if (it == s.begin()) continue;
                it--;
                cnt++;
                ans += it->second;
                s.erase(it);
            }
        }
        cout << cnt << ' ' << ans << endl;
    }
}

