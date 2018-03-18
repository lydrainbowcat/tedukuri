#include <stdio.h>
#define EMPTY -1

char map[16][16];
unsigned short table[16][16];
int filled;

void fill (int i, int j, int a)
{
    int r, c, k, m;
    filled++;
    map[i][j] = a;
    for (k = 0; k < 16; k++)
        table[i][k] |= (1 << (a - 1)), table[k][j] |= (1 << (a - 1));
    r = (int)(i / 4) * 4;
    c = (int)(j / 4) * 4;
    for (k = 0; k < 4; k++)
    {
        for (m = 0; m < 4; m++)
            table[r + k][c + m] |= (1 << (a - 1));
    }
    return;
}

int search ()
{
    char t_map[16][16];
    unsigned short t_table[16][16]; int t_filled;
    int i, j, k, m, r, c, r1, r2, t0, t, flag;
    
    if (filled == 256) return 1;
    
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
        {
            if (map[i][j]) continue;
            r = -1;
            for (k = 0; k < 16; k++)
            {
                if (((table[i][j] & (1 << k)) == 0) && r == -1) r = k;
                else if (((table[i][j] & (1 << k)) == 0) && r != -1) { r = -2; break; }
            }
            if (r == -1) return 0;
            else if (r != -2) fill(i, j, r + 1);
        }
    }
    
    for (i = 0; i < 16; i++)
    {
        for (k = 0; k < 16; k++)
        {
            r = -1;
            for (j = 0; j < 16; j++)
            {
                if (map[i][j] == k + 1) { r = -2; break; }
                if (map[i][j]) continue;
                if (((table[i][j] & (1 << k)) == 0) && r == -1) r = j;
                else if (((table[i][j] & (1 << k)) == 0) && r != -1) { r = -2; break; }
            }
            if (r == -1) return 0;
            else if (r != -2) fill(i, r, k + 1);
        }
    }
    
    for (j = 0; j < 16; j++)
    {
        for (k = 0; k < 16; k++)
        {
            r = -1;
            for (i = 0; i < 16; i++)
            {
                if (map[i][j] == k + 1) { r = -2; break; }
                if (map[i][j]) continue;
                if (((table[i][j] & (1 << k)) == 0) && r == -1) r = i;
                else if (((table[i][j] & (1 << k)) == 0) && r != -1) { r = -2; break; }
            }
            if (r == -1) return 0;
            else if (r != -2) fill(r, j, k + 1);
        }
    }
    
    for (r = 0; r < 16; r += 4)
    {
        for (c = 0; c < 16; c += 4)
        {
            for (k = 0; k < 16; k++)
            {
                r1 = -1, r2 = -1;
                for (i = 0; i < 4; i++)
                {
                    for (j = 0; j < 4; j++)
                    {
                        if (map[r + i][c + j] == k + 1) { r1 = r2 = -2; goto outerloop1; }
                        if (map[r + i][c + j]) continue;
                        if (((table[r + i][c + j] & (1 << k)) == 0) && r1 == -1) r1 = r + i, r2 = c + j;
                        else if (((table[r + i][c + j] & (1 << k)) == 0) && r1 != -1)
                            { r1 = r2 = -2; goto outerloop1; }
                    }
                }
                outerloop1: 
                if (r1 == -1) return 0;
                else if (r1 != -2) fill(r1, r2, k + 1);
            }
        }
    }
    
    if (filled == 256) return 1;
    
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
            t_map[i][j] = map[i][j];
    }
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
            t_table[i][j] = table[i][j];
    }
    t_filled = filled;
    
    t0 = 256;
    for (i = 15; i >= 0; i--)
    {
        for (j = 15; j >= 0; j--)
        {
            if (map[i][j]) continue;
            t = 0;
            for (k = 0; k < 16; k++)
            {
                if ((table[i][j] & (1 << k)) == 0) t++;
                if (t >= t0) break;
            }
            if (t < t0)
            {
               t0 = t;
               r1 = i, r2 = j;
            } 
            break;
        }
    }
    
    outerloop2:
    for (m = 0; m < 16; m++)
    {
        if ((table[r1][r2] & (1 << m)) == 0)
        {
            fill(r1, r2, m + 1);
            flag = search();
            if (flag == 1) return 1;
            else
            {
                for (i = 0; i < 16; i++)
                {
                    for (j = 0; j < 16; j++)
                        map[i][j] = t_map[i][j];
                }
                for (i = 0; i < 16; i++)
                {
                   for (j = 0; j < 16; j++)
                       table[i][j] = t_table[i][j];
               }
               filled = t_filled;
            }
        }
    }
    
    return 0;
}

int main ()
{
    int i, j, k, m, r, c, a;
    char ar[60];
    
    while (1)
    {
          
    memset(map, 0, sizeof(map));
    memset(table, 0, sizeof(table));
    filled = 0;
        
    for (i = 0; i < 16; i++)
    {
        if (scanf("%s", ar) != 1) goto end;
        for (j = 0; j < 16; j++)
        {
            a = ar[j];
            if (a == '-') continue;
            else fill(i, j, a - 64);
        }
    }
        
    search();
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
            printf("%c", map[i][j] + 64);
        printf("\n");
    } printf("\n");
    
    }
    end: 
    return 0;
}
