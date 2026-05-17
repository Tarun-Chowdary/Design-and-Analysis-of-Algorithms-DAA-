#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20
#define SPARSE_EDGES 120
#define DENSE_EDGES 190
#define MAX_WEIGHT 100

/* --------------------- STRUCTURES --------------------- */

// Node for adjacency list (weighted)
struct Node
{
    int vertex;
    int weight;
    struct Node *next;
};

/* --------------------- FUNCTIONS --------------------- */
// Create new node
struct Node *createNode(int v, int w)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

// Add edge to adjacency list
void addEdgeList(struct Node *adj[], int u, int v, int w)
{
    struct Node *newNode = createNode(v, w);
    newNode->next = adj[u];
    adj[u] = newNode;

    // Undirected graph
    newNode = createNode(u, w);
    newNode->next = adj[v];
    adj[v] = newNode;
}

// Check if edge already exists in matrix
int edgeExists(int matrix[N][N], int u, int v)
{
    return matrix[u][v] != 0;
}

/* --------------------- MAIN --------------------- */

int main()
{

    srand(time(NULL));

    /* ====================================================
       SPARSE GRAPH (Adjacency List)
    ==================================================== */

    struct Node *sparseList[N];
    int sparseCheck[N][N] = {0}; // To avoid duplicate edges

    for (int i = 0; i < N; i++)
        sparseList[i] = NULL;

    int count = 0;
    while (count < SPARSE_EDGES)
    {
        int u = rand() % N;
        int v = rand() % N;

        if (u != v && !sparseCheck[u][v])
        {
            int weight = rand() % MAX_WEIGHT + 1;

            addEdgeList(sparseList, u, v, weight);
            sparseCheck[u][v] = sparseCheck[v][u] = 1;
            count++;
        }
    }

    printf("\n===== SPARSE GRAPH (Adjacency List - Weighted) =====\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d -> ", i);
        struct Node *temp = sparseList[i];
        while (temp)
        {
            printf("(%d, w=%d) ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("desnse\n");
    /* ====================================================
       DENSE GRAPH (Adjacency Matrix)
    ==================================================== */

    int denseMatrix[N][N] = {0};
    int denseWeight[N][N] = {0};

    count = 0;
    while (count < DENSE_EDGES)
    {
        int u = rand() % N;
        int v = rand() % N;

        if (u != v && denseMatrix[u][v] == 0)
        {
            int weight = rand() % MAX_WEIGHT + 1;

            denseMatrix[u][v] = denseMatrix[v][u] = 1;      // Unweighted
            denseWeight[u][v] = denseWeight[v][u] = weight; // Weighted
            count++;
        }
    }

    printf("\n===== DENSE GRAPH (Adjacency Matrix - Unweighted) =====\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", denseMatrix[i][j]);
        printf("\n");
    }

    printf("\n===== DENSE GRAPH (Adjacency Matrix - Weighted) =====\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%3d ", denseWeight[i][j]);
        printf("\n");
    }

    return 0;
}
