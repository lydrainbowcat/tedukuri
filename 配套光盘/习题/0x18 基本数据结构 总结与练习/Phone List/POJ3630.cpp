#include<cstdio>
#include<cstring>
using namespace std;
const int MAX = 1e5 + 10;
char st[10100][10];
int word[MAX],ch[MAX][10],sz;
void init(){
   sz = 1;
   memset(ch[0],0,sizeof(ch[0]));
   memset(word,0,sizeof(word));
}
void inse(char *s){
    int nl = strlen(s),u = 0;
    for(int i = 0 ; i < nl ;i++){
        int c = s[i] - '0';
        if(! ch[u][c]){
          memset(ch[sz],0,sizeof(ch[sz]));
            ch[u][c] = sz++;
        }
        u = ch[u][c];
        word[u]++;
    }
}
int find(char *s){
   int nl = strlen(s),u = 0;
   for(int i = 0; i < nl; i++){
        int c = s[i] - '0';
        u = ch[u][c];
        if(word[u] == 1) return 0;
   }
   return 1;
}
int main()
{
    int T,N;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&N);
        for(int i = 1 ; i <= N; i++){
            scanf("%s",st[i]);
            inse(st[i]);
        }
        int ok = 1;
        for(int i = 1 ; i <= N; i++)
            if(find(st[i])){
                ok = 0;
                break;
            }
        if(ok) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}