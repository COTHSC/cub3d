NAME = cub3D

SRCS = main.c \
	parsing/parse_resolution.c \
	parsing/max_size.c \
	parsing/init_error.c \
	utils/free_for_exit.c \
	parsing/parse_resolution_utils1.c \
	parsing/parse_resolution_utils2.c \
	parsing/parse_resolution_utils3.c \
	parsing/parse_resolution_utils4.c \
	parsing/init_pos_dir.c \
	parsing/check_config.c \
	parsing/map_checking.c \
	utils/keys.c \
	utils/draw.c \
	utils/draw_frame.c \
	utils/spritecaster.c \
	utils/exit_game.c \
	utils/key_hook.c \
	utils/spritefinder.c \
	utils/sprite_utils.c \
	utils/raycast_utils.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	utils/draw_floor_cieling.c \
	utils/render_next_frame.c \
	utils/main_utils.c \
	save/bmp.c \

OBJS = $(SRCS:.c=.o)

HEADERS = includes

MLX_REQ_LN = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -Llibft -lft 

CC = clang -g

CFLAGS = -g -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C ./libft/
	$(MAKE) -C ./mlx_linux/
	$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_LN)

%.o : %.c
	$(CC) ${CFLAGS} -I ${HEADERS} -Imlx_linux   -o $@ -c $<

clean :
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./mlx_linux
	rm -f $(OBJS)

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re : fclean all

