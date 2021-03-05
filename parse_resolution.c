#include "cub3d.h"
#include "./libft/libft.h"
#include <fcntl.h>


int     innit_arrayf(char **farray, fptr functions[8])
{
    int i;

    i = 0;
    while(i < 8)
        farray[i++] = malloc(sizeof(char) * 3);
    ft_strlcpy(farray[0], "R ", 3);
    ft_strlcpy(farray[1], "NO", 3);
    ft_strlcpy(farray[2], "SO", 3);
    ft_strlcpy(farray[3], "WE", 3);
    ft_strlcpy(farray[4], "EA", 3);
    ft_strlcpy(farray[5], "S ", 3);
    ft_strlcpy(farray[6], "F ", 3);
    ft_strlcpy(farray[7], "C ", 3);

    functions[0] = &parse_resolution;
    functions[1] = &parse_paths;
    functions[2] = &parse_paths;
    functions[3] = &parse_paths;
    functions[4] = &parse_paths;
    functions[5] = &parse_sprite;
    functions[6] = &parse_colors;
    functions[7] = &parse_colors;
    return (1);
}


int     parse_lines(t_vars *vars, int fd)
{
    char **farray;
    char *buf;
    int i;
    int c;
    int h;
    fptr functions[8];
    
    h = 0;
    farray = malloc(sizeof(char *) * 8);
    innit_arrayf(farray, functions);
    i = 1;
    while (i != 0)
    {
        i = get_next_line(fd, &buf);
        c = 0;
        while(c < 8)
        {
            if(ft_strnstr(buf, farray[c], 3))
                (*functions[c])(vars->res, buf);
            else if (ft_isdigit(buf[0]))
            {
                parse_map(vars, buf, fd, h++);
                break;
            }

            c++;
        }
    }
    return 1;
}

int     parse_colors(t_res *res, char *buf)
{
    int r;
    int g;
    int b;
    int i = 0;
    int color;
    color = 0; 

    if(!buf)
        return 0;
    while (!ft_isdigit(buf[i]))
        i++;
    r = ft_atoi(&buf[i]);
    while (buf[i] != ',')
        i++;
    g = ft_atoi(&buf[i + 1]);
    while (buf[i] != ',')
        i++;
    b = ft_atoi(&buf[i + 1]);
    color = ft_get_color(r, g, b);
    if (ft_strnstr(buf, "F ", 3))
        res->F = color;
    else if (ft_strnstr(buf, "C ", 3))
        res->C = color;
    return 1;
}

int     ft_get_color(int r, int g, int b)
{
    int color;

    color = 0;

    color += r << 16;
    color += g << 8;
    color += b;

    return color;
}


int     parse_resolution(t_res *res, char *buf)
{
    int i;

    if(!buf)
        return 0;
    i = 0;
    while(!ft_isdigit(buf[i]))
        i++;
    res->w = ft_atoi(&buf[i]);

    while(ft_isdigit(buf[i]))
        i++;
    while(!ft_isdigit(buf[i]))
        i++;
    res->h = ft_atoi(&buf[i]);
    return 1;
}

int     parse_paths(t_res *res, char *buf)
{
    int i;
    int length;
    int start;

    if(!buf)
        return 0;

    i = 0;
    length = 0;
    while(buf[i] != ' ')
        i++;
    while(buf[i] == ' ')
        i++;
    start = i;
    while (buf[i] && buf[i] != '\n')
    {
        length++;
        i++;
    }
    if(ft_strnstr(buf, "NO", 3))
    {
        res->NO = malloc(length + 1);
        ft_strlcpy(res->NO, &buf[start], length); 
    }
    else if(ft_strnstr(buf, "SO", 3))
    {
        res->SO = malloc(length + 1);
        ft_strlcpy(res->SO, &buf[start], length); 
    }
    else if(ft_strnstr(buf, "WE", 3))
    {
        res->WE = malloc(length + 1);
        ft_strlcpy(res->WE, &buf[start], length); 
    }
    else if(ft_strnstr(buf, "EA", 3))
    {
        res->EA = malloc(length + 1);
        ft_strlcpy(res->EA, &buf[start], length); 
    }
    return 1;
}


