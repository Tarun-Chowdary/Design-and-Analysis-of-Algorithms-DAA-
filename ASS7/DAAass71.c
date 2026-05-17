#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define V 10


struct HeapNode {
    int vertex;
    int dist;
};

struct MinHeap {
    int size;
    struct HeapNode arr[100];
};

void swap(struct HeapNode *a, struct HeapNode *b) {
    struct HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(struct MinHeap *heap, int idx) {
    while (idx && heap->arr[(idx - 1) / 2].dist > heap->arr[idx].dist) {
        swap(&heap->arr[idx], &heap->arr[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

void heapifyDown(struct MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left].dist < heap->arr[smallest].dist)
        smallest = left;

    if (right < heap->size && heap->arr[right].dist < heap->arr[smallest].dist)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->arr[idx], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

void insertHeap(struct MinHeap *heap, int v, int dist) {
    heap->arr[heap->size].vertex = v;
    heap->arr[heap->size].dist = dist;
    heapifyUp(heap, heap->size);
    heap->size++;
}

struct HeapNode extractMin(struct MinHeap *heap) {
    struct HeapNode root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    heapifyDown(heap, 0);
    return root;
}




struct Node {
    int dest, weight;
    struct Node *next;
};

struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdgeList(struct Node* adj[], int u, int v, int w) {
    struct Node* newNode = createNode(v, w);
    newNode->next = adj[u];
    adj[u] = newNode;
}


void dijkstraList(struct Node* adj[], int src) {
    int dist[V];
    for (int i = 0; i < V; i++) dist[i] = INT_MAX;

    struct MinHeap heap;
    heap.size = 0;

    dist[src] = 0;
    insertHeap(&heap, src, 0);

    while (heap.size > 0) {
        struct HeapNode node = extractMin(&heap);
        int u = node.vertex;

        struct Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->dest;
            int w = temp->weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                insertHeap(&heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    printf("\n--- Adjacency List Result ---\n");
    for (int i = 0; i < V; i++)
        printf("Distance from %d to %d = %d\n", src, i, dist[i]);
}


void dijkstraMatrix(int graph[V][V], int src) {
    int dist[V], visited[V] = {0};

    for (int i = 0; i < V; i++) dist[i] = INT_MAX;

    struct MinHeap heap;
    heap.size = 0;

    dist[src] = 0;
    insertHeap(&heap, src, 0);

    while (heap.size > 0) {
        struct HeapNode node = extractMin(&heap);
        int u = node.vertex;

        if (visited[u]) continue;
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] != INT_MAX) {
                int w = graph[u][v];

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    insertHeap(&heap, v, dist[v]);
                }
            }
        }
    }

    printf("\n--- Adjacency Matrix Result ---\n");
    for (int i = 0; i < V; i++)
        printf("Distance from %d to %d = %d\n", src, i, dist[i]);
}


int main() {
    struct Node* adj[V];
    int graph[V][V];

    
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
        for (int j = 0; j < V; j++)
            graph[i][j] = INT_MAX;
    }

    
    addEdgeList(adj, 0, 1, 4);
    addEdgeList(adj, 0, 2, 1);
    addEdgeList(adj, 2, 1, 2);
    addEdgeList(adj, 1, 3, 1);
    addEdgeList(adj, 2, 3, 5);
    addEdgeList(adj, 3, 4, 3);
    addEdgeList(adj, 4, 5, 2);
    addEdgeList(adj, 5, 6, 1);
    addEdgeList(adj, 6, 7, 7);
    addEdgeList(adj, 7, 8, 2);
    addEdgeList(adj, 8, 9, 3);

    
    graph[0][1] = 4;
    graph[0][2] = 1;
    graph[2][1] = 2;
    graph[1][3] = 1;
    graph[2][3] = 5;
    graph[3][4] = 3;
    graph[4][5] = 2;
    graph[5][6] = 1;
    graph[6][7] = 7;
    graph[7][8] = 2;
    graph[8][9] = 3;

    int src = 0;

    clock_t start, end;

    start = clock();
    dijkstraList(adj, src);
    end = clock();
    printf("Time (List): %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    dijkstraMatrix(graph, src);
    end = clock();
    printf("Time (Matrix): %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}