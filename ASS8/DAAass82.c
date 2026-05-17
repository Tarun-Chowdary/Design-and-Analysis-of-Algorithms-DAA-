#include <stdio.h>
#include <limits.h>
#include <time.h>


int mcm_recursive(int arr[], int i, int j) {
    if (i == j)
        return 0;

    int min = INT_MAX;

    for (int k = i; k < j; k++) {
        int cost = mcm_recursive(arr, i, k)
                 + mcm_recursive(arr, k + 1, j)
                 + arr[i - 1] * arr[k] * arr[j];

        if (cost < min)
            min = cost;
    }

    return min;
}


int mcm_dp(int arr[], int n) {
    int dp[n][n];

    
    for (int i = 1; i < n; i++)
        dp[i][i] = 0;

    
    for (int len = 2; len < n; len++) {
        for (int i = 1; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j]
                         + arr[i - 1] * arr[k] * arr[j];

                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }

    return dp[1][n - 1];
}


int main() {
    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int arr[n + 1];

    printf("Enter dimensions (size %d):\n", n + 1);
    for (int i = 0; i <= n; i++) {
        scanf("%d", &arr[i]);
    }

   
    clock_t start1 = clock();
    int result1 = mcm_recursive(arr, 1, n);
    clock_t end1 = clock();

    
    clock_t start2 = clock();
    int result2 = mcm_dp(arr, n + 1);
    clock_t end2 = clock();

    
    printf("\nMinimum multiplications (Recursive): %d\n", result1);
    printf("Time (Recursive): %lf sec\n",
           (double)(end1 - start1) / CLOCKS_PER_SEC);

    printf("\nMinimum multiplications (DP): %d\n", result2);
    printf("Time (DP): %lf sec\n",
           (double)(end2 - start2) / CLOCKS_PER_SEC);

    return 0;
}