int     parse_sprite(t_res *res, char *buf)
{
    int i;
    int length;
    int start;

    if(!buf)
        return 0;
    i = 0;
    length = 0;
    while(buf[i] != ' ')
        i++;
    while(buf[i] == ' ')
        i++;
    start = i;
    while (buf[i] && buf[i] != '\n')
    {
        length++;
        i++;
    }
    res->S = malloc(length + 1);
    ft_strlcpy(res->S, &buf[start], length); 
    return 1;
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

int     array_length(int *array)
{
    int length;

    length = 0;
    while (array[length])
        length++;
    return (length);
}

int     save_position(t_vars *vars, char c, int h, int i)
{
    vars->p->px = (double)i;
    vars->p->py = (double)h;
    vars->p->dx = -1;
    vars->p->dy = 0;
    vars->p->plx =  0;
    vars->p->ply = 0.66;
    vars->p->ms = 0.03;
    vars->p->rs = 0.03;
    return (1);
}

int     sia(int *array, int h)
{
    int result;
    int count;

    result = 0;
    count = 0;

    while (count < h)
    {
        result = result + array[count];
        count++;
    }
    return (result);
}

int     parse_map(t_vars *vars, char *buf, int fd, int h)
{
    int length;
    int j;
    int i;
    static int nc;
    static int arlength;


    length = ft_strlen(buf);
 
    if (h == 0)
    { 
        nc = 0;
        arlength = length * sizeof(int);
	    vars->collumn = (int *)malloc(sizeof(int));
	    vars->collumn[nc] = 24;
        vars->map = (int *)malloc(sizeof(int) * length * (h + 1));
    }
    else
    {
	    vars->collumn = (int *)ft_realloc(vars->collumn, sizeof(int) * (nc + 1), sizeof(int) * (nc + 2));
	    vars->collumn[++nc] = length;
        vars->map = (int *)ft_realloc(vars->map, arlength, sizeof(int) * length + arlength);
        arlength += length * sizeof(int); 
    }
    printf("this is the result %i \n", sia(vars->collumn, h));
    printf("this is the key %i for h %i \n", sia(vars->collumn, h), h);

    i = 0;
    j = 0;
    while (buf[i])
    {
        if (buf[i] == '1')
            *(vars->map + sia(vars->collumn, h) + j++) = 1;
        else if (buf[i] == '0')
            *(vars->map + sia(vars->collumn, h)  + j++) = 0;
        else if (buf[i] == '2')
            *(vars->map + sia(vars->collumn, h) + j++) = 2;
        else if (ft_strchr("NSEW", buf[i]))
        {
            *(vars->map +  sia(vars->collumn, h)  + j++) = 0;
            save_position(vars, buf[i], h, j);
        }
        i++;
    }
    return (1);
}
/*

int     parse_map(t_vars *vars, char *buf, int fd, int h)
{
    int i = 0;
    int c = 0;
    int length;

    length = ft_strlen(buf);
    if(h == 0)
    vars->map = NULL;
    vars->map = (int **)ft_realloc(vars->map, sizeof(int **) * (h + 1));
    vars->map[h] = malloc(sizeof(int) * length);
    while (buf[i])
    {
        if (buf[i] == '1')
           vars->map[h][c++] = 1;
        else if (buf[i] == '0')
            vars->map[h][c++] = 0;
        else if (buf[i] == '2')
            vars->map[h][c++] = 2;
        else if (ft_strchr("NSEW", buf[i]))
        {
            vars->map[h][c++] = 0;
            save_position(vars, buf[i], h, c);
        }

        i++;
    }
    printf("this is the size of my array %lu \n", sizeof(vars->map));
    i = 0;
    
    return (1);
}
int     parse_map(t_vars *vars, char *buf, int fd, int h)
{
    int i = 0;
    int c = 0;
    int length;

    length = ft_strlen(buf);
    if(h == 0)
    vars->map = NULL;
    vars->map = (int **)ft_realloc(vars->map, sizeof(int **) * (h + 1));
    vars->map[h] = malloc(sizeof(int) * length);
    while (buf[i])
    {
        if (buf[i] == '1')
           vars->map[h][c++] = 1;
        else if (buf[i] == '0')
            vars->map[h][c++] = 0;
        else if (buf[i] == '2')
            vars->map[h][c++] = 2;
        else if (ft_strchr("NSEW", buf[i]))
        {
            vars->map[h][c++] = 0;
            save_position(vars, buf[i], h, c);
        }

        i++;
    }
    printf("this is the size of my array %lu \n", sizeof(vars->map));
    i = 0;
    
    return (1);
}
int     parse_map(t_vars *vars, char *buf, int fd, int h)
{
    int i = 0;
    int c = 0;
    int length;

    length = ft_strlen(buf);
    if(h == 0)
    vars->map = NULL;
    vars->map = (int **)ft_realloc(vars->map, sizeof(int **) * (h + 1));
    vars->map[h] = malloc(sizeof(int) * length);
    while (buf[i])
    {
        if (buf[i] == '1')
           vars->map[h][c++] = 1;
        else if (buf[i] == '0')
            vars->map[h][c++] = 0;
        else if (buf[i] == '2')
            vars->map[h][c++] = 2;
        else if (ft_strchr("NSEW", buf[i]))
        {
            vars->map[h][c++] = 0;
            save_position(vars, buf[i], h, c);
        }

        i++;
    }
    printf("this is the size of my array %lu \n", sizeof(vars->map));
    i = 0;
    
    return (1);
}i*/
