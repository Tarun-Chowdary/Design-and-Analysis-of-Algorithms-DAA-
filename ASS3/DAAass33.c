#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;
int max_depth = 0;
int current_depth = 0;

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        comparisons++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r)
{
    current_depth++;
    if (current_depth > max_depth)
        max_depth = current_depth;

    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
    current_depth--;
}

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

void quickSort(int arr[], int low, int high)
{
    current_depth++;
    if (current_depth > max_depth)
        max_depth = current_depth;

    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
    current_depth--;
}

void generateNearlySorted(int arr[], int n)
{

    for (int i = 0; i < n; i++)
        arr[i] = i;

    int swap_count = (int)(n * 0.2);
    for (int k = 0; k < swap_count; k++)
    {
        int i = rand() % n;
        int j = rand() % n;
        swap(&arr[i], &arr[j]);
    }
}

int main()
{
    int n = 10000;
    int *arr = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));

    srand(time(NULL));
    clock_t start, end;

    FILE *fp = fopen("sort_comparison.txt", "w");
    if (!fp)
    {
        printf("Error opening file\n");
        return 1;
    }

    printf("Generating nearly sorted data (N=%d)...\n", n);
    generateNearlySorted(arr, n);

    for (int i = 0; i < n; i++)
        temp[i] = arr[i];
    comparisons = 0;
    max_depth = 0;
    current_depth = 0;

    start = clock();
    mergeSort(temp, 0, n - 1);
    end = clock();
    double time_ms = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Merge Sort: %lld comparisons, Max Depth: %d, Time: %f s\n", comparisons, max_depth, time_ms);
    fprintf(fp, "MergeSort %lld %d %f\n", comparisons, max_depth, time_ms);

    for (int i = 0; i < n; i++)
        temp[i] = arr[i];
    comparisons = 0;
    max_depth = 0;
    current_depth = 0;

    start = clock();
    quickSort(temp, 0, n - 1);
    end = clock();
    double time_qs = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Quick Sort: %lld comparisons, Max Depth: %d, Time: %f s\n", comparisons, max_depth, time_qs);
    fprintf(fp, "QuickSort %lld %d %f\n", comparisons, max_depth, time_qs);

    fclose(fp);
    free(arr);
    free(temp);
    return 0;
}