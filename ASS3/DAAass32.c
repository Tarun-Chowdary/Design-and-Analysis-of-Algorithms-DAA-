#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;
int max_depth = 0;
int current_depth = 0;


void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        comparisons++; 

        if (arr[j] <= pivot) { 
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
int randomizedPartition(int arr[], int low, int high) {
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high);
}

void standardQuickSort(int arr[], int low, int high) {
    current_depth++;
    if (current_depth > max_depth) max_depth = current_depth;

    if (low < high) {
        int pi = partition(arr, low, high);
        standardQuickSort(arr, low, pi - 1);
        standardQuickSort(arr, pi + 1, high);
    }
    current_depth--;
}

void randomizedQuickSort(int arr[], int low, int high) {
    current_depth++;
    if (current_depth > max_depth) max_depth = current_depth;

    if (low < high) {
        int pi = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
    current_depth--;
}


void generateArray(int arr[], int n, int duplicate_percentage) {
    
    int unique_count = n * (100 - duplicate_percentage) / 100;
    if (unique_count < 1) unique_count = 1;

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % unique_count;
    }
}

int main() {
    int n = 100000;
    int *arr = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));
    
    srand(time(NULL));
    clock_t start, end;
    double cpu_time;

    FILE *fp = fopen("duplicate.txt", "w");
    if (!fp) { printf("Error opening file.\n"); return 1; }

    int percentages[] = {90, 50, 10}; 
    const char *names[] = {"Array-I (90% Dup)", "Array-II (50% Dup)", "Array-III (10% Dup)"};

    printf("Running Duplicate Keys Analysis\n");
    printf("%-20s , %-10s , %-12s , %-10s , %-10s\n", "Dataset", "Algorithm", "Comparisons", "Recursion", "Time(s)");
    for (int k = 0; k < 3; k++) {
        int dup_pct = percentages[k];

        
        generateArray(arr, n, dup_pct);


        for(int i=0; i<n; i++) temp[i] = arr[i]; 
        
        comparisons = 0;
        max_depth = 0;
        current_depth = 0;
        
        start = clock();
        standardQuickSort(temp, 0, n - 1);
        end = clock();
        cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "%d Standard %lld %d %f\n", dup_pct, comparisons, max_depth, cpu_time);
        printf("%-20s | Standard   | %-12lld | %-10d | %f\n", names[k], comparisons, max_depth, cpu_time);

        for(int i=0; i<n; i++) temp[i] = arr[i]; 
        
        comparisons = 0;
        max_depth = 0;
        current_depth = 0;
        
        start = clock();
        randomizedQuickSort(temp, 0, n - 1);
        end = clock();
        cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "%d Randomized %lld %d %f\n", dup_pct, comparisons, max_depth, cpu_time);
        printf("%-20s | Randomized | %-12lld | %-10d | %f\n", names[k], comparisons, max_depth, cpu_time);
        
    }

    fclose(fp);
    free(arr);
    free(temp);
    
    

    return 0;
}