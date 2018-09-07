/**
 * Model solution to problem: "Ultra-QuickSort".
 * FAU Programming Contest, Jan 2005.
 * author: Stefan Buettcher
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** Number of elements in the current sequence. **/
int n;

/** The sequence itself. **/
int sequence[1000004];

/** Used by my MergeSort implementation. **/
int temp[1000004];


/**
 * getResult is a MergeSort implementation that, at the same time, reports
 * the number of swap operations that would have been necessary to sort the
 * input sequence.
 **/
long long getResult(int *sequence, int from, int to) {
	if (to == from + 1)
		return 0;
	if (to == from + 2) {
		if (sequence[from] < sequence[from + 1])
			return 0;
		int temp = sequence[from];
		sequence[from] = sequence[from + 1];
		sequence[from + 1] = temp;
		return 1;
	}
	int middle = (from + to) / 2;
	long long result = getResult(sequence, from, middle);
	result += getResult(sequence, middle, to);
	int rightPos = (to - middle) - 1;
	int leftPos = (middle - from) - 1;
	int outPos = to - from;
	while ((leftPos >= 0) && (rightPos >= 0)) {
		if (sequence[leftPos + from] > sequence[rightPos + middle]) {
			result += (rightPos + 1);
			temp[--outPos] = sequence[from + (leftPos--)];
		}
		else
			temp[--outPos] = sequence[middle + (rightPos--)];
	}
	while (leftPos >= 0)
		temp[--outPos] = sequence[from + (leftPos--)];
	while (rightPos >= 0)
		temp[--outPos] = sequence[middle + (rightPos--)];

	// copy "temp" to the original "sequence" array
	memcpy(&sequence[from], temp, (to - from) * sizeof(int));
	return result;
} // end of getResult(int*, int, int)


/**
 * getResult2 is the naive O(n^2) BubbleSort implementation that is used
 * to verify the results produced by getResult.
 **/
long long getResult2(int *sequence, int from, int to) {
	bool done = false;
	long long result = 0;
	while (!done) {
		done = true;
		for (int i = from; i < to - 1; i++) {
			if (sequence[i] > sequence[i + 1]) {
				result++;
				int temp = sequence[i];
				sequence[i] = sequence[i + 1];
				sequence[i + 1] = temp;
				done = false;
			}
		}
	}
	return result;
} // end of getResult2(int*, int, int)


/**
 * main reads input from stdin, calls getResult for every test case and writes
 * the output to stdout.
 **/
int main() {
	while (scanf("%i", &n) == 1) {
		if (n == 0)
			break;
		for (int i = 0; i < n; i++)
			scanf("%i", &sequence[i]);
		if (n == 1) {
			printf("0\n");
			continue;
		}
		long long result = getResult(sequence, 0, n);
		if (result <= 1000000000)
			printf("%i\n", (int)result);
		else
			printf("%i%09i\n", (int)(result / 1000000000), (int)(result % 1000000000));
	}
	return 0;
} // end of main()


