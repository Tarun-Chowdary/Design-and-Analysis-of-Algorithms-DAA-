#include <stdio.h>
#include <stdlib.h>
int presentelem(int *arr, int size, int elem)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == elem)
            return 1;
    }
    return 0;
}
int isSubset(int *A, int *B, int sizeA, int sizeB)
{
    if (sizeA > sizeB)
        return 0;

    for (int i = 0; i < sizeA; i++)
    {
        if (!presentelem(B, sizeB, A[i]))
            return 0;
    }
    return 1;
}

int main()
{
    int n, m, elem;
    printf("\n------ Enter the size of Set A ------\n");
    scanf("%d", &n);

    int *new = (int *)malloc(n * sizeof(int));

    int i = 0;
    printf("Enter elements of Set A:\n");
    while (i < n)
    {
        scanf("%d", &elem);
        if (!presentelem(new, i, elem))
        {
            new[i] = elem;
            i++;
        }
        else
        {
            printf("duplicate element founded\n");
        }
    }
    printf("\n------ Enter the size of Set B ------\n");
    scanf("%d", &m);
    int *arr = (int *)malloc(m * sizeof(int));
    i = 0;
    printf("Enter elements of Set B:\n");
    while (i < m)
    {
        scanf("%d", &elem);
        if (!presentelem(arr, i, elem))
        {
            arr[i] = elem;
            i++;
        }
        else
        {
            printf("duplicate element founded\n");
        }
    }
    int final = isSubset(new, arr, n, m);

    if (final && n == m)
    {
        printf("\nSet A is equal to Set B\n");
    }
    else if (final)
    {
        printf("\n----------Set A is a proper subset of Set B------\n");
    }
    else
    {
        printf("\n---------Set A is not a subset of Set B--------\n");
    }
    free(new);
    free(arr);

    return 0;
}
