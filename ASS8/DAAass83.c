#include <stdio.h>
#include <time.h>


int knapsack_recursive(int W, int wt[], int val[], int n) {
    if (n == 0 || W == 0)
        return 0;

    if (wt[n - 1] > W)
        return knapsack_recursive(W, wt, val, n - 1);

    int include = val[n - 1] +
        knapsack_recursive(W - wt[n - 1], wt, val, n - 1);

    int exclude =
        knapsack_recursive(W, wt, val, n - 1);

    return (include > exclude) ? include : exclude;
}


int knapsack_dp(int W, int wt[], int val[], int n) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {

            if (i == 0 || w == 0)
                dp[i][w] = 0;

            else if (wt[i - 1] <= w) {
                int include = val[i - 1] +
                              dp[i - 1][w - wt[i - 1]];
                int exclude = dp[i - 1][w];

                dp[i][w] = (include > exclude) ? include : exclude;
            }

            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}


int main() {
    int n, W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int wt[n], val[n];

    printf("Enter weights:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &wt[i]);

    printf("Enter values:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);

    printf("Enter capacity: ");
    scanf("%d", &W);

    
    clock_t start1 = clock();
    int res1 = knapsack_recursive(W, wt, val, n);
    clock_t end1 = clock();

    
    clock_t start2 = clock();
    int res2 = knapsack_dp(W, wt, val, n);
    clock_t end2 = clock();

    
    printf("\nMaximum Profit (Recursive): %d\n", res1);
    printf("Time (Recursive): %lf sec\n",
           (double)(end1 - start1) / CLOCKS_PER_SEC);

    printf("\nMaximum Profit (DP): %d\n", res2);
    printf("Time (DP): %lf sec\n",
           (double)(end2 - start2) / CLOCKS_PER_SEC);

    return 0;
}