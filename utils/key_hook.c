#include "../cub3d.h"

 int             key_hook(t_vars *vars)
 {
     double odx;
     double opx;
/*
     if (vars->keys->w)
     {
         if(vars->WorldMap[(int)(vars->p->px + vars->p->dx * vars->p->ms)][(int)(vars->p->py)] == 0)
             vars->p->px += vars->p->dx * vars->p->ms;
         if(vars->WorldMap[(int)(vars->p->px)][(int)(vars->p->py + vars->p->dy * vars->p->ms)] == 0)
             vars->p->py += vars->p->dy * vars->p->ms;
     } */
     
     if (vars->keys->w)
     {
         if(!*(vars->map + sia(vars->collumn, (int)(vars->p->px + vars->p->dx * vars->p->ms)) + (int)(vars->p->py)))
             vars->p->px += vars->p->dx * vars->p->ms;
         if(vars->WorldMap[(int)(vars->p->px)][(int)(vars->p->py + vars->p->dy * vars->p->ms)] == 0)
             vars->p->py += vars->p->dy * vars->p->ms;
     }
     if (vars->keys->s)
     {
         if(vars->WorldMap[(int)(vars->p->px - vars->p->dx * vars->p->ms)][(int)(vars->p->py)] == 0)
             vars->p->px -= vars->p->dx * vars->p->ms;
         if(vars->WorldMap[(int)(vars->p->px)][(int)(vars->p->py - vars->p->dy * vars->p->ms)] == 0)
             vars->p->py -= vars->p->dy * vars->p->ms;
     }
 /*  if (vars->keys->d)
     {
         if(worldMap[(int)(vars->p->px + (vars->p->dx + M_PI_2) * vars->p->ms)][(int)(vars->p->py)]   == 0)
             vars->p->px += (vars->p->dx + M_PI_2) * vars->p->ms;
         if(worldMap[(int)(vars->p->px)][(int)(vars->p->py + (vars->p->dy + 1) * vars->p->ms)] == 0)
             vars->p->py += (vars->p->dy + M_PI_2) * vars->p->ms;
     }
     if (vars->keys->a)
     {
         if(worldMap[(int)(vars->p->px + (vars->p->dx - 1) * vars->p->ms)][(int)(vars->p->py)] == 0)
             vars->p->px += (vars->p->dx - 1) * vars->p->ms;
         if(worldMap[(int)(vars->p->px)][(int)(vars->p->py - (vars->p->dy - 1) * vars->p->ms)] == 0)
             vars->p->py += (vars->p->dy - 1) * vars->p->ms;
     }*/
     if (vars->keys->r)
     {
         odx = vars->p->dx;

         vars->p->dx = vars->p->dx * cos(-1 * vars->p->rs) - vars->p->dy *sin(-1 * vars->p->rs);
         vars->p->dy = odx * sin(-vars->p->rs) + vars->p->dy * cos(-vars->p->rs);
         opx = vars->p->plx;
         vars->p->plx = vars->p->plx * cos(-1 *(vars->p->rs)) - vars->p->ply * sin(-1 * (vars->p->rs));
         vars->p->ply = opx * sin(-1 * vars->p->rs) + vars->p->ply * cos(-1 * vars->p->rs);
     }
     if (vars->keys->l)
     {
         odx = vars->p->dx;

         vars->p->dx = vars->p->dx * cos(vars->p->rs) - vars->p->dy *sin(vars->p->rs);
         vars->p->dy = odx * sin(vars->p->rs) + vars->p->dy * cos(-vars->p->rs);
         opx = vars->p->plx;
         vars->p->plx = vars->p->plx * cos(vars->p->rs) - vars->p->ply * sin(vars->p->rs);
         vars->p->ply = opx * sin(vars->p->rs) + vars->p->ply * cos(vars->p->rs);
     }
     draw_frame(vars);
     return (1);
 }
