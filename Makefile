# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 11:53:52 by rakman            #+#    #+#              #
#    Updated: 2026/02/15 05:27:19 by rakman           ###   ########.fr        #
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

SRC_CORE = src/01_core/00_game_loop.c \
           src/01_core/01_utils.c

SRC_EVENTS = src/04_events/00_key_handler.c \
             src/04_events/01_move_player.c \
             src/04_events/02_rotate_player.c

SRC_EXIT = src/05_exit/00_clean_exit.c \
           src/05_exit/01_error.c

SRC_INITIALIZE_GAME = src/00_initialize_game/00_validate_mapfile/00_validate_mapfile.c \
                      src/00_initialize_game/00_validate_mapfile/01_dispatch_sneaky_files.c \
                      src/00_initialize_game/00_validate_mapfile/01_dispatch_sneaky_utils.c \
                      src/00_initialize_game/00_validate_mapfile/02_check_file_ending.c \
                      src/00_initialize_game/00_validate_mapfile/03_file_has_double_map.c \
                      src/00_initialize_game/00_validate_mapfile/04_validate_color_format.c \
                      src/00_initialize_game/01_parse_mapfile/00_parse_mapfile.c \
                      src/00_initialize_game/01_parse_mapfile/01_read_map_grid/00_read_map_grid.c \
                      src/00_initialize_game/01_parse_mapfile/01_read_map_grid/01_read_map_grid_utils.c \
                      src/00_initialize_game/01_parse_mapfile/02_validate_map/00_validate_map.c \
                      src/00_initialize_game/01_parse_mapfile/02_validate_map/01_normalize_map.c \
                      src/00_initialize_game/01_parse_mapfile/02_validate_map/02_validate_enclosure.c \
                      src/00_initialize_game/01_parse_mapfile/02_validate_map/03_find_player.c \
                      src/00_initialize_game/01_parse_mapfile/03_parse_textures/00_parse_textures.c \
                      src/00_initialize_game/01_parse_mapfile/03_parse_textures/01_parse_texture_path.c \
                      src/00_initialize_game/01_parse_mapfile/03_parse_textures/02_parse_color.c \
                      src/00_initialize_game/02_init_game_resources/00_init_game_resources.c \
                      src/00_initialize_game/02_init_game_resources/01_load_textures.c \
                      src/00_initialize_game/02_init_game_resources/02_set_player_position.c

SRC_RAYCASTING = src/02_raycasting/00_dda.c \
                 src/02_raycasting/01_math_utils.c \
                 src/02_raycasting/02_raycaster.c

SRC_RENDER = src/03_render/00_render_frame.c \
             src/03_render/01_draw_walls.c

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

SRCS = $(SRC_MAIN) $(SRC_CORE) $(SRC_EVENTS) $(SRC_EXIT) \
       $(SRC_INITIALIZE_GAME) $(SRC_RAYCASTING) $(SRC_RENDER) $(SRC_LIBFT) $(SRC_GNL)

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
