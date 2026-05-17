#include <stdio.h>
#include <math.h>
#include <float.h>
#include <limits.h> 
#include <stdlib.h>   


void closestPair1D(int arr[], int n) {
    int minDist = INT_MAX;
    int p1 = 0, p2 = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = abs(arr[i] - arr[j]);

            if (dist < minDist) {
                minDist = dist;
                p1 = arr[i];
                p2 = arr[j];
            }
        }
    }

    printf("\n--- 1D Closest Pair ---\n");
    printf("Points: %d and %d\n", p1, p2);
    printf("Minimum Distance: %d\n", minDist);
}


struct Point {
    int x, y;
};


float distance(struct Point a, struct Point b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}


void closestPair2D(struct Point points[], int n) {
    float minDist = FLT_MAX;
    struct Point p1, p2;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float dist = distance(points[i], points[j]);

            if (dist < minDist) {
                minDist = dist;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }

    printf("\n--- 2D Closest Pair ---\n");
    printf("Points: (%d,%d) and (%d,%d)\n", p1.x, p1.y, p2.x, p2.y);
    printf("Minimum Distance: %.2f\n", minDist);
}


int main() {

  
    int arr[] = {1, 5, 3, 19, 18, 25};
    int n1 = sizeof(arr) / sizeof(arr[0]);

    closestPair1D(arr, n1);

    
    struct Point points[] = {
        {2, 3},
        {12, 30},
        {40, 50},
        {5, 1},
        {12, 10},
        {3, 4}
    };

    int n2 = sizeof(points) / sizeof(points[0]);

    closestPair2D(points, n2);

    return 0;
}