int     load_textures(t_vars *vars)
{

        vars->tex = malloc(sizeof(t_tex));
        vars->tex->a = malloc(sizeof(t_img));
        vars->tex->a->ptr = mlx_xpm_file_to_image(vars->mlx, "../pics/greystone_1.xpm", &vars->tex->a->width, &vars->tex->a->height); 
        vars->tex->a->data = mlx_get_data_addr(vars->tex->a->ptr, &vars->tex->a->bpp, &vars->tex->a->size_l, &vars->tex->a->endian);
        return (1);
}



int main()
{
        t_vars  vars;
        t_tex   *tex;



        vars.pos = malloc(sizeof(t_pos));
        init_position(&vars);

        vars.mlx = mlx_init();
        vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Hello world!");
        load_textures(&vars);


        mlx_loop(vars.mlx);
        return 0;
}
