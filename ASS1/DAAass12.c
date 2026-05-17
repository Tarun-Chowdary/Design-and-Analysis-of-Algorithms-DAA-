#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50000


int linearSearch(int arr[], int key, int *comparisons) {
    for (int i = 0; i < SIZE; i++) {
        (*comparisons)++;
        if (arr[i] == key)
            return i;
    }
    return -1;
}

int binarySearch(int arr[], int key, int *comparisons) {
    int low = 0, high = SIZE - 1;

    while (low <= high) {
        (*comparisons)++;
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int arr[SIZE], key;
    int comparisons;
    clock_t start, end;
    double time_taken;

    srand(time(NULL));

   
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % 100000;

    printf("Enter element to search: ");
    scanf("%d", &key);

   
    comparisons = 0;
    start = clock();
    int pos1 = linearSearch(arr, key, &comparisons);
    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nLinear Search:");
    printf("\nPosition: %d", pos1);
    printf("\nComparisons: %d", comparisons);
    printf("\nTime: %f seconds\n", time_taken);
    qsort(arr, SIZE, sizeof(int), compare);

    
    comparisons = 0;
    start = clock();
    int pos2 = binarySearch(arr, key, &comparisons);
    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nBinary Search:");
    printf("\nPosition: %d", pos2);
    printf("\nComparisons: %d", comparisons);
    printf("\nTime: %f seconds\n", time_taken);

    return 0;
}
