#include <stdio.h>
#include <limits.h>

#define V 10   
#define E 8    


struct Edge {
    int src, dest, weight;
};


void bellmanFord(struct Edge edges[], int src) {
    int dist[V];


    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }


    int hasNegativeCycle = 0;
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            hasNegativeCycle = 1;
            break;
        }
    }

    
    if (hasNegativeCycle) {
        printf("\n Negative Weight Cycle Detected!\n");
        printf("Shortest path is NOT defined.\n");
    } else {
        printf("\n--- Shortest Distances (Bellman-Ford) ---\n");
        for (int i = 0; i < V; i++)
            printf("Distance from %d to %d = %d\n", src, i, dist[i]);
    }
}


int main() {

    struct Edge edges[E] = {
        {0, 1, 4},
        {0, 2, 5},
        {1, 2, -2},
        {2, 3, 3},
        {3, 1, -6},  
        {3, 4, 2},
        {4, 5, 1},
        {5, 6, 2}
    };

    int src = 0;

    bellmanFord(edges, src);

    return 0;
}