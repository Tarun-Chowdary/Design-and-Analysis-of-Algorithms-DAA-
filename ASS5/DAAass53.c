#include <stdio.h>
#include <stdlib.h>

int find_set(int x, int parent[])
{
    if (parent[x] != x)
    {
        parent[x] = find_set(parent[x], parent);
    }
    return parent[x];
}

void union_set(int x, int y, int parent[], int rank[], int *components)
{
    int rootx = find_set(x, parent);
    int rooty = find_set(y, parent);

    if (rootx == rooty)
        return;

    if (rank[rootx] < rank[rooty])
        parent[rootx] = rooty;
    else if (rank[rootx] > rank[rooty])
        parent[rooty] = rootx;
    else
    {
        parent[rooty] = rootx;
        rank[rootx]++;
    }

    (*components)--;
}

int main(void)
{
    int N;
    int valid = 1;

    printf("Enter number of buildings: ");
    scanf("%d", &N);

    if (N <= 0)
    {
        printf("Invalid input.\n");
        valid = 0;
    }

    int *parent = NULL;
    int *rank = NULL;

    if (valid)
    {
        parent = (int *)malloc(N * sizeof(int));
        rank = (int *)malloc(N * sizeof(int));

        if (parent == NULL || rank == NULL)
        {
            printf("Memory allocation failed.\n");
            valid = 0;
        }
    }

    if (valid)
    {

        for (int i = 0; i < N; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }

        int components = N;

        int M;
        printf("Enter number of road operations: ");
        scanf("%d", &M);

        for (int i = 0; i < M; i++)
        {
            printf("Use operations:\n");
            printf("1)Find(x)\n");
            printf("2)Union(x, y)\n");
            int type;
            scanf("%d", &type);

            if (type == 1)
            {
                int x;
                scanf("%d", &x);

                if (x < 0 || x >= N)
                    printf("Invalid building.\n");
                else
                    printf("Representative of %d is %d\n", x, find_set(x, parent));
            }
            else if (type == 2)
            {
                int u, v;
                scanf("%d %d", &u, &v);

                if (u < 0 || u >= N || v < 0 || v >= N)
                {
                    printf("Invalid buildings.\n");
                }
                else
                {
                    union_set(u, v, parent, rank, &components);

                    if (components == 1)
                        printf("The city is now fully connected.\n");
                    else
                        printf("The city is not fully connected yet.\n");
                }
            }
            else
            {
                printf("Invalid operation type.\n");
            }
        }

        printf("Final parent array:\n");
        for (int i = 0; i < N; i++)
            printf("%d ", parent[i]);
        printf("\n");

        printf("Final rank array:\n");
        for (int i = 0; i < N; i++)
            printf("%d ", rank[i]);
        printf("\n");
    }

    free(parent);
    free(rank);
    return 0;
}