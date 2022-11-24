#include "kernel.h"
#include <time.h>

void sort_elements_by_idx(element *elements, int start, int end) {
    if (start >= end)
        return;

    int pivot = start;
    int i = pivot + 1;
    int j = end;
    element temp;
    while (i <= j)
    {
        while (i <= end && elements[i].index <= elements[pivot].index)
        {
            i++;
        }
        while (j > start && elements[j].index >= elements[pivot].index)
        {
            j--;
        }
        if (i > j)
        {
            temp = elements[j];
            elements[j] = elements[pivot];
            elements[pivot] = temp;
        }
        else
        {
            temp = elements[i];
            elements[i] = elements[j];
            elements[j] = temp;
        }
    }
    sort_elements_by_idx(elements, start, j - 1);
    sort_elements_by_idx(elements, j + 1, end);
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: ./partition_problem <g|dp>\n");
		exit(1);
	}

    /* Handle input file */

    int nmemb;
    scanf("%d\n", &nmemb);

	element elements[nmemb]; // Data of each elements.

	for (int i = 0; i < nmemb; i++){
		scanf("%d\n", &elements[i].value);
		elements[i].index = i;

		// Initializing group ids.
		for (int j = 0; j < MAX_NGRP; j++)
			elements[i].groupId[j] = -1;
	}

	/* Run algorithm */

	int partitionable = -1;

	struct timeval start;
	gettimeofday(&start, NULL);

	if (strcmp(argv[1], "g") == 0) {
		partitionable = partition_by_greedy(elements, nmemb);
	} else if (strcmp(argv[1], "dp") == 0) {
		partitionable = partition_by_dp(elements, nmemb);
	} else {
		fprintf(stderr, "Invalid arguments\n");
		exit(1);
	}

	struct timeval end;
	gettimeofday(&end, NULL);
	fprintf(stderr, "elapsed time: %lf\n", ((end.tv_sec + end.tv_usec * 0.000001) - (start.tv_sec + start.tv_usec * 0.000001)));

	/* Print result */
	int sum[2] = {0, };

	printf("%d\n\n", partitionable);

	sort_elements_by_idx(elements, 0, nmemb-1);

	for (int j = 0; j < partitionable; j++) {
		printf("[%02d]\n", j+1);
		sum[0] = 0; sum[1] = 0;
		for (int i = 0; i < nmemb; i++) {
			printf("%d %d\n", elements[i].value, elements[i].groupId[j]);
			sum[elements[i].groupId[j]] += elements[i].value;
		}
		printf("Sum of each group : [%d, %d]\n\n", sum[0], sum[1]);
	}
	
	return 0;
}