# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fguryel <fguryel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 11:53:52 by rakman            #+#    #+#              #
#    Updated: 2025/08/27 02:52:27 by fguryel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./inc -I./lib/minilibx-linux -I./lib/get_next_line

# MLX
MLX_DIR = lib/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# Source files
SRC_MAIN = src/main.c

SRC_CORE = src/core/game_loop.c \
           src/core/utils.c

SRC_EVENTS = src/events/key_handler.c \
             src/events/move_player.c

SRC_EXIT = src/exit/clean_exit.c \
           src/exit/error.c

SRC_INIT = src/init/init_data.c \
           src/init/init_mlx.c

SRC_PARSING = src/parsing/check_map.c \
              src/parsing/parse_file.c \
              src/parsing/parse_map.c \
              src/parsing/parse_textures.c

SRC_RAYCASTING = src/raycasting/dda.c \
                 src/raycasting/math_utils.c \
                 src/raycasting/raycaster.c

SRC_RENDER = src/render/draw_walls.c \
             src/render/rebder_frame.c \
             src/render/textures.c

SRC_LIBFT = lib/libft/ft_atoi.c \
            lib/libft/ft_bzero.c \
            lib/libft/ft_calloc.c \
            lib/libft/ft_isalnum.c \
            lib/libft/ft_isalpha.c \
            lib/libft/ft_isascii.c \
            lib/libft/ft_isdigit.c \
            lib/libft/ft_isprint.c \
            lib/libft/ft_itoa.c \
            lib/libft/ft_lstadd_back.c \
            lib/libft/ft_lstadd_front.c \
            lib/libft/ft_lstclear.c \
            lib/libft/ft_lstdelone.c \
            lib/libft/ft_lstiter.c \
            lib/libft/ft_lstlast.c \
            lib/libft/ft_lstmap.c \
            lib/libft/ft_lstnew.c \
            lib/libft/ft_lstsize.c \
            lib/libft/ft_memchr.c \
            lib/libft/ft_memcmp.c \
            lib/libft/ft_memcpy.c \
            lib/libft/ft_memmove.c \
            lib/libft/ft_memset.c \
            lib/libft/ft_putchar_fd.c \
            lib/libft/ft_putendl_fd.c \
            lib/libft/ft_putnbr_fd.c \
            lib/libft/ft_putstr_fd.c \
            lib/libft/ft_split.c \
            lib/libft/ft_strchr.c \
            lib/libft/ft_strdup.c \
            lib/libft/ft_striteri.c \
            lib/libft/ft_strjoin.c \
            lib/libft/ft_strlcat.c \
            lib/libft/ft_strlcpy.c \
            lib/libft/ft_strlen.c \
            lib/libft/ft_strmapi.c \
            lib/libft/ft_strncmp.c \
            lib/libft/ft_strnstr.c \
            lib/libft/ft_strrchr.c \
            lib/libft/ft_strtrim.c \
            lib/libft/ft_substr.c \
            lib/libft/ft_tolower.c \
            lib/libft/ft_toupper.c

SRC_GNL = lib/get_next_line/get_next_line.c \
          lib/get_next_line/get_next_line_utils.c

SRCS = $(SRC_MAIN) $(SRC_CORE) $(SRC_EVENTS) $(SRC_EXIT) $(SRC_INIT) \
       $(SRC_PARSING) $(SRC_RAYCASTING) $(SRC_RENDER) $(SRC_LIBFT) $(SRC_GNL)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
