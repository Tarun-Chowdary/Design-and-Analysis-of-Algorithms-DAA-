#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ======================= STRUCTURES ======================= */

struct Edge {
    int src, dest, weight;
};

/* ======================= UNION-FIND ======================= */

int *parent, *rankArr;

void makeSet(int n) {
    parent = (int*)malloc(n * sizeof(int));
    rankArr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }
}

int findSet(int v) {
    if (parent[v] != v)
        parent[v] = findSet(parent[v]);
    return parent[v];
}

void unionSet(int u, int v) {
    int rootU = findSet(u);
    int rootV = findSet(v);

    if (rankArr[rootU] < rankArr[rootV])
        parent[rootU] = rootV;
    else if (rankArr[rootU] > rankArr[rootV])
        parent[rootV] = rootU;
    else {
        parent[rootV] = rootU;
        rankArr[rootU]++;
    }
}

/* ======================= KRUSKAL (FOR G1) ======================= */

int compare(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

int kruskal(struct Edge edges[], int V, int E, struct Edge mst[]) {
    makeSet(V);
    qsort(edges, E, sizeof(struct Edge), compare);

    int count = 0, total = 0;

    for (int i = 0; i < E && count < V - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        if (findSet(u) != findSet(v)) {
            mst[count++] = edges[i];
            total += edges[i].weight;
            unionSet(u, v);
        }
    }
    return total;
}

/* ======================= PRIM (FOR G2) ======================= */

int prim(int **graph, int V, struct Edge mst[]) {
    int *key = (int*)malloc(V * sizeof(int));
    int *parentArr = (int*)malloc(V * sizeof(int));
    int *inMST = (int*)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX;

    key[0] = 0;
    parentArr[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int min = INT_MAX, u = -1;

        for (int v = 0; v < V; v++)
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                u = v;
            }

        inMST[u] = 1;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parentArr[v] = u;
                key[v] = graph[u][v];
            }
    }

    int total = 0;
    for (int i = 1; i < V; i++) {
        mst[i - 1].src = parentArr[i];
        mst[i - 1].dest = i;
        mst[i - 1].weight = graph[i][parentArr[i]];
        total += mst[i - 1].weight;
    }

    free(key);
    free(parentArr);
    free(inMST);

    return total;
}

/* ======================= MAIN ======================= */

int main() {

    int V1, E1, V2, E2;

    printf("Enter vertices and edges for G1 (sparse): ");
    scanf("%d %d", &V1, &E1);

    struct Edge *edges1 = (struct Edge*)malloc(E1 * sizeof(struct Edge));
    printf("Enter edges (src dest weight) for G1:\n");
    for (int i = 0; i < E1; i++)
        scanf("%d %d %d", &edges1[i].src, &edges1[i].dest, &edges1[i].weight);

    printf("Enter vertices and edges for G2 (dense): ");
    scanf("%d %d", &V2, &E2);

    int **graph2 = (int**)malloc(V2 * sizeof(int*));
    for (int i = 0; i < V2; i++) {
        graph2[i] = (int*)calloc(V2, sizeof(int));
    }

    printf("Enter edges (src dest weight) for G2:\n");
    for (int i = 0; i < E2; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph2[u][v] = graph2[v][u] = w;
    }

    int u_bridge, v_bridge, w_bridge;
    printf("Enter mandatory high-capacity edge (u v weight): ");
    scanf("%d %d %d", &u_bridge, &v_bridge, &w_bridge);

    /* ---- Compute MST of G1 using Kruskal ---- */
    struct Edge *mst1 = (struct Edge*)malloc((V1 - 1) * sizeof(struct Edge));
    int cost1 = kruskal(edges1, V1, E1, mst1);

    /* ---- Compute MST of G2 using Prim ---- */
    struct Edge *mst2 = (struct Edge*)malloc((V2 - 1) * sizeof(struct Edge));
    int cost2 = prim(graph2, V2, mst2);

    /* ---- Combine both MSTs with mandatory edge ---- */
    int totalCost = cost1 + cost2 + w_bridge;

    printf("\n===== Final Global MST =====\n");

    printf("\nMST of G1 (Kruskal):\n");
    for (int i = 0; i < V1 - 1; i++)
        printf("%d - %d (Cost %d)\n", mst1[i].src, mst1[i].dest, mst1[i].weight);

    printf("\nMST of G2 (Prim):\n");
    for (int i = 0; i < V2 - 1; i++)
        printf("%d - %d (Cost %d)\n", mst2[i].src, mst2[i].dest, mst2[i].weight);

    printf("\nMandatory High-Capacity Edge:\n");
    printf("%d - %d (Cost %d)\n", u_bridge, v_bridge, w_bridge);

    printf("\nTotal Cost of Global MST = %d\n", totalCost);

    return 0;
}
