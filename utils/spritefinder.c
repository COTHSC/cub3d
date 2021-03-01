#include "../cub3d.h"

int     innit_sprites(t_sprites **sprite, double x, double y, int num)
{
        sprite[num]->x = x;
        sprite[num]->y = y;
        sprite[num]->texture = 1;
        sprite[num]->dist = 0;
        return (1);
}

int     spritefinder(t_sprites **sprite, int **map)
{
	int w;
	int h;
	int i;
	
	w = 0;
	h = 0;
	i = 0;
	while (map[h][0])
	{
		w = 0;
		while ( w < 24)
		{
			if(map[h][w] == 2)
			{
                
				sprite[i] = malloc(sizeof(t_sprites));
				innit_sprites(sprite, h + 0.5, w + 0.5 , i);
				i++;
				
			}
			w++;
		}
		h++;
	}
	return (1);
}
