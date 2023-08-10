NAME = Cub3D

SRCS = src/main.c src/get_next_line.c src/map.c src/free.c src/raycasting.c src/color.c src/key.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
MLX_DIR = minilibx-linux

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR)
LIBRARIES = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lX11 -lXext -lm

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBRARIES) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
