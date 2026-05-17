#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, num, min, max;
    FILE *fp;
    printf("Enter number of integers: ");
    scanf("%d", &n);
    fp = fopen("numbers.txt", "w");
    if (fp == NULL)
    {
        printf("File error\n");
        return -1;
    }
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        num = rand() % 1000;
        fprintf(fp, "%d ", num);
    }
    fclose(fp);
    fp = fopen("numbers.txt", "r");
    printf("\nNumbers read from file:\n");

    fscanf(fp, "%d", &num);
    min = max = num;
    printf("%d ", num);
    for (int i = 1; i < n; i++)
    {
        fscanf(fp, "%d", &num);
        printf("%d ", num);
        if (num < min)
            min = num;
        if (num > max)
            max = num;
    }
    fclose(fp);
    printf("\n\nMinimum value: %d", min);
    printf("\nMaximum value: %d\n", max);
    return 0;
}
