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
    int root_x = find_set(x, parent);
    int root_y = find_set(y, parent);

    if (root_x == root_y)
    {
        return;
    }

    if (rank[root_x] < rank[root_y])
    {
        parent[root_x] = root_y;
    }
    else if (rank[root_x] > rank[root_y])
    {
        parent[root_y] = root_x;
    }
    else
    {
        parent[root_y] = root_x;
        rank[root_x]++;
    }
}

int main(void)
{
    int n;
    int valid = 1;

    printf("Enter number of elements (n): ");
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
            printf("Memory not allocated.\n");
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

        int q;
        printf("Number of operations to be performed: ");
        scanf("%d", &q);

        if (q < 0)
        {
            printf("Invalid input.\n");
        }
        else
        {

            for (int i = 0; i < q; i++)
            {
                printf("Operations:\n");
                printf("1)Find(x)\n");
                printf("2)Union(x, y)\n");

                int type;
                scanf("%d", &type);

                if (type == 1)
                {
                    int x;
                    scanf("%d", &x);

                    if (x < 0 || x >= n)
                    {
                        printf("Invalid element.\n");
                    }
                    else
                    {
                        int rep = find_set(x, parent);
                        printf("Representative of %d is %d\n", x, rep);
                    }
                }
                else if (type == 2)
                {
                    int x, y;
                    scanf("%d %d", &x, &y);

                    if (x < 0 || x >= n || y < 0 || y >= n)
                    {
                        printf("Invalid elements.\n");
                    }
                    else
                    {
                        union_set(x, y, parent, rank);
                    }
                }
                else
                {
                    printf("Invalid operation type.\n");
                }
            }

            printf("Final parent array:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", parent[i]);
            }
            printf("\n");

            printf("Final rank array:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", rank[i]);
            }
            printf("\n");
        }
    }

    free(parent);
    free(rank);

    return 0;
}