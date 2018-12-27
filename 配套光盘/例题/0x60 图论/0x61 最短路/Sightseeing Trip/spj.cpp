#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdlib>
using namespace std;
int a[310][310], d[310][310], pos[310][310];
int n, m, ans = 0x3f3f3f3f;
vector<int> path; //具体方案
//一些定义
const int ACCEPT = 0;
const int WRONG_ANSWER = 1;
//fstd 标准输出 fout 选手输出 fin 标准输入
FILE *fstd,*fout,*fin;

void get_path(int x, int y) {
	if (pos[x][y] == 0) return;
	get_path(x, pos[x][y]);
	path.push_back(pos[x][y]);
	get_path(pos[x][y], y);
}

int main(int argc, char* argv[]) {
    if (argc!=4) {
        printf("参数不足 %d",argc);
        return -1;
    }
    //打开文件
    if (NULL==(fstd=fopen(argv[1],"r"))) {
        return -1;
    }
    if (NULL==(fout=fopen(argv[2],"r")) ){
        return -1;
    }
    if (NULL==(fin=fopen(argv[3],"r"))) {
        return -1;
    }

	fscanf(fin, "%d%d", &n, &m);
	memset(a, 0x3f, sizeof(a));
	for (int i = 1; i <= n; i++) a[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		fscanf(fin, "%d%d%d", &x, &y, &z);
		a[y][x] = a[x][y] = min(a[x][y], z);
	}
	memcpy(d, a, sizeof(a));
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i < k; i++)
			for (int j = i + 1; j < k; j++)
				if ((long long)d[i][j] + a[j][k] + a[k][i] < ans) {
					ans = d[i][j] + a[j][k] + a[k][i];
					path.clear();
					path.push_back(i);
					get_path(i, j);
					path.push_back(j);
					path.push_back(k);
				}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (d[i][j] > d[i][k] + d[k][j]) {
					d[i][j] = d[i][k] + d[k][j];
					pos[i][j] = k;
				}
	}
	if (ans == 0x3f3f3f3f) {
		char str[20];
		fgets(str, 13, fout);
		str[12] = 0;
		if (!strcmp(str, "No solution.")) return ACCEPT; else return WRONG_ANSWER;
	}
	/*for (int i = 0; i < path.size(); i++)
		printf("%d ", path[i]);
	puts("");*/
	long long res = 0;
	int x, y, st;
	fscanf(fout, "%d", &x);
	st = x;
	while (~fscanf(fout, "%d", &y)) {
		res += a[x][y];
		x = y;
	}
	res += a[x][st];
	if (ans == res) return ACCEPT; else return WRONG_ANSWER;
}
