#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std; 
//一些定义
const int ACCEPT = 0;
const int WRONG_ANSWER = 1;
//fstd 标准输出 fout 选手输出 fin 标准输入
FILE *fstd,*fout,*fin;
int n, m, k, a[20][20], v[20][20], ans, val;

//执行比较操作。
bool DoCompare(){
    fscanf(fin, "%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
    	for (int j = 1; j <= m; j++) fscanf(fin, "%d", &a[i][j]);
    fscanf(fstd, "%*s%*s%d", &ans);
    fscanf(fout, "%*s%*s%d", &val);
    // 答案不对 
    if (val != ans) return false;
    for (int i = 1; i <= k; i++) {
    	int x, y; fscanf(fout, "%d%d", &x, &y);
    	// 格子越界或者有重复 
    	if (x < 1 || y < 1 || x > n || y > m || v[x][y]) return false;
    	v[x][y] = 1;
    	val -= a[x][y];
    }
    // 输出的格子加起来不等于答案 
    if (val) return false;
    // 检查凸性 
    for (int i = 1; i <= n; i++) {
    	int cnt = 0, l = m, r = 1;
    	for (int j = 1; j <= m; j++)
    		if (v[i][j]) cnt++, l = min(l, j), r = max(r, j);
    	if (cnt == 0) continue;
    	// 输出的格子在一行里不连续 
    	if (r - l + 1 != cnt) return false;
    }
    for (int j = 1; j <= m; j++) {
    	int cnt = 0, l = n, r = 1;
    	for (int i = 1; i <= n; i++)
    		if (v[i][j]) cnt++, l = min(l, i), r = max(r, i);
    	if (cnt == 0) continue;
    	// 输出的格子在一列里不连续 
    	if (r - l + 1 != cnt) return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
    if(argc!=4){
        printf("参数不足 %d",argc);
        return -1;
    }

    //打开文件
    if(NULL==(fstd=fopen(argv[1],"r"))){
        return -1;
    }
    if(NULL==(fout=fopen(argv[2],"r"))){
        return -1;
    }
    if(NULL==(fin=fopen(argv[3],"r"))){
        return -1;
    }

    if(DoCompare()){
        return ACCEPT;
    }else{
        return WRONG_ANSWER;
    }
}
