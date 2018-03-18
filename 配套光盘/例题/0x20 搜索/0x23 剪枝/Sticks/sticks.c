/*
	Problem: 	Sticks
	Author:		Jan Kotas
	Algorithm:	backtrack with restrains
	Complexity:	exp
*/

#include <stdio.h>
#include <memory.h>

#define bool int
#define false 0
#define true 1

#define MAXLEN 50

int total; /* total length */

int type_count;
int lengths[MAXLEN]; /* parts lengths */
int counts[MAXLEN]; /* parts counts */

int starts[256]; /* starts of sticks - pointers to array solution */
int solution[256]; /* solution - ponters to array lengths */

int stick_length; /* currently tested length of stick */

bool try_it(
	int length, /* already used length of parts */
	int count, /* count of already used parts */
	bool less /* the current stick is already lexicographically less then previous */
) 
{
	int s; /* count of finished sticks */
	int l;
	int i, j, k;

	s = length / stick_length;

	if((l = length % stick_length) == 0)
	{
		if(length == total)
			return true;

		/* starting new stick */

		starts[s] = count;
		i = solution[starts[s-1]];
		less = false;
	}
	else
	{
		i = less ? solution[count-1] : solution[starts[s-1] + (count - starts[s])];

		l = stick_length - l;

		if(lengths[i] > l)
		{
			do { i--; } while(lengths[i] > l); /* record for part of length 1 always exists */
			less = true;
		}
	}

	for( ; i >= 0; i--)
	{
		if(!counts[i])
			goto skip;

#if 1 /* checks for replacing of group of sticks with bigger one */

		l = lengths[i];

		for(j = count - 1, k = i + 1; j >= starts[s]; j--)
		{
			l += lengths[solution[j]];

			while(l > lengths[k]) 
				k++;

			if(k >= type_count)
				break;

			if(l == lengths[k] && !!counts[k])
				goto skip;
		}

#endif

		solution[count] = i;

		counts[i]--;

		if(try_it(length + lengths[i], count+1,	less))
		{
			counts[i]++;
			return true;
		}

		counts[i]++;

skip:
		less = true;
	}
			
	return false;
}

int failed[1024];
int failed_count;

int main(void)
{
	int m, l, i, j, found, last;

	for(;;)
	{
		scanf("%d", &m);

		if(!m) break;

		memset(counts, 0, sizeof(counts));

		for(i = 0; i < m; i++)
		{
			scanf("%d", &l);
			counts[l-1]++;
		}

		type_count = 1;		
		total = counts[0];

		lengths[0] = 1; /* restrain - part of the length 1 always exists */
		
		for(i = 1; i < MAXLEN; i++)
		{
			if(!counts[i])
				continue;

			total += (counts[type_count] = counts[i]) * (lengths[type_count] = i+1);
			type_count++;
		}

		lengths[type_count] = total; /* restrain */

		found = total;

		failed_count = 0;

		last = total / lengths[type_count-1];

		for(i = 2; i <= last; i++)
		{
			 /* i - number of sticks */

			if(total % i != 0)
				continue;

			for(j = 0; j < failed_count; j++)
				if(i % failed[j] == 0)
					break;

			if(j != failed_count)
				continue;

			stick_length = total / i;

			starts[0] = 0;
			solution[0] = type_count-1;

			if(try_it(lengths[type_count-1], 1, true))  
			{
				found = total / i;
				continue;
			}

			failed[failed_count++] = i;
		}

		printf("%d\n", found);
	}
	return 0;
}
