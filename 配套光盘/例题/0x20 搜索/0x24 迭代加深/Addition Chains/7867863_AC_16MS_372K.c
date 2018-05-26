#include <stdio.h>
#define mi 19931117

int lg[110];
int log2calc (int a)
{
    int ans = 0, ml = 1;
    while (ml < a) ans++, ml *= 2;
    return ans;
}

int arr[110], arrmr, maxdepth, tar;
int hfunc ()
{
    if (arr[arrmr] > tar) return mi;
    else return lg[(int)ceil((double)tar / arr[arrmr])];
}

int dfs (int depth)
{
    int i, j, h;
    for (i = depth - 1; i >= 0; i--)
    {
        if (arr[i] + arr[i] <= arr[depth - 1]) break;
        for (j = i; j >= 0; j--)
        {
            if (arr[i] + arr[j] <= arr[depth - 1]) break;
            arr[depth] = arr[i] + arr[j];
            arrmr = depth;
            h = hfunc();
            if (h == 0) return 1;
            else if (h + depth < maxdepth)
            {
                 if (dfs(depth + 1)) return 1;
            }
        }
    } return 0;
}

int main ()
{
    int i;
    for (i = 1; i < 110; i++)
        lg[i] = log2calc(i);
    while (1)
    {
          scanf("%d", &tar);
          if (tar == 0) break;
          else if (tar == 1)
          {
               printf("1\n");
               continue;
          }
          else if (tar == 2)
          {
               printf("1 2\n");
               continue;
          }
          arr[0] = 1;
          arrmr = 0;
          maxdepth = hfunc();
          while (dfs(1) == 0) maxdepth++;
          for (i = 0; i < maxdepth; i++)
              printf("%d ", arr[i]);
          printf("\n");
    }
    return 0;
}
