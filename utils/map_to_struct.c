#include "../cub3d.h"

int map_to_struct(int map[24][24], t_vars *vars)
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
        vars->WorldMap[i][c] = map[i][c];
        c++;
        }
        i++;
    }
    return (1);
}
