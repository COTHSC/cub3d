#include "../cub3d.h"

int map_to_struct(int *map, t_vars *vars)
{
    int i;
    int c;
    int map_height = 24;
    int map_width = 24;

    i = 0;
    while (i < map_height)
    {
        c = 0;
        while (c < map_width)
        {
        vars->WorldMap[i][c] = *(vars->map + i * 24 + c);
        c++;
        }
        i++;
    }
    return (1);
}
