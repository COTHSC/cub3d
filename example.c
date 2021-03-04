#include "cub3d.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, int size, int newsize)
{
	char	*str;
	char	*new;
	int		i;

	str = (char*)ptr;
	if (!(new = (char*)malloc(sizeof(char) * newsize + 1)))
	{
		if (ptr && size != 0)
			free(ptr);
		return (NULL);
	}
	i = -1;
	while (++i < size)
		*(new + i) = *(str + i);
	while (i < newsize)
		*(new + i++) = '\0';
	if (ptr && size != 0)
		free(ptr);
	return (new);
}

int main()
{
    int r = 3;
    int c = 4;
    int i = 0;
    int nr = 5;
    int j;
    int count = 0;
    int *arr;
    int length;



    length = 0;
    arr = NULL;
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

    while (arr[length])
        length++;

    printf("this is length: %i \n", length);
    arr = (int *)ft_realloc(arr, sizeof(int) * r * c, sizeof(int) * nr * c);

    
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
    
    while (arr[length])
        length++;

    printf("this is length: %i \n", length);
    *(arr + c * c + 0) = 10000;

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
