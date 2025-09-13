# Project name
NAME = cub3d

# Directories
SRC_DIR = src
INC_DIR = include
LIBFT_DIR = libft
MLX_DIR = minilibx_mms_20200219

# Source files
SRCS = \
	$(SRC_DIR)/entity.c \
	$(SRC_DIR)/player.c \
	$(SRC_DIR)/map.c \
	$(SRC_DIR)/scene.c \
	$(SRC_DIR)/texture.c \
	$(SRC_DIR)/renderer.c \
	$(SRC_DIR)/renderer_raycast.c \
	$(SRC_DIR)/game_loop.c \
	$(SRC_DIR)/door.c \
	$(SRC_DIR)/ui_element.c \
	$(SRC_DIR)/button.c \
	$(SRC_DIR)/text.c \
	$(SRC_DIR)/menu.c \
	$(SRC_DIR)/stats.c \
	$(SRC_DIR)/completion.c \
	$(SRC_DIR)/main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Rules
all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

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