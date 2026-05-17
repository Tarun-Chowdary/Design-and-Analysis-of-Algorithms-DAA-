#include <stdio.h>
#include <stdlib.h>

#define V 6
#define E 9

/* ---------------- EDGE STRUCTURE ---------------- */

struct Edge {
    int src, dest, weight;
};

/* ---------------- DISJOINT SET ---------------- */

int parent[V];
int rank[V];

void makeSet() {
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int v) {
    if (parent[v] != v)
        parent[v] = find(parent[v]);   // Path Compression
    return parent[v];
}

void unionSet(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);

    if (rank[rootU] < rank[rootV])
        parent[rootU] = rootV;
    else if (rank[rootU] > rank[rootV])
        parent[rootV] = rootU;
    else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

/* ---------------- SORT FUNCTION ---------------- */

int compare(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

/* ---------------- MAIN ---------------- */

int main() {

    struct Edge edges[E] = {
        {0,1,3},  // C1-C2
        {0,2,1},  // C1-C3
        {0,3,6},  // C1-C4
        {1,2,5},  // C2-C3
        {1,4,3},  // C2-C5
        {2,3,5},  // C3-C4
        {2,5,4},  // C3-C6
        {3,5,2},  // C4-C6
        {4,5,6}   // C5-C6
    };

    makeSet();

    // Step 1: Sort edges by weight
    qsort(edges, E, sizeof(edges[0]), compare);

    printf("\nEdges sorted in ascending order:\n");
    for (int i = 0; i < E; i++)
        printf("C%d - C%d  Cost = %d\n",
               edges[i].src + 1,
               edges[i].dest + 1,
               edges[i].weight);

    printf("\nEdges included in MST:\n");

    int edgeCount = 0;
    int totalCost = 0;

    for (int i = 0; i < E && edgeCount < V - 1; i++) {

        int u = edges[i].src;
        int v = edges[i].dest;

        if (find(u) != find(v)) {   // No cycle
            printf("C%d - C%d  Cost = %d\n",
                   u + 1, v + 1, edges[i].weight);

            totalCost += edges[i].weight;
            unionSet(u, v);
            edgeCount++;
        }
    }

    printf("\nTotal Minimum Cost = %d lakhs\n", totalCost);

    return 0;
}
