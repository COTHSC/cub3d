#include "cub3d.h"
#include "./libft/libft.h"
#include <fcntl.h>

int     parse_lines(t_vars *vars, int fd)
{
    char *buf;
    int i;

    i = 1;
    while (i != 0)
    {
        i = get_next_line(fd, &buf);
    }

    return 1;
}


int     parse_resolution(t_res *res, int fd)
{
       char *buf;
       int i;
        
       get_next_line(fd, &buf);
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

int     parse_textures(t_texpath *texpath, fd)
{

}
