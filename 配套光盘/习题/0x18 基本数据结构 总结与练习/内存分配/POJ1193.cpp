/*
Author: https://github.com/archer811/ACM/blob/master/poj/1193/1193%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D.cpp
题意：(中文题)模拟内存分配。
题解：典型的模拟题：
1.维护一个进程的链表，每个节点存有进程开始时间t，进程运行时间p，
在内存中的首地址s，占用内存大小m,和下一节点指针。
2.维护一个队列，表示还没有空间运行的进程。
3.维护一个释放内存的最早时间nexttime，每读入一个新进程的时候，若
进程开始时间不小于nexttime，表示有进程在这之前已结束（可能不止一
个），将其从链表删除，并循环检测队首进程是否有空间运行，如果有，就
将其先加入（注意开始时间要设为止刻的nexttime，而不是读入的值了）。
最后将新读入的进程加入链表，或加入队列。
如此往复。。。读入结束后，再对残余的队列和链表处理完，算出结果，完毕。
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include<cstdio>
using namespace std;
const int inf = 1<<28;
int n,m;
struct node
{
       int m,t,p,s,next;
}a[10000];

int Q[10000],head,tail,root,nexttime;

//分配内存(插入链表)
bool alloc(int pos,int t)
{
     if (!root || a[root].s-0>=a[pos].m)
     {
                a[pos].next=root;
                root=pos;
                a[pos].t=t;
                a[pos].s=0;
                return true ;
     }
     int i;
     for (i=root;a[i].next!=0;i=a[i].next)
     {
         if (a[i].s+a[i].m-1+a[pos].m < a[a[i].next].s)
         {
            a[pos].next=a[i].next;
            a[i].next=pos;
            a[pos].s=a[i].s+a[i].m;
            a[pos].t=t;
            return true;
         }
     }
     if (i && n-(a[i].s+a[i].m) >= a[pos].m)
     {
           a[i].next=pos;
           a[pos].next=0;
           a[pos].s=a[i].s+a[i].m;
           a[pos].t=t;
           return true;
     }
     return false;
}
//删除结束的进程，加入队列进程,更新nexttime
void free_and_pop()
{
					int pre=root,temp=inf;
                    for (int i=root;i;)
                    {
                        if (a[i].t+a[i].p==nexttime)
                        {
                              if (i==root)
                              {
                                           root=a[root].next;
                                           i=root;
                              }
                              else
                              {
                                           i=a[pre].next=a[i].next;
                              }
                        }
                        else
                        {
                             if (a[i].t+a[i].p<temp) temp=a[i].t+a[i].p;
                             pre=i;
                             i=a[i].next;
                        }
                    }
                    while (head<tail)
                    if (!alloc(Q[head],nexttime)) break;
                    else { temp=min(temp,a[Q[head]].t+a[Q[head]].p);++head;}

                    nexttime=temp;

}
//插入新读入的进程
void insert(int pos)
{
               while (a[pos].t>=nexttime)  free_and_pop();
               if (!alloc(pos,a[pos].t)) { Q[tail++]=pos; }
               else nexttime=min(nexttime,a[pos].t+a[pos].p);

}
//处理最后的队列中的进程
int SolveRemain()
{
	while (head<tail)
	{
		free_and_pop();
	}
	int lasttime=nexttime;
	for (int i=root;i;i=a[i].next)
	{
		lasttime=max(lasttime,a[i].t+a[i].p);
	}
	return lasttime;
}

int main()
{
    scanf("%d",&n);
    head=tail=root=0;
    nexttime=inf;
    for (int i=1;;i++)
    {
        scanf("%d%d%d",&a[i].t,&a[i].m,&a[i].p);
		if (a[i].t==0 && a[i].m==0 && a[i].p==0) break;
        insert(i);
    }

    printf("%d\n%d\n",SolveRemain(),tail);

    return 0;
}
