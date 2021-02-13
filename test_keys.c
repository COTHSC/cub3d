
#include <stdio.h>
#include "mlx_linux/mlx.h"

typedef struct s_param{
        int             x;
        int             y;
        char    str[3];
}                               t_param;


void            param_init(t_param *param)
{
        param->x = 3;
        param->y = 4;
        param->str[0] = 'a';
        param->str[1] = 'b';
        param->str[2] = '\0';
}

int		keypress(int keycode, t_param *param)
{
	printf("this is the keycode %i \n", keycode);
}

int main()
{
	void *mlx;
	void* window;
	t_param	param;
	
	param_init(&param);
	mlx = mlx_init();
	window = mlx_new_window(mlx, 640, 480, "keytry");
	
	mlx_hook(window, 2, 1L << 0, &keypress, &param);
	mlx_loop(mlx);
}
