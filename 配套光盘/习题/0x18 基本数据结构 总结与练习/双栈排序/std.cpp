// Author: yxc
// Update: lyd
// https://www.acwing.com/solution/acwing/content/3710/
#include <iostream>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;

const int N = 1010;

int n;
int a[N], f[N];
int color[N];
bool g[N][N];

bool dfs(int u, int c)
{
	color[u] = c;
	for (int i = 1; i <= n; i++)
		if (g[u][i])
		{
			if (color[i] == c) return false;
			if (color[i] == -1 && !dfs(i, !c)) return false;
		}

	return true;
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		f[n + 1] = n + 1;
		memset(g, false, sizeof g);
		for (int i = n; i; i--) f[i] = min(f[i + 1], a[i]);

		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				if (a[i] < a[j] && f[j + 1] < a[i])
					g[i][j] = g[j][i] = true;

		memset(color, -1, sizeof color);

		bool flag = true;
		for (int i = 1; i <= n; i++)
			if (color[i] == -1 && !dfs(i, 0))
			{
				flag = false;
				break;
			}

		if (!flag)
		{
			cout << 0 << endl;
			continue;
		}

		stack<int> stk1, stk2;

		int now = 1;
		for (int i = 1; i <= n; i++)
		{
			if (color[i] == 0)
			{
				// 要入第一个栈了，第一个栈该出的现在必须要出掉
				// 为了使字典序最小，第二个栈可以再等等
				while (stk1.size() && stk1.top() == now)
				{
					stk1.pop();
					cout << "b ";
					now++;
				}
				stk1.push(a[i]);
				cout << "a ";
			}
			else
			{
				// 要入第二个栈了，第二个栈该出的现在必须要出掉
				// 然而由于b比c字典序小，第一个栈可以出的也应该出掉
				while (true)
					if (stk1.size() && stk1.top() == now)
					{
						stk1.pop();
						cout << "b ";
						now++;
					}
					else if (stk2.size() && stk2.top() == now)
					{
						stk2.pop();
						cout << "d ";
						now++;
					}
					else break;
                stk2.push(a[i]);
                cout << "c ";
			}

		}
		// 最后出栈剩余的
		while (true)
			if (stk1.size() && stk1.top() == now)
			{
				stk1.pop();
				cout << "b ";
				now++;
			}
			else if (stk2.size() && stk2.top() == now)
			{
				stk2.pop();
				cout << "d ";
				now++;
			}
			else break;
		cout << endl;
	}
	return 0;
}