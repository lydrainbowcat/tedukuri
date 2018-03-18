// 随机数据生成模板
#include<cstdlib>
#include<ctime>

int random(int n) {
    return (long long)rand() * rand() % n;
}

int main() {
    srand((unsigned)time(0));
    // ...具体内容...
}

// 实例：随机生成整数序列
// 不超过100000个绝对值在1000000000内的整数
int n = random(100000) + 1;
int m = 1000000000;
for (int i = 1; i <= n; i++) {
    a[i] = random(2 * m + 1) - m;
}

// 实例：随机生成区间列
for (int i = 1; i <= m; i++) {
    int l = random(n) + 1;
    int r = random(n) + 1;
    if (l > r) swap(l, r);
    printf("%d %d\n", l, r);
}

// 实例：随机生成树
for (int i = 2; i <= n; i++) {
    // 从 2~n 之间的每个点 i 向 1~i-1 之间的点随机连一条边
    int fa = random(i - 1) + 1;
    int val = random(1000000000) + 1;
    printf("%d %d %d\n", fa, i, val);
}

// 实例：随机生成图
// 无向图，连通，不含重边、自环
pair<int, int> e[1000005]; // 保存数据
map< pair<int, int>, bool > h; // 防止重边
// 先生成一棵树，保证连通
for (int i = 1; i < n; i++) {
    int fa = random(i) + 1;
    e[i] = make_pair(fa, i + 1);
    h[e[i]] = h[make_pair(i + 1, fa)] = 1;
}
// 再生成剩余的 m-n+1 条边
for (int i = n; i <= m; i++) {
    int x, y;
    do {
        x = random(n) + 1, y = random(n) + 1;
    } while (x == y || h[make_pair(x, y)]);
    e[i] = make_pair(x, y);
    h[e[i]] = h[make_pair(y, x)] = 1;
}
// 随机打乱，输出
random_shuffle(e + 1, e + m + 1);
for (int i = 1; i <= m; i++)
    printf("%d %d\n", e[i].first, e[i].second);


// Windows系统对拍程序
#include<cstdlib>
#include<cstdio>
#include<ctime>
int main() {
    for (int T = 1; T <= 10000; T++) {
        // 自行设定适当的路径
        system("C:\\random.exe");
        // 返回当前程序已经运行的CPU时间，windows下单位ms，类unix下单位s
        double st = clock();
        system("C:\\sol.exe");
        double ed = clock();
        system("C:\\bf.exe");
        if (system("fc C:\\data.out C:\\data.ans")) {
            puts("Wrong Answer");
            // 程序立即退出，此时data.in即为发生错误的数据，可人工演算、调试
            return 0;
        }
        else {
            printf("Accepted, 测试点 #%d, 用时 %.0lfms\n", T, ed - st);
        }
    }
}
