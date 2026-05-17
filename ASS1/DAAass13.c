#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons;

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;
            if (arr[j] > arr[j + 1])
            {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0)
        {
            comparisons++;
            if (arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            else
            {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++;
        if (arr[j] < pivot)
        {
            i++;
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }

    int t = arr[i + 1];
    arr[i + 1] = pivot;
    pivot = t;

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        comparisons++;
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main()
{
    int sizes[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int nSizes = 10;

    clock_t start, end;
    double time_taken;

    for (int s = 0; s < nSizes; s++)
    {
        int n = sizes[s];

        int *arr = (int *)malloc(n * sizeof(int));
        int *temp = (int *)malloc(n * sizeof(int));

        srand(time(NULL));
        for (int i = 0; i < n; i++)
            arr[i] = rand() % 100000;

        printf("\n=====================================");
        printf("\nArray Size: %d\n", n);

        for (int i = 0; i < n; i++)
            temp[i] = arr[i];
        comparisons = 0;
        start = clock();
        bubbleSort(temp, n);
        end = clock();
        time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Bubble Sort   -> Time: %f sec | Comparisons: %lld\n",
               time_taken, comparisons);

        for (int i = 0; i < n; i++)
            temp[i] = arr[i];
        comparisons = 0;
        start = clock();
        insertionSort(temp, n);
        end = clock();
        time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Insertion Sort-> Time: %f sec | Comparisons: %lld\n",
               time_taken, comparisons);

        for (int i = 0; i < n; i++)
            temp[i] = arr[i];
        comparisons = 0;
        start = clock();
        quickSort(temp, 0, n - 1);
        end = clock();
        time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Quick Sort    -> Time: %f sec | Comparisons: %lld\n",
               time_taken, comparisons);

        for (int i = 0; i < n; i++)
            temp[i] = arr[i];
        comparisons = 0;
        start = clock();
        mergeSort(temp, 0, n - 1);
        end = clock();
        time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Merge Sort    -> Time: %f sec | Comparisons: %lld\n",
               time_taken, comparisons);

        free(arr);
        free(temp);
    }

    return 0;
}
