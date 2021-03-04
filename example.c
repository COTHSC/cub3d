#include "cub3d.h"

int main()
{
    int r = 3;
    int c = 4;
    int i = 0;
    int nr = 5;
    int j;
    int count = 0;
    int *arr;

    arr = (int*)malloc(sizeof(int) * r * c);

    while (i < r)
    {
        j = 0;
        while (j < c)
        {
            *(arr + i * c + j) = ++count;
            j++;
        }
        i++;
    }



    arr = realloc(arr, sizeof(int) * nr * c);
    

    while (i < nr)
    {
        j = 0;
        while (j < c)
        {
            *(arr + i * c + j) = ++count;
            j++;
        }
        i++;
    }


    i = 0; 
    j = 0; 
    while (i < nr)
    {
        j = 0;
        while (j < c)
        {
            printf(" %i ", *(arr + i * c + j));
            j++;
        }
        i++;
        printf("\n");
    }
}
