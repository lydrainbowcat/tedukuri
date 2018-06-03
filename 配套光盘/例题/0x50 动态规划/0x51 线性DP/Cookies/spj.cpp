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
int n, m, ans, val, c[32], g[32];

//执行比较操作。
bool DoCompare(){
    fscanf(fin, "%d%d", &n, &m);
    for (int i = 1; i <= n; i++) fscanf(fin, "%d", &g[i]);
    fscanf(fstd, "%d", &ans);
    fscanf(fout, "%d", &val);
    // 答案不对 
    if (ans != val) return false;
    for (int i = 1; i <= n; i++) {
		fscanf(fout, "%d", &c[i]);
		// 每个孩子分到正整数块饼干 
		if (c[i] <= 0) return false;
		m -= c[i];
	}
	// 饼干没有分完 
	if (m) return false;
	// 检查方案的怨气值是否等于输出的值 
    for (int i = 1; i <= n; i++) {
    	int cnt = 0;
    	for (int j = 1; j <= n; j++) if (c[j] > c[i]) cnt++;
    	val -= cnt * g[i];
    }
	return val == 0;
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
