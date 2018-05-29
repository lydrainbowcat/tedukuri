#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;
//一些定义
const int ACCEPT = 0;
const int WRONG_ANSWER = 1;
//fstd 标准输出 fout 选手输出 fin 标准输入
FILE *fstd,*fout,*fin;
int n;
vector<int> chosen; // 被选择的数
unordered_map<string, bool> h;

void calc(int x) {
	if (x == n + 1) { // 问题边界
		string s;
		for (int i = 0; i < chosen.size(); i++) {
			if (i > 0) s += ' ';
			if (chosen[i] < 10) s += chosen[i] + '0';
			else s += chosen[i]/10 + '0', s += chosen[i]%10 + '0';
		}
		h[s] = 1;
		return;
	}
    //"不选x"分支
	calc(x + 1); // 求解子问题
	//"选x"分支
	chosen.push_back(x); // 记录x已被选择
	calc(x + 1); // 求解子问题 
	chosen.pop_back(); // 准备回溯到上一问题之前，还原现场
}

//执行比较操作。
bool DoCompare(){
    fscanf(fin, "%d", &n);
    calc(1);
    char str[51];
    while(fgets(str, 50, fout) != NULL) {
    	int len = strlen(str);
    	while(len > 0 && (str[len - 1] < '0' || str[len - 1] > '9')) len--;
    	str[len] = 0;
    	if(h.find(str) == h.end()) return false;
    	h.erase(str);
    }
    return !h.size();
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
