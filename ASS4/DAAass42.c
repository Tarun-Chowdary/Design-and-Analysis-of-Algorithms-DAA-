#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 120000  

long long comp_mom = 0;
long long comp_qs = 0;


void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int findMedian(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++) {
            comp_mom++;
            if (arr[i] > arr[j])
                swap(&arr[i], &arr[j]);
        }
    return arr[n / 2];
}


int partitionMoM(int arr[], int l, int r, int x) {
    int i;
    for (i = l; i < r; i++) {
        comp_mom++;
        if (arr[i] == x) break;
    }
    swap(&arr[i], &arr[r]);

    i = l;
    for (int j = l; j < r; j++) {
        comp_mom++;
        if (arr[j] <= x) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}


int medianOfMedians(int arr[], int l, int r, int k) {
    if (k > 0 && k <= r - l + 1) {
        int n = r - l + 1;
        int i;
        int medians[(n + 4) / 5];

        for (i = 0; i < n / 5; i++)
            medians[i] = findMedian(arr + l + i * 5, 5);

        if (i * 5 < n) {
            medians[i] = findMedian(arr + l + i * 5, n % 5);
            i++;
        }

        int medOfMed = (i == 1) ? medians[0]
                                : medianOfMedians(medians, 0, i - 1, i / 2);

        int pos = partitionMoM(arr, l, r, medOfMed);

        if (pos - l == k - 1)
            return arr[pos];
        if (pos - l > k - 1)
            return medianOfMedians(arr, l, pos - 1, k);
        return medianOfMedians(arr, pos + 1, r, k - pos + l - 1);
    }
    return -1;
}


int partitionQS(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        comp_qs++;
        if (arr[j] <= pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}


int quickSelect(int arr[], int low, int high, int k) {
    if (low <= high) {
        int p = partitionQS(arr, low, high);
        if (p == k) return arr[p];
        else if (p > k) return quickSelect(arr, low, p - 1, k);
        else return quickSelect(arr, p + 1, high, k);
    }
    return -1;
}


int main() {
    int *data = malloc(N * sizeof(int));
    int *a1 = malloc(N * sizeof(int));
    int *a2 = malloc(N * sizeof(int));

    srand(time(NULL));

    
    for (int i = 0; i < N; i++) {
        data[i] = 10000 + rand() % 2000000;
        a1[i] = data[i];
        a2[i] = data[i];
    }

    FILE *fp = fopen("census_data.txt", "w");
    fprintf(fp, "n time_mom time_qs comp_mom comp_qs\n");

    clock_t start, end;
    double time_mom, time_qs;

  
    comp_mom = 0;
    start = clock();
    int mom_median = medianOfMedians(a1, 0, N - 1, N / 2 + 1);
    end = clock();
    time_mom = (double)(end - start) / CLOCKS_PER_SEC;

   
    comp_qs = 0;
    start = clock();
    int qs_median = quickSelect(a2, 0, N - 1, N / 2);
    end = clock();
    time_qs = (double)(end - start) / CLOCKS_PER_SEC;

 
    printf("\nMedian (Median of Medians) = %d", mom_median);
    printf("\nMedian (Quickselect)       = %d\n", qs_median);

    printf("\n--- Performance Comparison ---\n");
    printf("Algorithm\tTime(sec)\tComparisons\n");
    printf("MoM\t\t%f\t%lld\n", time_mom, comp_mom);
    printf("Quickselect\t%f\t%lld\n", time_qs, comp_qs);


    fprintf(fp, "%d %f %f %lld %lld\n", N, time_mom, time_qs, comp_mom, comp_qs);

    fclose(fp);
    free(data);
    free(a1);
    free(a2);

    return 0;
}

