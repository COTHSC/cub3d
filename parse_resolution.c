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
    fptr functions[8];

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
       g = ft_atoi(&buf[i]);
       while (buf[i] != ',')
            i++;
       b = ft_atoi(&buf[i]);
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

