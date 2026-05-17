#include <stdio.h>
#include <stdlib.h>

int presentelement(int *arr, int size, int elem)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == elem)
        {
            return 1;
        }
    }
    return 0;
}

void unionset(int *uarr, int *arr, int *mp, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!presentelement(uarr, *mp, arr[i]))
        {
            uarr[*mp] = arr[i];
            (*mp)++;
        }
    }
}

int main()
{
    int disjoint;
    printf("\n ------------------ Enter no. of disjoint or overlapping set: ------------\n");
    scanf("%d", &disjoint);
    int mi = 0;
    int *uarr = (int *)malloc(sizeof(int) * 100 * disjoint);
    for (int i = 0; i < disjoint; i++)
    {
        int setsize;
        printf("Enter the  size of set:\n");
        scanf("%d", &setsize);
        int *arr = (int *)malloc(sizeof(int) * setsize);
        printf("Enter the elements of set:\n");
        for (int i = 0; i < setsize; i++)
        {
            scanf("%d", &arr[i]);
        }
        unionset(uarr, arr, &mi, setsize);
    }
    printf("\n ------- The union of the given sets is: --------\n");
    for (int i = 0; i < mi; i++)
    {
        printf("%d ", uarr[i]);
    }
    return 0;
}
