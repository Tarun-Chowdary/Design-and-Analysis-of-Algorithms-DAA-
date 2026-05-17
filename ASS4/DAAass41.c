#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comp_fixed = 0;
long long comp_qs = 0;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partitionFixed(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (i <= j)
    {
        while (i <= high && (++comp_fixed && arr[i] <= pivot))
            i++;
        while ((++comp_fixed && arr[j] > pivot))
            j--;
        if (i < j)
            swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quickSortFixed(int arr[], int low, int high)
{
    if (low < high)
    {
        int p = partitionFixed(arr, low, high);
        quickSortFixed(arr, low, p - 1);
        quickSortFixed(arr, p + 1, high);
    }
}

double findMedianFixedPivot(int arr[], int n)
{
    quickSortFixed(arr, 0, n - 1);
    if (n % 2 == 0)
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    else
        return arr[n / 2];
}

int partitionQS(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low;

    for (int j = low; j < high; j++)
    {
        comp_qs++;
        if (arr[j] <= pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}

int quickSelect(int arr[], int low, int high, int k)
{
    if (low <= high)
    {
        int p = partitionQS(arr, low, high);
        if (p == k)
            return arr[p];
        else if (p > k)
            return quickSelect(arr, low, p - 1, k);
        else
            return quickSelect(arr, p + 1, high, k);
    }
    return -1;
}

double findMedianQuickSelect(int arr[], int n)
{
    if (n % 2 == 1)
        return quickSelect(arr, 0, n - 1, n / 2);
    else
    {
        int m1 = quickSelect(arr, 0, n - 1, n / 2 - 1);
        int m2 = quickSelect(arr, 0, n - 1, n / 2);
        return (m1 + m2) / 2.0;
    }
}

int main()
{
    int n = 110000;

    int original[n], arr1[n], arr2[n];

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        original[i] = rand() % 361;
        arr1[i] = original[i];
        arr2[i] = original[i];
    }

    clock_t start, end;
    double time_fixed, time_qs;

    start = clock();
    double median1 = findMedianFixedPivot(arr1, n);
    end = clock();
    time_fixed = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    double median2 = findMedianQuickSelect(arr2, n);
    end = clock();
    time_qs = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n\nMedian (Fixed Pivot) = %.2f", median1);
    printf("\nMedian (Quickselect) = %.2f", median2);

    printf("\n\n--- Comparative Analysis ---");
    printf("\nFixed Pivot -> Time: %f sec, Comparisons: %lld", time_fixed, comp_fixed);
    printf("\nQuickselect -> Time: %f sec, Comparisons: %lld", time_qs, comp_qs);

    if (time_qs < time_fixed)
        printf("\n\nQuickselect is faster for this dataset.");
    else
        printf("\n\nFixed Pivot is faster for this dataset.");

    if (comp_qs < comp_fixed)
        printf("\nQuickselect uses fewer comparisons.");
    else
        printf("\nFixed Pivot uses fewer comparisons.");

    return 0;
}
