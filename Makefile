NAME = cub3d

SRC_DIR = src
INC_DIR = include
LIBFT_DIR = libft
MLX_DIR = minilibx_mms_20200219

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/entity.c \
	$(SRC_DIR)/player.c \
	$(SRC_DIR)/map.c \
	$(SRC_DIR)/game.c \
	$(SRC_DIR)/renderer.c \
	$(SRC_DIR)/game_loop.c \

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re