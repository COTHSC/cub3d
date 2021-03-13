NAME = cub3D

SRCS = main.c \
	utils/reset_buffer.c \
	parsing/parse_resolution.c \
	utils/keys.c \
	utils/draw.c \
	utils/draw_frame.c \
	utils/spritecaster.c \
	utils/key_hook.c \
	utils/spritefinder.c \
	utils/sprite_utils.c \
	utils/raycast_utils.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	utils/draw_floor_cieling.c \
	utils/render_next_frame.c \
	save/bmp.c \

OBJS = $(SRCS:.c=.o)

HEADERS = includes

MLX_REQ_LN = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -Llibft -lft 

MLX_REQ_OSX = -Lmlx_osx -lmlx -framework OpenGL -framework AppKit

CC = gcc

CFLAGS = -Wall -Wextra

DEBUG = -g

#LIB = -L./libft/ -lft

all : $(NAME)

$(NAME) : $(OBJS)
#	$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_OSX)
	$(CC) -O3 -g -o $(NAME) $(OBJS) $(MLX_REQ_LN)
#        $(MAKE) -C ./libft
#        cp libft/libft.a ./$(NAME)
#        ar rcs $@ $^
debug :
	$(CC) ${CFLAGS} ${DEBUG} -I ${HEADERS} -Imlx_osx  -o ${OBJS} -c ${SRCS}
	$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_OSX)

%.o : %.c
	$(CC) ${CFLAGS} -g -I ${HEADERS} -Imlx_osx  -o $@ -c $<
	#$(CC) ${CFLAGS} -I ${HEADERS} -Imlx_linux   -o $@ -c $<

clean :
#        $(MAKE) clean -C ./libft
	rm -f $(OBJS)

fclean : clean
#         $(MAKE) fclean -C ./libft
	rm -f $(NAME)

re : fclean all

