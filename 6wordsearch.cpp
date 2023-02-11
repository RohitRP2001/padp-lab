#include <stdio.h>
#include <string.h>
#include <omp.h>
#define MAX_LEN 1000

int main()
{
    char word[MAX_LEN];
    char text[MAX_LEN];
    int count = 0;
    
    printf("Enter the word to search: ");
    scanf("%s", word);
    
    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    
    #pragma omp parallel shared(count)
    {
        #pragma omp critical
        {
            while (fscanf(fp, "%s", text) != EOF)
            {
                if (strcmp(word, text) == 0)
                {
                    count++;
                }
            }
        }
    }
    fclose(fp);
    
    printf("'%s' occurs %d times in the input file.\n", word, count);
    
    return 0;
}
