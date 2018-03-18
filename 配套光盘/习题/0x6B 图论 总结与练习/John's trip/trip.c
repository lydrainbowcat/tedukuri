/*
	Problem: 	Trip
	Author:		Jan Kotas
	Class:		graph
	Description:	find cycle containing each edge just once
	Algorithm:	Euclid path with logging
	Complexity:	O(edges)
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct street
{
	int x, y; /* ending junctions */
	int number; /* number of the street */

	int nextx, nexty; /* single linked lists started by junctions[i] */

	int prev, next; /* index of previous and next street in the solution */
}
streets[2048];

int junctions[64]; /* index of unused street going to junction with smallest number */

int path(int junction, int *start_street, int *end_street) /* returns ending junction */
{
	int street, s;

	street = -1;

	for(;;)
	{
		if((s = junctions[junction]) == -1)
		{
			if(street == -1)
				*start_street = -1;

			*end_street = street;

			return junction;
		}

		if(streets[s].next == -1) /* unused street */
		{
			if(street == -1)
			{
				streets[s].prev = -2;
				*start_street = s;
			}
			else
			{
				streets[s].prev = street ;
				streets[street].next = s;
			}

			streets[s].next = -2;

			junctions[junction] = (streets[s].x == junction) 
				? streets[s].nextx : streets[s].nexty;

			junction = (streets[s].x != junction) ? 
				streets[s].x : streets[s].y;

			street = s;
		}
		else
		{
			junctions[junction] = (streets[s].x == junction) ? 
				streets[s].nextx : streets[s].nexty;
		}
	}
}

int number_cmp(const void *a, const void *b)
{
	return ((struct street *)a)->number - ((struct street *)b)->number;
}

#define min(a, b)  (((a) < (b)) ? (a) : (b)) 

void print(int start_street)
{
	int s;

	printf("%d", streets[start_street].number);

	for(s = streets[start_street].next; s != start_street; s = streets[s].next)
		printf(" %d", streets[s].number);

	printf("\n");
}

int main(void)
{
	int count, junction, start_street, street, i, s, e, ss;

	for(;;)
	{
		count = 0;

		for(;;)
		{
			scanf("%d%d", &streets[count].x, &streets[count].y);
			if(!streets[count].x || !streets[count].y) break;

			scanf("%d", &streets[count++].number);
		}

		if(!count) break;

		junction = min(streets[0].x, streets[0].y);

		qsort(streets, count, sizeof(streets[0]), number_cmp);

		memset(junctions, -1, sizeof(junctions));

		for(i = count - 1; i >= 0; i--)
		{
			streets[i].nextx = junctions[streets[i].x];
			junctions[streets[i].x] = i;

			streets[i].nexty = junctions[streets[i].y];
			junctions[streets[i].y] = i;

			streets[i].prev = -1;
			streets[i].next = -1;
		}

		if(path(junction, &start_street, &e) != junction)
			goto fail;

		streets[start_street].prev = e;
		streets[e].next = start_street;

		street = start_street;

		do
		{
again:
			if(path(junction, &s, &e) != junction)
				goto fail;

			if(s != -1 && e != -1)
			{
				ss = streets[street].prev;

				streets[s].prev = ss;
				streets[ss].next = s;

				streets[street].prev = e;
				streets[e].next = street;

				goto again;
			}

			street = streets[street].prev;

			junction = (streets[street].x != junction) ? 
				streets[street].x : streets[street].y;
		}
		while(street != start_street);

		print(start_street);

		continue;

fail:
		printf("Round trip does not exist.\n");
	}
	return 0;
}
