#include "../cub3d.h"

int     draw_cieling(t_vars *vars, int x, int draw_start)
{
        int i = 0;

        while (i < draw_start)
                vars->buf[i++][x] = CCOLOR;
        return (1);
}

int     draw_floor(t_vars *vars, int x, int draw_end)
{
        int i = draw_end;

        while (i < screenHeight)
                vars->buf[i++][x] = FCOLOR;
        return (1);
}
