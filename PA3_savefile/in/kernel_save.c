#include "kernel.h"

void sort_elements(element *elements, int start, int end) {
    if (start >= end)
        return;

    int pivot = start;
    int i = pivot + 1;
    int j = end;
    element temp;
    while (i <= j)
    {
        while (i <= end && elements[i].value <= elements[pivot].value)
        {
            i++;
        }
        while (j > start && elements[j].value >= elements[pivot].value)
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
    sort_elements(elements, start, j - 1);
    sort_elements(elements, j + 1, end);
}

int partition_by_greedy(element *elements, int nmemb)
{
    /*
     TODO : Partition the elements using greedy algorithm.
     - You might want to use the sorting algorithm implemented.
     - Returns 1 if implemented.
    */

    return -1;
}

int partition_by_dp(element *elements, int nmemb)
{
    /*
     TODO : Partition the elements using Dynamic Programming algorithm.
     - You might want to use the sorting algorithm implemented.
     - Your elementry goal is to tell whether the given set of numbers are partionable and show one solution.
     - Your secondary goal is to tell all the possible cases of parititioning.
     - Returns 0 if not partitionable, else number of available partitions.
    */

    return -1;
}