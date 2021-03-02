#include "cub3d.h"
#include "./libft/libft.h"
#include <fcntl.h>

int     parse_resolution(char *map_file, t_res *res)
{
       int fd;
       char *buf;
       int i;
        
       fd = open(map_file, O_RDONLY);
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
        
        
      printf("this is my w %i and h %i \n", res->w, res->h); 
       return 1;
}
