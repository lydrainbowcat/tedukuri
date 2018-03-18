#include <stdio.h>
#include <stdlib.h>

void main()
{
	int k, i;

	/* few of big parts */

	for(k = 128; k >= 0; k--)
	{
		i = 1 + rand() % 32;

		printf("%d\n", i);

		for(i = i - 1; i >= 0; i--)
			printf((i == 0) ? "%d\n" : "%d ", 1 + rand() % 64);
	}

	/* many of small parts */

	for(k = 128; k >= 0; k--)
	{
		i = 1 + rand() % 64;

		printf("%d\n", i);

		for(i = i - 1; i >= 0; i--)
			printf((i == 0) ? "%d\n" : "%d ", 1 + rand() % 8);
	}

	printf("0\n");
}
