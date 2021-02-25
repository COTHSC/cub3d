NAME = cub3D

SRCS = raytexting2.c \
	utils/reset_buffer.c \
	utils/keys.c \
	utils/innit_position.c \
	utils/draw.c \
	utils/map_to_struct.c \
	utils/draw_frame.c \
	utils/key_hook.c \
	utils/spritecaster.c \
	utils/draw_floor_cieling.c \
	utils/render_next_frame.c \

OBJS = $(SRCS:.c=.o)

HEADERS = includes

MLX_REQ_LN = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm 

MLX_REQ_OSX = -Lmlx_osx -lmlx -framework OpenGL -framework AppKit

CC = gcc

CFLAGS = -Wall -Wextra

DEBUG = -g

#LIB = -L./libft/ -lft

all : $(NAME)

$(NAME) : $(OBJS)
#	$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_OSX)
	$(CC) -g -o $(NAME) $(OBJS) $(MLX_REQ_LN)
#        $(MAKE) -C ./libft
#        cp libft/libft.a ./$(NAME)
#        ar rcs $@ $^
debug :
	$(CC) ${CFLAGS} ${DEBUG} -I ${HEADERS} -Imlx_osx  -o ${OBJS} -c ${SRCS}
	$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_OSX)

%.o : %.c
	$(CC) ${CFLAGS} -g -I ${HEADERS} -Imlx_osx -o $@ -c $<
	#$(CC) ${CFLAGS} -I ${HEADERS} -Imlx_linux -O3  -o $@ -c $<

clean :
#        $(MAKE) clean -C ./libft
	rm -f $(OBJS)

fclean : clean
#         $(MAKE) fclean -C ./libft
	rm -f $(NAME)

re : fclean all
