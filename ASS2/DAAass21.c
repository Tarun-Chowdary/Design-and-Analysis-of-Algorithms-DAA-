#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int Largest4(int *arr, int n)
{

	int largest1 = arr[0], largest2 = INT_MIN, largest3 = INT_MIN, largest4 = INT_MIN;
	int i = 1;
	// we will find 4th largest by finding 1st largest .
	// with 1st largest we will find 2nd largest and  so on we will find 4th largest .
	while (i < n)
	{
		if (arr[i] > largest1)
		{
			largest4 = largest3;
			largest3 = largest2;
			largest2 = largest1;
			largest1 = arr[i];
		}
		else if (arr[i] > largest2)
		{
			largest4 = largest3;
			largest3 = largest2;
			largest2 = arr[i];
		}
		else if (arr[i] > largest3)
		{
			largest4 = largest3;
			largest3 = arr[i];
		}
		else if (arr[i] > largest4)
		{
			largest4 = arr[i];
		}
		i++;
	}
	return largest4;
}

int smallest3(int *arr, int size)
{
	int small1 = arr[0], small2 = INT_MAX, small3 = INT_MAX;
	int n = 1;
	// we will find 3rd smallest by finding 1st smallest.
	// with 1st smallest we will find 2nd smallest and so on we will find 3rd smallest.
	while (n < size)
	{
		if (arr[n] < small1)
		{
			small3 = small2;
			small2 = small1;
			small1 = arr[n];
		}
		else if (arr[n] < small2)
		{
			small3 = small2;
			small2 = arr[n];
		}
		else if (arr[n] < small3)
		{
			small3 = arr[n];
		}
		n++;
	}
	return small3;
}

int main()
{
	int n;
	printf("enter the size of the array(it must be larger than 10):\n");
	scanf("%d", &n);
	if (n < 10)
	{
		printf("the size of the array must be larger than 10\n");
		return -1;
	}

	int *arr;
	arr = (int *)malloc(sizeof(int) * n);

	srand(time(NULL));

	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() - RAND_MAX / 2;
		printf("---The Generated Array Of Index %d IS  %d ---\n", i + 1, arr[i]);
	}

	int l4 = Largest4(arr, n);
	int s3 = smallest3(arr, n);
	printf("The fourth largest number is : %d\n", l4);
	printf("The third smallest number is : %d\n", s3);
	return 0;
}