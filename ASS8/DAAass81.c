#include <stdio.h>
#include <time.h>


int fib_recursive(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}


int fib_dp(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}


int fib_optimized(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int a = 0, b = 1, c;

    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}


int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    
    clock_t start1 = clock();
    int res1 = fib_recursive(n);
    clock_t end1 = clock();

   
    clock_t start2 = clock();
    int res2 = fib_dp(n);
    clock_t end2 = clock();

    
    clock_t start3 = clock();
    int res3 = fib_optimized(n);
    clock_t end3 = clock();

    
    printf("\nFibonacci using Recursive = %d", res1);
    printf("\nTime (Recursive) = %lf seconds",
           (double)(end1 - start1) / CLOCKS_PER_SEC);

    printf("\n\nFibonacci using DP = %d", res2);
    printf("\nTime (DP) = %lf seconds",
           (double)(end2 - start2) / CLOCKS_PER_SEC);

    printf("\n\nFibonacci using Optimized DP = %d", res3);
    printf("\nTime (Optimized) = %lf seconds",
           (double)(end3 - start3) / CLOCKS_PER_SEC);

    return 0;
}