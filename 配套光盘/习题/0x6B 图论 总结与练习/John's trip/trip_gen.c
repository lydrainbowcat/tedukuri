#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct street
{
	int from, to, number;
}
streets[2048];

int comp[64];
int use[64];

int count;

void print()
{
	int i, j, k;
	struct street s;

	for(i = 0; i < count; i++)
		streets[i].number = i + 1;

	for(i = 0; i < count; i++)
	{
		j = rand() % count;
		k = rand() % count;

		s = streets[j];
		streets[j] = streets[k];
		streets[k] = s;
	}

	for(i = 0; i < count; i++)
		printf("%d %d %d\n", streets[i].from + 1, streets[i].to + 1, streets[i].number);

	printf("0 0\n");
}

int find(int i)
{
    int l,p=i;

    while(comp[i]!=i)i=comp[i];

    while(p!=i){ l=p; p=comp[p]; comp[l]=i; }

    return i;
}

void add(int f, int t)
{
	streets[count].from = f;
	streets[count].to = t;
	count++;

    comp[find(f)] = find(t);

	use[f]++;
	use[t]++;
}

void main()
{
	int k, i, m, b;

	printf("1 2 1\n");
	printf("2 3 2\n");
	printf("3 1 6\n");
	printf("1 2 5\n");
	printf("2 3 3\n");
	printf("3 1 4\n");
	printf("0 0\n");

	printf("1 2 1\n");
	printf("2 3 2\n");
	printf("1 3 3\n");
	printf("2 4 4\n");
	printf("0 0\n");

	printf("1 1 1\n");
	printf("0 0\n");

	printf("1 1 1\n");
	printf("1 1 2\n");
	printf("0 0\n");
	
	printf("1 2 1\n");
	printf("2 3 2\n");
	printf("1 3 3\n");
	printf("2 4 4\n");
	printf("2 4 5\n");
	printf("0 0\n");


	for(k = 30; k >= 0; k--)
	{
		count = 0;

		m = 1 + rand() % (1 + rand() % 44);

		memset(use, 0, sizeof(use[0]) * m);

		for(i = 0; i < m; i++)
			comp[i] = i;

		for(i = 1 + rand() % (1 + rand() % (1 + (m * m) / 3)); i >= 0; i--)
			add(rand() % m, rand() % m);

		for(i = 1; i < m; i++)
			if(find(i-1) != find(i))
				add(comp[i-1], comp[i]);

		for(i = rand() % (1 + rand() % (1995 - count)); i >= 0; i--)
			add(rand() % m, rand() % m);

		if(rand() & 7)
		{
			b = -1;

			for(i = 0; i < m; i++)
			{
				if(use[i] & 1)
				{
					if(b != -1)
					{
						add(b, i);
						b = -1;
					}
					else b = i;
				}
			}
		}

		print();
	}

	printf("0 0\n");
}
