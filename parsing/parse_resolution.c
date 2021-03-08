#include "../cub3d.h"
#include "../libft/libft.h"
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
    int j;
    fptr functions[8];

    h = 0;
    farray = malloc(sizeof(char *) * 8);
    innit_arrayf(farray, functions);
    i = 1;
    while (i != 0)
    {
        i = get_next_line(fd, &buf);
        c = 0;
        j = 0;
        while(buf[j] == ' ')
            j++;
        while(c < 8)
        {
            if(ft_strnstr(buf, farray[c], 3))
                (*functions[c])(vars->res, buf);
            else if (ft_isdigit(buf[j]))
            {
                parse_map(vars, buf, h++);
                break;
            }

            c++;
        }
        free(buf);
    }
    while (i < 8)
        free(farray[i++]);
    free(farray);
    return h;
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
        ft_strlcpy(res->NO, &buf[start], length + 1); 
    }
    else if(ft_strnstr(buf, "SO", 3))
    {
        res->SO = malloc(length + 1);
        ft_strlcpy(res->SO, &buf[start], length + 1); 
    }
    else if(ft_strnstr(buf, "WE", 3))
    {
        res->WE = malloc(length + 1);
        ft_strlcpy(res->WE, &buf[start], length + 1); 
    }
    else if(ft_strnstr(buf, "EA", 3))
    {
        res->EA = malloc(length + 1);
        ft_strlcpy(res->EA, &buf[start], length + 1); 
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
    ft_strlcpy(res->S, &buf[start], length + 1); 
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

int     init_orientation(t_vars *vars, double h)
{
    double opx;
    double odx;
    if (h == 0)
        return (0);
    printf("this is rot %f \n", h);
    vars->p->dx = vars->p->dx * cos(h) - vars->p->dy *sin(h);
    vars->p->dy = odx * sin(h) + vars->p->dy * cos(-h);
    opx = vars->p->plx;
    vars->p->plx = vars->p->plx * cos(h) - vars->p->ply * sin(h);
    vars->p->ply = opx * sin(h) + vars->p->ply * cos(h);
    return (0);
}

int     save_position(t_vars *vars, char c, int h, int i)
{
    double rot;

    if (c == 'N')
        rot = 0;
    else if (c == 'S')
        rot = M_PI;
    else if (c == 'E')
        rot = 3 * M_PI / 2;
    else if (c == 'W')
        rot = M_PI / 2;

    printf("this is rot %f \n", rot);
    vars->p->px = (double)h;
    vars->p->py = (double)i;
    vars->p->dx = -1;
    vars->p->dy = 0;
    vars->p->plx =  0;
    vars->p->ply = 0.66;
    vars->p->ms = 0.03;
    vars->p->rs = 0.03;
    init_orientation(vars, rot);
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

int     check_map(t_vars *vars)
{
    int h;
    int w;
    int ret;

    h = 1;
    ret = 0;
    while (h < vars->map_h)
    {
        w = 1;
        while (w < vars->collumn[h] && w < vars->collumn[h - 1])
        {
            if (get_value(vars, h, w) + get_value(vars, h - 1, w) == 5)
                ret = -1;
            if (get_value(vars, h, w) + get_value(vars, h, w - 1) == 5)
                ret = -1;
            if (get_value(vars, h, w) + get_value(vars, h - 1, w) == 7)
                ret = -1;
            if (get_value(vars, h, w) + get_value(vars, h, w - 1) == 7)
                ret = -1;
            w++;
        }
        w = 1;
        while (w < vars->collumn[h])
        {
            if (get_value(vars, 0, w) == 0)
                ret = -1;
            if (get_value(vars, h, w) == 0 && w > vars->collumn[h + 1])
                ret = -1;
            if (get_value(vars, h, w) == 2 && w > vars->collumn[h + 1])
                ret = -1;
            w++;
        }
        h++;
    }
    return (ret);
}

int     parse_map(t_vars *vars, char *buf, int h)
{
    int length;
    int j;
    int i;
    static int nc;
    static int arlength;

    length = ft_strlen(buf) + 1;
    if (h == 0)
    { 
        nc = 0;
        arlength = (length + 1) * sizeof(int);
        vars->collumn = (int *)malloc(sizeof(int));
        vars->collumn[nc] = length;
        vars->map = (int *)malloc(sizeof(int) * length * (h + 2));
    }
    else
    {
        vars->collumn = (int *)ft_realloc(vars->collumn, sizeof(int) * (nc + 1), sizeof(int) * (nc + 2));
        vars->collumn[++nc] = length;
        vars->map = (int *)ft_realloc(vars->map, arlength, sizeof(int) * length + arlength);
        arlength += (length) * sizeof(int); 
    }
    i = -1;
    j = 0;

    *(vars->map + sia(vars->collumn, h) + j++) = 5;
    while (buf[++i])
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
        else
            *(vars->map + sia(vars->collumn, h) + j++) = 5;
    }
    *(vars->map + sia(vars->collumn, h) + j) = 5;
    return (1);
}