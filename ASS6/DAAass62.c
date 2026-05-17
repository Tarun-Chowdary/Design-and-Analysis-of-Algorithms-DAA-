#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6   // Number of cities

/* -------------------- ADJACENCY LIST -------------------- */

struct Node {
    int dest;
    int weight;
    struct Node* next;
};

struct Node* adj[V];

struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = adj[src];
    adj[src] = newNode;

    newNode = createNode(src, weight);  // Undirected
    newNode->next = adj[dest];
    adj[dest] = newNode;
}

/* -------------------- MIN HEAP -------------------- */

struct MinHeapNode {
    int vertex;
    int key;
};

struct MinHeap {
    int size;
    int pos[V];
    struct MinHeapNode* array[V];
};

struct MinHeapNode* newHeapNode(int v, int key) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->vertex = v;
    node->key = key;
    return node;
}

void swapHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left]->key < heap->array[smallest]->key)
        smallest = left;

    if (right < heap->size && heap->array[right]->key < heap->array[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        heap->pos[heap->array[smallest]->vertex] = idx;
        heap->pos[heap->array[idx]->vertex] = smallest;
        swapHeapNode(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

int isEmpty(struct MinHeap* heap) {
    return heap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* heap) {
    if (isEmpty(heap))
        return NULL;

    struct MinHeapNode* root = heap->array[0];
    struct MinHeapNode* lastNode = heap->array[heap->size - 1];
    heap->array[0] = lastNode;

    heap->pos[root->vertex] = heap->size - 1;
    heap->pos[lastNode->vertex] = 0;

    heap->size--;
    minHeapify(heap, 0);

    return root;
}

void decreaseKey(struct MinHeap* heap, int v, int key) {
    int i = heap->pos[v];
    heap->array[i]->key = key;

    while (i && heap->array[i]->key < heap->array[(i - 1) / 2]->key) {
        heap->pos[heap->array[i]->vertex] = (i - 1) / 2;
        heap->pos[heap->array[(i - 1) / 2]->vertex] = i;
        swapHeapNode(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/* -------------------- PRIM'S ALGORITHM -------------------- */

void primMST() {

    int parent[V];        // Stores MST
    int key[V];           // Minimum weight edge
    int inMST[V] = {0};   // Track included vertices
    int order[V];         // Order of inclusion

    struct MinHeap heap;
    heap.size = V;

    for (int v = 0; v < V; v++) {
        key[v] = INT_MAX;
        heap.array[v] = newHeapNode(v, key[v]);
        heap.pos[v] = v;
    }

    // Start from C1 (vertex 0)
    key[0] = 0;
    decreaseKey(&heap, 0, 0);
    parent[0] = -1;

    int count = 0;

    while (!isEmpty(&heap)) {
        struct MinHeapNode* minNode = extractMin(&heap);
        int u = minNode->vertex;

        inMST[u] = 1;
        order[count++] = u;

        struct Node* temp = adj[u];
        while (temp) {
            int v = temp->dest;

            if (!inMST[v] && temp->weight < key[v]) {
                key[v] = temp->weight;
                parent[v] = u;
                decreaseKey(&heap, v, key[v]);
            }
            temp = temp->next;
        }
    }

    /* ---------- DISPLAY RESULTS ---------- */

    int totalCost = 0;
    printf("\nEdges in Minimum Spanning Tree:\n");
    for (int i = 1; i < V; i++) {
        printf("C%d - C%d  Cost = %d\n",
               parent[i] + 1, i + 1, key[i]);
        totalCost += key[i];
    }

    printf("\nTotal Minimum Cost = %d lakhs\n", totalCost);

    printf("\nOrder of vertices added:\n");
    for (int i = 0; i < V; i++)
        printf("C%d ", order[i] + 1);
    printf("\n");
}

/* -------------------- MAIN -------------------- */

int main() {

    for (int i = 0; i < V; i++)
        adj[i] = NULL;

    // Add given edges
    addEdge(0,1,3);  // C1-C2
    addEdge(0,2,1);  // C1-C3
    addEdge(0,3,6);  // C1-C4
    addEdge(1,2,5);  // C2-C3
    addEdge(1,4,3);  // C2-C5
    addEdge(2,3,5);  // C3-C4
    addEdge(2,5,4);  // C3-C6
    addEdge(3,5,2);  // C4-C6
    addEdge(4,5,6);  // C5-C6

    primMST();

    return 0;
}
