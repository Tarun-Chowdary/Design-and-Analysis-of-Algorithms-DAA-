#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>


double findMedianSortedArrays(int A[], int n, int B[], int m) {
   
    if (n > m)
        return findMedianSortedArrays(B, m, A, n);

    int low = 0, high = n;

    while (low <= high) {
        int cut1 = (low + high) / 2;
        int cut2 = (n + m + 1) / 2 - cut1;

        int left1 = (cut1 == 0) ? INT_MIN : A[cut1 - 1];
        int left2 = (cut2 == 0) ? INT_MIN : B[cut2 - 1];
   
        int right1 = (cut1 == n) ? INT_MAX : A[cut1];
        int right2 = (cut2 == m) ? INT_MAX : B[cut2];

        if (left1 <= right2 && left2 <= right1) {
            
            if ((n + m) % 2 == 0)
                return ( (left1 > left2 ? left1 : left2) +
                         (right1 < right2 ? right1 : right2) ) / 2.0;
            else
                return (left1 > left2 ? left1 : left2);
        }
        else if (left1 > right2) {
            high = cut1 - 1;
        }
        else {
            low = cut1 + 1;
        }
    }
    return 0.0;
}


int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


int main() {
    int n = 50000;   
    int m = 60000;  

    int *A = malloc(n * sizeof(int));
    int *B = malloc(m * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < n; i++)
        A[i] = 100 + rand() % 100000;   // transaction range

    for (int i = 0; i < m; i++)
        B[i] = 100 + rand() % 100000;

  
    qsort(A, n, sizeof(int), cmp);
    qsort(B, m, sizeof(int), cmp);

    double median = findMedianSortedArrays(A, n, B, m);

    printf("Bank 1 transactions = %d\n", n);
    printf("Bank 2 transactions = %d\n", m);
    printf("Median of combined transaction data = %.2f\n", median);

    free(A);
    free(B);

    return 0;
}
