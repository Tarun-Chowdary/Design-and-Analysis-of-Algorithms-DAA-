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

void union_set(int x, int y, int parent[], int rank[])
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
}

int main(void)
{
    int n;
    int valid = 1;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input.\n");
        valid = 0;
    }

    int *parent = NULL;
    int *rank = NULL;

    if (valid)
    {
        parent = (int *)malloc(n * sizeof(int));
        rank = (int *)malloc(n * sizeof(int));

        if (parent == NULL || rank == NULL)
        {
            printf("Memory allocation failed.\n");
            valid = 0;
        }
    }

    if (valid)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }

        int m;
        printf("Enter number of operations: ");
        scanf("%d", &m);

        if (m < 0)
        {
            printf("Invalid input.\n");
        }
        else
        {

            for (int i = 0; i < m; i++)
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

                    if (x < 0 || x >= n)
                        printf("Invalid student.\n");
                    else
                        printf("Representative of %d is %d\n", x, find_set(x, parent));
                }
                else if (type == 2)
                {
                    int x, y;
                    scanf("%d %d", &x, &y);

                    if (x < 0 || x >= n || y < 0 || y >= n)
                        printf("Invalid students.\n");
                    else
                        union_set(x, y, parent, rank);
                }
                else
                {
                    printf("Invalid operation type.\n");
                }
            }
        }

        printf("Final parent array:\n");
        for (int i = 0; i < n; i++)
            printf("%d ", parent[i]);
        printf("\n");

        printf("Final rank array:\n");
        for (int i = 0; i < n; i++)
            printf("%d ", rank[i]);
        printf("\n");
    }

    free(parent);
    free(rank);
    return 0;
}