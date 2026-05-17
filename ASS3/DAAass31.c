

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        comparisons++;
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

int randomizedPartition(int arr[], int low, int high)
{
    srand(time(NULL));
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);

    return partition(arr, low, high);
}

void randomizedQuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

void generateData(int arr[], int n, int type)
{
    for (int i = 0; i < n; i++)
    {
        if (type == 1)
        {
            arr[i] = i;
        }
        else if (type == 2)
        {
            arr[i] = n - i;
        }
        else
        {
            arr[i] = rand() % 100000;
        }
    }
}

int main()
{
    int n = 100000;
    int *arr = (int *)malloc(n * sizeof(int));
    clock_t start, end;
    double time_taken;

    printf("--- Randomized Quicksort Analysis (N = %d) ---\n\n", n);

    generateData(arr, n, 1);
    comparisons = 0;

    start = clock();
    randomizedQuickSort(arr, 0, n - 1);
    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Scenario 1: Already Sorted Input\n");
    printf("Comparisons: %lld\n", comparisons);
    printf("Time Taken : %f seconds\n\n", time_taken);

    generateData(arr, n, 2);
    comparisons = 0;

    start = clock();
    randomizedQuickSort(arr, 0, n - 1);
    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Scenario 2: Reverse Sorted Input\n");
    printf("Comparisons: %lld\n", comparisons);
    printf("Time Taken : %f seconds\n\n", time_taken);

    generateData(arr, n, 3);
    comparisons = 0;

    start = clock();
    randomizedQuickSort(arr, 0, n - 1);
    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Scenario 3: Random Input\n");
    printf("Comparisons: %lld\n", comparisons);
    printf("Time Taken : %f seconds\n\n", time_taken);

    free(arr);
    return 0;
}