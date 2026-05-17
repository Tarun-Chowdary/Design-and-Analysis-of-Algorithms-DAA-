#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void findviadivncon(int *arr, int l, int r, int *max, int *min, int *count)
{
    int lmin, rmin, lmax, rmax;
    if (l == r)
    {
        *max = arr[l];
        *min = *max;
    }
    else if (r == l + 1)
    {
        (*count)++;
        if (arr[l] >= arr[r])
        {
            *max = arr[l];
            *min = arr[r];
        }
        else
        {
            *max = arr[r];
            *min = arr[l];
        }
    }
    else
    {
        int mid = l + ((r - l) / 2);
        findviadivncon(arr, l, mid, &lmax, &lmin, count);
        findviadivncon(arr, mid + 1, r, &rmax, &rmin, count);
        if (lmin < rmin)
            *min = lmin;
        else
            *min = rmin;
        (*count)++;
        if (lmax < rmax)
            *max = rmax;
        else
            *max = lmax;
        (*count)++;
    }
}

void naivealg(int *arr, int size, int *max, int *min, int *count)
{
    *max = arr[0];
    *min = *max;
    for (int i = 1; i < size; i++)
    {
        (*count)++;

        if ((*max) < arr[i])
        {
            *max = arr[i];
        }
        (*count)++;
        if ((*min) > arr[i])
        {
            *min = arr[i];
        }
    }
}

int main()
{
    int sizes[] = {100, 1000, 10000, 20000, 50000, 100000};
    int tests = sizeof(sizes) / sizeof(sizes[0]);
    srand(time(NULL));
    printf("size\tNaive_Comparisons\tDivncon_Comparisons\n");

    for (int t = 0; t < tests; t++)
    {
        int n = sizes[t];
        int *arr = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % 100000;
        }

        int max, min;
        int naiveCount = 0;
        int dcCount = 0;

        naivealg(arr, n, &max, &min, &naiveCount);
        findviadivncon(arr, 0, n - 1, &max, &min, &dcCount);

        printf("%d\t%d\t\t\t%d\n", n, naiveCount, dcCount);

        free(arr);
    }

    return 0;
}
