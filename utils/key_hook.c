#include "../cub3d.h"

 int             key_hook(t_vars *vars)
 {
     double oldDirX;
     double oldPlaneX;

     if (vars->keys->w)
     {
         if(vars->WorldMap[(int)(vars->pos->posX + vars->pos->dirX * vars->pos->move_speed)][(int)(vars->pos->posY)] == 0)
             vars->pos->posX += vars->pos->dirX * vars->pos->move_speed;
         if(vars->WorldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY + vars->pos->dirY * vars->pos->move_speed)] == 0)
             vars->pos->posY += vars->pos->dirY * vars->pos->move_speed;
     }
     if (vars->keys->s)
     {
         if(vars->WorldMap[(int)(vars->pos->posX - vars->pos->dirX * vars->pos->move_speed)][(int)(vars->pos->posY)] == 0)
             vars->pos->posX -= vars->pos->dirX * vars->pos->move_speed;
         if(vars->WorldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY - vars->pos->dirY * vars->pos->move_speed)] == 0)
             vars->pos->posY -= vars->pos->dirY * vars->pos->move_speed;
     }
 /*  if (vars->keys->d)
     {
         if(worldMap[(int)(vars->pos->posX + (vars->pos->dirX + M_PI_2) * vars->pos->move_speed)][(int)(vars->pos->posY)]   == 0)
             vars->pos->posX += (vars->pos->dirX + M_PI_2) * vars->pos->move_speed;
         if(worldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY + (vars->pos->dirY + 1) * vars->pos->move_speed)] == 0)
             vars->pos->posY += (vars->pos->dirY + M_PI_2) * vars->pos->move_speed;
     }
     if (vars->keys->a)
     {
         if(worldMap[(int)(vars->pos->posX + (vars->pos->dirX - 1) * vars->pos->move_speed)][(int)(vars->pos->posY)] == 0)
             vars->pos->posX += (vars->pos->dirX - 1) * vars->pos->move_speed;
         if(worldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY - (vars->pos->dirY - 1) * vars->pos->move_speed)] == 0)
             vars->pos->posY += (vars->pos->dirY - 1) * vars->pos->move_speed;
     }*/
     if (vars->keys->r)
     {
         oldDirX = vars->pos->dirX;

         vars->pos->dirX = vars->pos->dirX * cos(-1 * vars->pos->rot_speed) - vars->pos->dirY *sin(-1 * vars->pos->rot_speed);
         vars->pos->dirY = oldDirX * sin(-vars->pos->rot_speed) + vars->pos->dirY * cos(-vars->pos->rot_speed);
         oldPlaneX = vars->pos->planeX;
         vars->pos->planeX = vars->pos->planeX * cos(-1 *(vars->pos->rot_speed)) - vars->pos->planeY * sin(-1 * (vars->pos->rot_speed));
         vars->pos->planeY = oldPlaneX * sin(-1 * vars->pos->rot_speed) + vars->pos->planeY * cos(-1 * vars->pos->rot_speed);
     }
     if (vars->keys->l)
     {
         oldDirX = vars->pos->dirX;

         vars->pos->dirX = vars->pos->dirX * cos(vars->pos->rot_speed) - vars->pos->dirY *sin(vars->pos->rot_speed);
         vars->pos->dirY = oldDirX * sin(vars->pos->rot_speed) + vars->pos->dirY * cos(-vars->pos->rot_speed);
         oldPlaneX = vars->pos->planeX;
         vars->pos->planeX = vars->pos->planeX * cos(vars->pos->rot_speed) - vars->pos->planeY * sin(vars->pos->rot_speed);
         vars->pos->planeY = oldPlaneX * sin(vars->pos->rot_speed) + vars->pos->planeY * cos(vars->pos->rot_speed);
     }
     draw_frame(vars);
     return (1);
 }
