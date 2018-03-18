#include <stdio.h>

int mem[13][13][13][32][2][2];

int search (int l1, int l2, int l3, int depth, int status, int free)
{
    int i1, i2, i3, ans;
    if (mem[l1][l2][l3][depth][status][free] >= 0) return mem[l1][l2][l3][depth][status][free];
    else
    {
         if (status && l1 + l2 + l3 < depth) return mem[l1][l2][l3][depth][status][free] = 0;
         else if (depth == 0 && l1 + l2 + l3) return mem[l1][l2][l3][depth][status][free] = 0;
         else if (l1 + l2 + l3 == 0) return mem[l1][l2][l3][depth][status][free] = 1;
         else if (l1 + l2 + l3 == 1) return mem[l1][l2][l3][depth][status][free] = 1;
         
         ans = 0;
         if (depth > 1)
         {
            if (l3 > 0) ans += search(l1, l2, l3 - 1, depth - 1, status, 1);
            else if (l2 > 0) ans += search(l1, l2 - 1, l3, depth - 1, status, 1);
            else ans += search(l1 - 1, l2, l3, depth - 1, status, 1);
            ans %= 11380;
         }
         if (free) for (i1 = 0; i1 <= l1; i1++)
         {
             for (i2 = 0; i2 <= l2; i2++)
             {
                 for (i3 = 0; i3 <= l3; i3++)
                 {
                     if (i1 == 0 && i2 == 0 && i3 == 0) continue;
                     if (i1 == l1 && i2 == l2 && i3 == l3) continue;
                     
                        ans += search(i1, i2, i3, depth, status, 0) * 
                               search(l1 - i1, l2 - i2, l3 - i3, depth, 0, 1);
                     if (status)
                     {
                        ans += search(i1, i2, i3, depth, 0, 0) * 
                               search(l1 - i1, l2 - i2, l3 - i3, depth, 1, 1);
                        ans -= search(i1, i2, i3, depth, 1, 0) * 
                               search(l1 - i1, l2 - i2, l3 - i3, depth, 1, 1);
                     }
                     ans %= 11380;
                     ans = (ans + 113800) % 11380;
                 }
             }
         }
         return mem[l1][l2][l3][depth][status][free] = ans;
    }
}

int main ()
{
    int l1, l2, l3, depth;
    scanf("%d %d %d %d", &l3, &l2, &l1, &depth);
    memset(mem, 0x7FFFFFFF, sizeof(mem));
    printf("%d\n", search(l1, l2, l3, depth, 1, 1));
    return 0;
}
