#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void recognize(char *text, char *pattern, int *postion, int *count)
{
    int n = strlen(text);
    int m = strlen(pattern);

    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        while (j < m && text[i + j] == pattern[j])
        {
            j++;
        }

        if (j == m)
        {
            postion[*count] = i;
            (*count)++;
        }
    }
}

int main()
{
    char *sourcestring = (char *)malloc(200 * sizeof(char));
    char *patternstring = (char *)malloc(100 * sizeof(char));

    printf("\n--- Enter the source string containing a pattern: ---\n");
    scanf("%s", sourcestring);

    printf("Enter the pattern to recognize:\n");
    scanf("%s", patternstring);

    int position[200];
    int count = 0;

    recognize(sourcestring, patternstring, position, &count);

    if (count == 0)
    {
        printf("\n-----Pattern not found----\n");
    }
    else
    {
        printf("\n --------- Pattern found at positions: --------\n");
        for (int i = 0; i < count; i++)
        {
            printf(" postion[%d]\n", position[i]);
        }
    }

    free(sourcestring);
    free(patternstring);

    return 0;
}
