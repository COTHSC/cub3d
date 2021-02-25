#include "../cub3d.h"

int     init_position(t_vars *vars)
{
    vars->pos->posX = 22.0;
    vars->pos->posY = 11.5;
    vars->pos->dirX = -1;
    vars->pos->dirY = 0;
    vars->pos->planeX =  0;
    vars->pos->planeY = 0.66;
    vars->pos->move_speed = 0.03;
    vars->pos->rot_speed = 0.03;
    return (1);
}
